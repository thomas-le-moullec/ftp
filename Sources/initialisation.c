/*
** initialisation.c for Initialisation in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 23:49:10 2017 Thomas LE MOULLEC
** Last update Tue May 16 22:06:31 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

void            initialise_connection(t_connect *server)
{
  server->client_ip = NULL;
  server->pe = NULL;
  server->s_in_size = sizeof(server->s_in_client);
  if (!(server->pe = getprotobyname("TCP")))
    handle_error_sys("Error With TCP Protocol");
  if ((server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto)) == -1)
    handle_error_sys("Could not create new socket");
  server->s_in.sin_family = AF_INET;
  server->s_in.sin_port = htons(server->port);
  server->s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(server->fd, (const struct sockaddr *)&server->s_in, \
	   sizeof(server->s_in)) == -1)
    {
      close(server->fd);
      handle_error_sys("Cannot Bind on this port");
    }
  if (listen(server->fd, 42) == -1)
    {
      close(server->fd);
      handle_error_sys("Error on the Listen");
    }
}

void		initialise_session(t_handler *control)
{
  control->client.cmd = NULL;
  control->client.param = "";
  control->user->pathUser = NULL;
  control->user->userName = NULL;
  control->user->passwd = NULL;
  control->user->is_connected = false;
  control->pasv = false;
  control->activ = false;
}

void		init_cmd_fct(t_command_tab *orders)
{
  orders->cmd_tab[0] = &user_fct;
  orders->cmd_tab[1] = &passwd_fct;
  orders->cmd_tab[2] = &pwd_fct;
  orders->cmd_tab[3] = &cdup_fct;
  orders->cmd_tab[4] = &cwd_fct;
  orders->cmd_tab[5] = &quit_fct;
  orders->cmd_tab[6] = &help_fct;
  orders->cmd_tab[7] = &noop_fct;
  orders->cmd_tab[8] = &pasv_fct;
  orders->cmd_tab[9] = &port_fct;
  orders->cmd_tab[10] = &retr_fct;
  orders->cmd_tab[11] = &stor_fct;
  orders->cmd_tab[12] = &list_fct;
  orders->cmd_tab[13] = &del_fct;
}

void		init_cmd_order(t_command_tab *orders)
{
  orders->cmd[0] = USER;
  orders->cmd[1] = PASSWORD;
  orders->cmd[2] = PWD;
  orders->cmd[3] = CDUP;
  orders->cmd[4] = CWD;
  orders->cmd[5] = QUIT;
  orders->cmd[6] = HELP;
  orders->cmd[7] = NOOP;
  orders->cmd[8] = PASV;
  orders->cmd[9] = PORT;
  orders->cmd[10] = RETR;
  orders->cmd[11] = STOR;
  orders->cmd[12] = LIST;
  orders->cmd[13] = DELE;
}

void		initialise_cmd(t_command_tab *orders)
{
  init_cmd_fct(orders);
  init_cmd_order(orders);
}
