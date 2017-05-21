/*
** basics.c for basics in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:45:08 2017 Thomas LE MOULLEC
** Last update Sun May 21 10:43:42 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            quit_fct(t_connect *server, t_handler *control)
{
  (void)control;
  dprintf(server->client_fd, "%s", SUCCESS_QUIT);
  return (true);
}

bool            del_fct(t_connect *server, t_handler *control)
{
  if (remove(control->client.param) == -1)
    {
      handle_error_sys(control->client.param);
      return (false);
    }
  dprintf(server->client_fd, "%s", SUCCESS_DELE);
  return (true);
}

bool			help_fct(t_connect *server, t_handler *control)
{
  (void)control;
  dprintf(server->client_fd, "%s", SUCCESS_HELP);
  return (true);
}

bool            noop_fct(t_connect *server, t_handler *control)
{
  (void)control;
  dprintf(server->client_fd, "%s", SUCCESS_NOOP);
  return (true);
}
