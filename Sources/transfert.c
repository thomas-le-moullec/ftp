/*
** transfert.c for transfert in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp/Sources
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:47:04 2017 Thomas LE MOULLEC
** Last update Sun May 14 14:48:08 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            pasv_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("PASV\n");
  return (true);
}

bool            port_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("PORT\n");
  return (true);
}

bool            retr_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("RETR\n");
  return (true);
}

bool            stor_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("STOR\n");
  return (true);
}

bool            list_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("LIST\n");
  return (true);
}
