/*
** handle_client.c for handle_client in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 14:54:20 2017 Thomas LE MOULLEC
** Last update Fri May 19 11:44:20 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		get_param(char *client_res, t_handler *control, int i)
{
  int		j;

  j = 0;
  if (client_res[i] == CRLF1)
    {
      control->client.param = strdup("");
      return (true);
    }
  control->client.param = malloc(sizeof(*control->client.param) * \
				 (strlen(client_res) + 1));
  while (client_res[i] != '\0' && client_res[i] != CRLF1)
    {
      if (control->client.param[j] != SP1 && control->client.param[j] != SP2)
	{
	  control->client.param[j] = tolower(client_res[i]);
	  j++;
	}
      i++;
    }
  control->client.param[j] = '\0';
  return (true);
}

bool		get_order(t_handler *control, char *client_res)
{
  int		i;

  i = 0;
  if ((control->client.cmd = malloc(sizeof(*client_res) * 10000)) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1  &&	  \
	 client_res[i] != SP1 && client_res[i] != SP2)
    {
      control->client.cmd[i] = tolower(client_res[i]);
      i++;
    }
  control->client.cmd[i] = '\0';
  while (client_res[i] == SP1 || client_res[i] == SP2)
    i++;
  get_param(client_res, control, i);
  //  printf("CMD =...%s... && PARAM =...%s...\n", control->client.cmd, control->client.param);
  return (true);
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
  client_res = NULL;
  server->client_ip = inet_ntoa(server->s_in_client.sin_addr);
  dprintf(server->client_fd, "%s", WELCOME);
  control->client.param = strdup("");
  while (end == false)
    {
      //      client_res = client_read(server->client_fd);
      client_res = get_next_line(server->client_fd);
      get_order(control, client_res);
      exec_order(control, server);
      if (strcmp(control->client.cmd, QUIT) == 0)
	end = true;
      free(client_res);
      control->client.param = strdup("");
      control->client.param = NULL;
      control->client.cmd = NULL;
    }
  if (close(server->client_fd) == -1)
    return (false);
  return (true);
}
