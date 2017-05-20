/*
** my_str_to_wordtab.c for str in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 20 19:48:33 2017 Thomas LE MOULLEC
** Last update Sat May 20 19:54:45 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char		**my_str_to_wordtab(char *str, char c)
{
  char		**tab;
  int		i;
  int		x;
  int		y;

  tab = NULL;
  y = 0;
  tab = malloc(sizeof(char *) * (strlen(str) + 1));
  i = 0;
  while (str[i] != '\0')
    {
      x = 0;
      tab[y] = NULL;
      tab[y] = malloc(sizeof(char) * (strlen(str) + 1));
      while (str[i] == c)
	i++;
      while (str[i] != '\0' && str[i] != c)
	tab[y][x++] = str[i++];
      if (str[i] != c)
	{
	  free(tab[y]);
	  tab[y] = NULL;
	  return (tab);
	}
      if (str[i] != '\0')
	i++;
      tab[y++][x] = 0;
    }
  tab[y] = NULL;
  return (tab);
}
