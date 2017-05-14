/*
** basics.c for basics in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:45:08 2017 Thomas LE MOULLEC
** Last update Sun May 14 21:56:26 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            quit_fct(t_connect *server, t_handler *control)
{
  (void)control;
  dprintf(server->client_fd, "221 QUIT\n");
  return (true);
}

bool            del_fct(t_connect *server, t_handler *control)
{
  if (remove(control->client.param) == -1)
    {
      handle_error_sys(control->client.param);
      return (false);
    }
  dprintf(server->client_fd, "%s\n", SUCCESS_DELE);
  return (true);
}

bool			help_fct(t_connect *server, t_handler *control)
{
  int			i;
  static t_command_tab	*fct = NULL;

  if (fct == NULL)
    {
      if ((fct = malloc(sizeof(*fct))) == NULL)
	handle_error_sys("Malloc Failed");
      initialise_cmd(fct);
    }
  i = 0;
  (void)control;
  dprintf(server->client_fd, "214-The following commands are recognized.\n");
  while (i < NBR_CMD)
    {
      dprintf(server->client_fd, " %s", fct->cmd[i]);
      if (i % 14 == 0 && i != 0)
	dprintf(server->client_fd, "\n");
      i++;
    }
  if (i % 14 != 0)
    dprintf(server->client_fd, "\n");
  dprintf(server->client_fd, "214 Help OK.\n");
  return (true);
}

bool            noop_fct(t_connect *server, t_handler *control)
{
  (void)control;
  dprintf(server->client_fd, "%s\n", SUCCESS_NOOP);
  return (true);
}
