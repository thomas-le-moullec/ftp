/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Sun May 14 13:05:17 2017 Thomas LE MOULLEC
** Last update Tue May 23 18:01:34 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		check_authentification(t_handler *control, t_connect *server)
{
  if (control->user->is_connected == false &&		\
      strcmp(control->client.cmd, USER) != 0 &&		\
      strcmp(control->client.cmd, PASSWORD) != 0 &&	\
      strcmp(control->client.cmd, QUIT) != 0)
    {
      dprintf(server->client_fd, "%s", ERR_AUTH);
      return (false);
    }
  return (true);
}

bool		passwd_fct(t_connect *server, t_handler *control)
{
  if (control->user->userName == NULL)
    {
      dprintf(server->client_fd, "%s", PASS_FIRST);
      return (false);
    }
  if (strcmp(control->user->userName, DEF_USER) != 0)
    {
      dprintf(server->client_fd, "%s", ERR_USER);
      return (false);
    }
  dprintf(server->client_fd, "%s", SUCCESS_AUTH);
  control->user->passwd = control->client.param;
  control->user->is_connected = true;
  chdir(control->user->pathUser);
  return (true);
}

bool          user_fct(t_connect *server, t_handler *control)
{
  int		i;

  i = 0;
  /*  if (control->user->is_connected == true)
    {
      dprintf(server->client_fd, "%s", ALRD_AUTH);
      return (false);
      }*/
  while (control->client.param[i] != '\0')
    {
      control->client.param[i] = tolower(control->client.param[i]);
      i++;
    }
  control->user->userName = control->client.param;
  dprintf(server->client_fd, "%s", ASK_PASS);
  return (true);
}
