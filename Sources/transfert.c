/*
** transfert.c for transfert in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:47:04 2017 Thomas LE MOULLEC
** Last update Fri May 19 14:27:13 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		get_fd_pasv(t_handler *control, t_connect pasv, t_connect *server)
{
  int		port;
  socklen_t	len;

  len = sizeof(&pasv.s_in);
  getsockname(pasv.fd, (struct sockaddr *)&pasv.s_in, &len);
  port = ntohs(pasv.s_in.sin_port);
  dprintf(server->client_fd, "%s(127,0,0,1,%d,%d).\r\n", \
	  SUCCESS_PASV, port / 256, port - (port / 256 * 256));
  if ((pasv.client_fd = accept(pasv.fd, (struct sockaddr *)&pasv.s_in_client, \
			       &pasv.s_in_size)) == -1)
    {
      close(pasv.fd);
      handle_error_sys("Accept failed");
    }
  control->client_fd = pasv.client_fd;
  control->pasv = true;
  return (true);
}

bool            pasv_fct(t_connect *server, t_handler *control)
{
  t_connect	pasv;

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
  return (get_fd_pasv(control, pasv, server));
}

bool            port_fct(t_connect *server, t_handler *control)
{
  t_connect	port;
  int		fd;

  (void)server;
  port.pe = getprotobyname("TCP");
  if (!port.pe)
    return (1);
  if ((fd = socket(AF_INET, SOCK_STREAM, port.pe->p_proto)) == -1)
    handle_error("Could not create new Socket");
  port.s_in.sin_family = AF_INET;
  port.s_in.sin_port = htons(atoi(control->client.param));
  port.s_in.sin_addr.s_addr = inet_addr(LOCALHOST);
  if (connect(fd, (struct sockaddr *)&port.s_in, sizeof(port.s_in)) == -1)
    handle_error("Could not connect");
  control->client_fd = fd;
  control->activ = true;
  dprintf(server->client_fd, "%s", SUCCESS_CMD);
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
  dprintf(server->client_fd, "%s", SUCCESS_DATA);
  if ((fd = open(control->client.param, O_RDONLY)) == -1)
    handle_error_sys("Open Failed");
  while (end == false)
    {
      client_res = client_read(fd, 1000);
      end = check_end_order_retr(client_res, end, fd, control->client_fd);
    }
  control->pasv = false;
  control->activ = false;
  dprintf(server->client_fd, "%s", END_DATA);
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
  dprintf(server->client_fd, "%s", SUCCESS_DATA);
  if ((fd = open(control->client.param, O_RDWR | O_CREAT | O_TRUNC, \
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    handle_error_sys("Open Failed");
  while (end == false)
    {
      client_res = client_read(control->client_fd, 1000);
      end = check_end_order_stor(client_res, end, fd, control->client_fd);
    }
  control->pasv = false;
  control->activ = false;
  dprintf(server->client_fd, "%s", END_DATA);
  return (true);
}
