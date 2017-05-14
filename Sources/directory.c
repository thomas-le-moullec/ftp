/*
** directory.c for directory in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:15:54 2017 Thomas LE MOULLEC
** Last update Sun May 14 22:17:43 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            cwd_fct(t_connect *server, t_handler *control)
{
  if (strcmp(control->client.param, "~") == 0 || \
      strcmp(control->client.param, "$HOME") == 0)
    {
      if (chdir(control->user->pathUser) == -1)
	handle_error_sys(control->user->pathUser);
    }
  else
    {
      if (chdir(control->client.param) == -1)
	handle_error_sys(control->client.param);
    }
  if (chdir(control->client.param) == -1)
    handle_error_sys(control->client.param);
  dprintf(server->client_fd, "%s\n", SUCCESS_CWD);
  return (true);
}

bool            cdup_fct(t_connect *server, t_handler *control)
{
  (void)control;
  if (chdir("../") == -1)
    handle_error_sys("../");
  dprintf(server->client_fd, "%s\n", SUCCESS_CDUP);
  return (true);
}

bool            pwd_fct(t_connect *server, t_handler *control)
{
  char		cwd[1024];

  (void)control;
  if (getcwd(cwd, sizeof(cwd)) == NULL)
    handle_error_sys("getcwd failed");
  dprintf(server->client_fd, "%s\n", cwd);
  dprintf(server->client_fd, "%s\n", SUCCESS_PWD);
  return (true);
}

