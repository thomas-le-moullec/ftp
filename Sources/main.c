/*
** main.c for main in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 13:11:23 2017 Thomas LE MOULLEC
** Last update Sun May 14 16:16:47 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

int		main(int ac, char **av)
{
  t_connect	*server;
  t_handler	*control;

  if (ac != 3)
    handle_error("Usage : ./server port path\n");
  if ((server = malloc(sizeof(*server))) == NULL || \
      (control = malloc(sizeof(*control))) == NULL)
    handle_error_sys("Malloc Failed");
  server->port = atoi(av[1]);
  control->user.pathUser = av[2];
  initialise_connection(server);
  run_server(server, control);
  return (0);
}
