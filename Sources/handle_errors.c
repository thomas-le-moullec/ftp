/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Sat May 13 11:32:33 2017 Thomas LE MOULLEC
** Last update Sun May 14 22:11:09 2017 Thomas LE MOULLEC
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
