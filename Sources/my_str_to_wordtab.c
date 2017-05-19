/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/chabot_t/rendu/PSU/PSU_2015_42sh
** 
** Made by Thomas CHABOT
** Login   <chabot_t@epitech.net>
** 
** Started on  Tue Apr 26 13:58:51 2016 Thomas CHABOT
** Last update Fri May 19 14:24:36 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		check_flags(char c, char *flags)
{
  int		i;

  i = 0;
  while (flags[i] != '\0')
    {
      if (c == flags[i])
	return (true);
      i++;
    }
  return (false);
}

int		count_words(char *str, char *flags)
{
  int		i;
  int		nb_words;

  i = 0;
  nb_words = 1;
  while (str[i] != '\0')
    {
      while (str[i] != '\0' && check_flags(str[i], flags) == true)
	i++;
      while (str[i] != '\0' && check_flags(str[i], flags) == false)
	i++;
      if (str[i] != '\0')
	nb_words++;
    }
  return (nb_words);
}

char		**my_str_to_wordtab(char *str, char *flags)
{
  int		i;
  int		j;
  int		k;
  char		**tabo;

  i = 0;
  k = 0;
  tabo = NULL;
  tabo = malloc((count_words(str, flags) + 1) * sizeof(char *));
  while (str[i] != '\0')
    {
      j = 0;
      tabo[k] = NULL;
      tabo[k] = malloc(sizeof(char) * (strlen(str) + 1));
      while (str[i] != '\0' && check_flags(str[i], flags) == true)
	i++;
      while (str[i] != '\0' && check_flags(str[i], flags) == false)
	tabo[k][j++] = str[i++];
      if (str[i] != '\0')
	i++;
      tabo[k++][j] = '\0';
    }
  tabo[k] = NULL;
  return (tabo);
}
