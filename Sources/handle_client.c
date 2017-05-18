/*
** handle_client.c for handle_client in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 14:54:20 2017 Thomas LE MOULLEC
** Last update Thu May 18 11:17:43 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

int		get_param(char *client_res, t_handler *control, int i)
{
  int		h;

  h = 0;
  if (client_res[i] == '\0' || client_res[i] == CRLF1 || \
      client_res[i] == CRLF2)
    {
      control->client.param = "";
      return (i);
    }
  while (client_res[i] == SP1 || client_res[i] == SP2)
    i++;
  if ((control->client.param = malloc(sizeof(*client_res) * \
				      (strlen(client_res) + 1))) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1 &&	\
	 client_res[i] != CRLF2 && client_res[i] != SP1 && \
	 client_res[i] != SP2)
    control->client.param[h++] = client_res[i++];
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
  control->client.param = "";
  while (client_res[i] != '\0' && client_res[i] != CRLF1 && \
	 client_res[i] != CRLF2 && client_res[i] != SP1 &&
	 client_res[i] != SP2)
    control->client.cmd[j++] = client_res[i++];
  control->client.cmd[j] = '\0';
  get_param(client_res, control, i);
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
  dprintf(server->client_fd, "%s", UNKNOWN_CMD);
  return (false);
}

bool		handle_client(t_connect *server, t_handler *control)
{
  char		*client_res;
  bool		end;

  end = false;
  server->client_ip = inet_ntoa(server->s_in_client.sin_addr);
  dprintf(server->client_fd, "%s", WELCOME);
  while (end == false)
    {
      client_res = client_read(server->client_fd);
      get_order(control, client_res);
      exec_order(control, server);
      if (strcmp(control->client.cmd, QUIT) == 0)
	end = true;
      free(client_res);
      control->client.param = NULL;
      control->client.cmd = NULL;
    }
  if (close(server->client_fd) == -1)
    return (false);
  return (true);
}
