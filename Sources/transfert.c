/*
** transfert.c for transfert in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:47:04 2017 Thomas LE MOULLEC
** Last update Tue May 16 23:15:00 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            pasv_fct(t_connect *server, t_handler *control)
{
  t_connect	pasv;
  socklen_t	len;
  int		port;

  pasv.client_ip = NULL;
  pasv.pe = NULL;
  pasv.s_in_size = sizeof(pasv.s_in_client);
  if (!(pasv.pe = getprotobyname("TCP")))
    handle_error_sys("Error With TCP Protocol");
  if ((pasv.fd = socket(AF_INET, SOCK_STREAM, pasv.pe->p_proto)) == -1)
    handle_error_sys("Could not create new socket");
  pasv.s_in.sin_family = AF_INET;
  pasv.s_in.sin_port = htons(0);
  pasv.s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(pasv.fd, (const struct sockaddr *)&pasv.s_in,	\
	   sizeof(pasv.s_in)) == -1)
    {
      close(pasv.fd);
      handle_error_sys("Cannot Bind on this port");
    }
  if (listen(pasv.fd, 42) == -1)
    {
      close(pasv.fd);
      handle_error_sys("Error on the Listen");
    }
  len = sizeof(&pasv.s_in);
  getsockname(pasv.fd, (struct sockaddr *)&pasv.s_in, &len);
  port = ntohs(pasv.s_in.sin_port);
  dprintf(server->client_fd, "%s(127,0,0,1,%d,%d).\r\n", SUCCESS_PASV, port / 256, port - (port / 256 * 256));
  if ((pasv.client_fd = accept(pasv.fd, (struct sockaddr *)&pasv.s_in_client, \
			       &pasv.s_in_size)) == -1)
    {
      close(pasv.fd);
      handle_error_sys("Accept failed");
    }
  control->pasv_client_fd = pasv.client_fd;
  control->pasv = true;
  return (true);
}

bool            port_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("PORT\n");
  return (true);
}

bool            retr_fct(t_connect *server, t_handler *control)
{
  int		fd;
  bool		end;
  char		*client_res;

  end = false;
  if (control->pasv == false && control->activ == false)
    {
      dprintf(server->client_fd, "%s", ERR_PASV_ACTIF);
      return (false);
    }
  if ((fd = open(control->client.param, O_RDONLY)) == -1)
    handle_error_sys("Open Failed");
  while (end == false)
    {
      client_res = client_read(fd);
      if (client_res == NULL)
	{
	  end = true;
	  close(fd);
	  close(control->pasv_client_fd);
	}
      if (end == false)
	dprintf(control->pasv_client_fd, "%s", client_res);
    }
  control->pasv = false;
  control->activ = false;
  return (true);
}

bool            stor_fct(t_connect *server, t_handler *control)
{
  bool		end;
  int		fd;
  char		*client_res;

  end = false;
  if (control->pasv == false && control->activ == false)
    {
      dprintf(server->client_fd, "%s", ERR_PASV_ACTIF);
      return (false);
    }
  if ((fd = open(control->client.param, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH)) == -1)
    handle_error_sys("Open Failed");
  while (end == false)
    {
      client_res = client_read(control->pasv_client_fd);
      if (client_res == NULL)
	{
	  end = true;
	  close(fd);
	  close(control->pasv_client_fd);
	}
      if (end == false)
	dprintf(fd, "%s", client_res);
    }
  control->pasv = false;
  control->activ = false;
  return (true);
}

bool            list_fct(t_connect *server, t_handler *control)
{
  char		**av;
  pid_t		pid;
  int		status;

  if (control->pasv == false && control->activ == false)
    {
      dprintf(server->client_fd, "%s", ERR_PASV_ACTIF);
      return (false);
    }
  pid = fork();
  if ((av = malloc(sizeof(char *) * 4)) == NULL)
    handle_error_sys("Malloc Failed");
  av[0] = strdup("/bin/ls");
  av[1] = strdup("-l");
  if (strcmp(control->client.param, "") != 0)
    av[2] = strdup(control->client.param);
  else
    av[2] = NULL;
  av[3] = NULL;
  if (pid == 0)
    {
      dup2(control->pasv_client_fd, 1);
      execve("/bin/ls", av, NULL);
    }
  else
    waitpid(pid, &status, WUNTRACED | WCONTINUED);
  close(control->pasv_client_fd);
  return (true);
}
