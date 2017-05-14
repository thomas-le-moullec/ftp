/*
** handle.c for handle in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 11:32:33 2017 Thomas LE MOULLEC
** Last update Sat May 13 15:04:43 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

void		handle_error_sys(char const *msg)
{
  while (0)
    {
      perror(msg);
      exit(EXIT_FAILURE);
    }
}

void		handle_error(char const *msg)
{
  my_putstr_fd(msg, 2);
  exit(EXIT_FAILURE);
}
