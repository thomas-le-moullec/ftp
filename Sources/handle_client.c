/*
** handle_client.c for handle_client in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 14:54:20 2017 Thomas LE MOULLEC
** Last update Sun May 14 16:17:52 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char            *client_read(int client_fd)
{
  char          *buffer;
  int           size;

  if ((buffer = malloc(sizeof(*buffer) * 100)) == NULL)
    handle_error_sys("Malloc Failed");
  if ((size = read(client_fd, buffer, 100)) == -1)
    return (NULL);
  buffer[size] = '\0';
  return (buffer);
}

int		get_param(char *client_res, t_handler *control, int i)
{
  int		h;

  h = 0;
  while (client_res[i] == SP1 || client_res[i] == SP2)
    i++;
  if ((control->client.param = malloc(sizeof(*client_res) * \
				      (strlen(client_res) + 1))) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1 &&	\
	 client_res[i] != CRLF2)
    {
      control->client.param[h] = client_res[i];
      i++;
      h++;
    }
  control->client.param[h] = '\0';
  return (i);
}

void		get_order(t_handler *control, char *client_res)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((control->client.cmd = malloc(sizeof(*client_res) * \
				    (strlen(client_res) + 1))) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1 && \
	 client_res[i] != CRLF2)
    {
      control->client.cmd[j] = client_res[i];
      if (client_res[i] == SP1 || client_res[i] == SP2)
	get_param(client_res, control, i);
      if (client_res[i] != '\0')
	i++;
      j++;
    }
  control->client.cmd[j] = '\0';
}

bool			exec_order(t_handler *control, t_connect *server)
{
  int			i;
  static t_command_tab *fct = NULL;

  i = 0;
  if (fct == NULL)
    {
      if ((fct = malloc(sizeof(*fct))) == NULL)
	handle_error_sys("Malloc Failed");
      initialise_cmd(fct);
    }
  if (check_authentification(control, server) == false)
    return (false);
  while (i < NBR_CMD)
    {
      if (strcmp(control->client.cmd, fct->cmd[i]) == 0)
	return ((fct->cmd_tab[i])(server, control));
      i++;
    }
  dprintf(server->client_fd, "%s\n", UNKNOWN_CMD);
  return (false);
}

bool		handle_client(t_connect *server, t_handler *control)
{
  char		*client_res;

  server->client_ip = inet_ntoa(server->s_in_client.sin_addr);
  client_res = client_read(server->client_fd);
  get_order(control, client_res);
  exec_order(control, server);
  while (strcmp(control->client.cmd, QUIT) != 0)
    {
      client_res = client_read(server->client_fd);
      get_order(control, client_res);
      exec_order(control, server);
      free(client_res);
    }
  if (close(server->client_fd) == -1)
    return (false);
  return (true);
}
