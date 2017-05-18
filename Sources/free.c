/*
** free.c for free in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu May 18 13:44:45 2017 Thomas LE MOULLEC
** Last update Thu May 18 13:44:53 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

void            *my_free(void *ptr)
{
  if (ptr != NULL)
    free(ptr);
  return (NULL);
}
