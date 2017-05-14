/*
** server.c for server in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 13:39:39 2017 Thomas LE MOULLEC
** Last update Sun May 14 10:47:14 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            parent_server(int client_fd)
{
  if (close(client_fd) == -1)
    return (false);
  return (true);
}

bool			run_server(t_connect *server, t_handler *control)
{
  while (1)
    {
      if ((server->client_fd = accept(server->fd, (struct sockaddr *)&server->s_in_client, &server->s_in_size)) == -1)
	{
	  close(server->fd);
	  handle_error_sys("Accept failed");
	}
      server->pid = fork();
      if (server->pid == 0)
	if (handle_client(server, control) == false)
	  return (false);
      if (server->pid > 0)
	  if (parent_server(server->client_fd) == false)
	    return (false);
      if (server->pid < 0)
	  handle_error_sys("Fork Failed");
    }
  return (true);
}
