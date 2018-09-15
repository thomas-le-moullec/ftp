/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Thu May 18 13:44:45 2017 Thomas LE MOULLEC
** Last update Sat May 20 20:24:03 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

void		*free_tab(char **tab)
{
  int		x;

  x = 0;
  if (tab != NULL)
    {
      while (tab[x] != NULL)
	free(tab[x++]);
      free(tab);
    }
  return (NULL);
}

void            *my_free(void *ptr)
{
  if (ptr != NULL)
    free(ptr);
  return (NULL);
}
