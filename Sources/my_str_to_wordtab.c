/*
** my_str_to_wordtab.c for str in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 20 19:48:33 2017 Thomas LE MOULLEC
** Last update Sat May 20 20:12:57 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

int		loop_on_char(char *str, int i, char c)
{
  while (str[i] == c)
    i++;
  return (i);
}

char		**my_str_to_wordtab(char *str, char c, int y, int i)
{
  char		**tab;
  int		x;

  tab = NULL;
  tab = malloc(sizeof(char *) * (strlen(str) + 1));
  while (str[i] != '\0')
    {
      x = 0;
      tab[y] = NULL;
      tab[y] = malloc(sizeof(char) * (strlen(str) + 1));
      i = loop_on_char(str, i, c);
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
