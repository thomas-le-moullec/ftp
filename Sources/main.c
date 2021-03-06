/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Sat May 13 13:11:23 2017 Thomas LE MOULLEC
** Last update Thu May 18 17:37:06 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

int		main(int ac, char **av)
{
  t_connect	*server;
  t_handler	*control;

  server = NULL;
  control = NULL;
  if (ac != 3)
    handle_error("Usage : ./server port path\n");
  if ((server = malloc(sizeof(*server))) == NULL || \
      (control = malloc(sizeof(*control))) == NULL)
    handle_error_sys("Malloc Failed");
  server->port = atoi(av[1]);
  if ((control->user = malloc(sizeof(*control->user))) == NULL)
    handle_error_sys("Malloc Failed");
  initialise_connection(server);
  initialise_session(control);
  control->user->pathUser = av[2];
  run_server(server, control);
  free(control);
  free(server);
  return (0);
}
