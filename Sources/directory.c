/*
** directory.c for directory in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun May 14 14:15:54 2017 Thomas LE MOULLEC
** Last update Sun May 14 14:29:20 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool            cwd_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("CWD\n");
  return (true);
}

bool            cdup_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("CDUP\n");
  return (true);
}

bool            pwd_fct(t_connect *server, t_handler *control)
{
  (void)control;
  (void)server;
  printf("PWD\n");
  return (true);
}

