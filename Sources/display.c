/*
** display.c for display in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 11:34:48 2017 Thomas LE MOULLEC
** Last update Sat May 13 13:22:41 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

void		my_putchar_fd(char c, int fd)
{
  if (write(fd, &c, 1) == -1)
    exit(EXIT_FAILURE);
}

void		my_putstr_fd(char const *str, int fd)
{
  unsigned int i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar_fd(str[i], fd);
      i++;
    }
}
