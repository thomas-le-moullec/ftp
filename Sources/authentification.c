/*
** authentification.c for authentification in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 13:05:17 2017 Thomas LE MOULLEC
** Last update Sun May 14 20:56:07 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		check_authentification(t_handler *control, t_connect *server)
{
  if (control->user->is_connected == false &&		\
      strcmp(control->client.cmd, USER) != 0 &&		\
      strcmp(control->client.cmd, PASSWORD) != 0 &&	\
      strcmp(control->client.cmd, QUIT) != 0)
    {
      dprintf(server->client_fd, "%s\n", ERR_AUTH);
      return (false);
    }
  return (true);
}

bool		passwd_fct(t_connect *server, t_handler *control)
{
  if (control->user->userName == NULL)
    {
      dprintf(server->client_fd, "%s\n", PASS_FIRST);
      return (false);
    }
  if (strcmp(control->client.param, DEF_PASS) != 0)
    {
      dprintf(server->client_fd, "%s\n", ERR_PASS);
      return (false);
    }
  dprintf(server->client_fd, "%s\n", SUCCESS_AUTH);
  control->user->passwd = control->client.param;
  control->user->is_connected = true;
  return (true);
}

bool          user_fct(t_connect *server, t_handler *control)
{
  if (control->user->is_connected == true)
    {
      dprintf(server->client_fd, "%s\n", ALRD_AUTH);
      return (false);
    }
  if (strcmp(control->client.param, DEF_USER) != 0)
    {
      dprintf(server->client_fd, "%s\n", ERR_USER);
      return (false);
    }
  control->user->userName = control->client.param;
  dprintf(server->client_fd, "%s\n", ASK_PASS);
  return (true);
}
