/*
** get_next_line.c for get_next_line.c in /home/le-mou_t/rendu/CPE_2015_getnextline
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Mon May 30 13:20:44 2016 Thomas LE MOULLEC
** Last update Sat May 20 18:58:15 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char		*my_strcar(char *str, char c)
{
  int		i;
  char		*stock;

  i = 0;
  while (str[i] != '\0')
    i++;
  if ((stock = malloc(sizeof(char) * (i + 2))) == NULL)
    return (NULL);
  i = 0;
  while (str[i] != '\0')
    {
      stock[i] = str[i];
      i++;
    }
  str = my_free(str);
  stock[i] = c;
  i++;
  stock[i] = '\0';
  return (stock);
}

int		do_it(t_get *get, char *buffer, int *ptr)
{
  int		j;

  j = 0;
  while (buffer[j] != '\0' && get->a == 0 && j != READ_SIZE)
    {
      if (buffer[j] == '\n')
	{
	  get->a = 1;
	  *ptr = j;
	}
      j++;
    }
  j = 0;
  if (get->a == 0)
    while (j != READ_SIZE && buffer[j] != '\0')
      get->stock = my_strcar(get->stock, buffer[j++]);
  if (get->a == 1)
    {
      while (j != *ptr && buffer[j] != '\0')
	get->stock = my_strcar(get->stock, buffer[j++]);
      *ptr = j + 1;
      return (-1);
    }
  return (0);
}

int		check_static(char *buffer, int *ptr, t_get *get)
{
  get->i = 0;
  get->a = 0;
  if ((get->stock = malloc(sizeof(*get->stock))) == NULL)
    return (1);
  *(get->stock) = '\0';
  while (buffer[*ptr] != '\0')
    {
      if (buffer[*ptr] == '\n')
	{
	  *ptr = *ptr + 1;
	  return (1);
	}
      get->stock = my_strcar(get->stock, buffer[*ptr]);
      *ptr = *ptr + 1;
    }
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	buffer[READ_SIZE + 1];
  static int	ptr = 0;
  t_get	get;

  if ((check_static(buffer, &ptr, &get)) == 1)
    return (get.stock);
  while (get.a == 0)
    {
      if ((get.cmpt = read(fd, buffer, READ_SIZE)) <= 0)
	{
	  buffer[get.cmpt] = '\0';
	  if (get.stock != NULL && get.stock[0] != '\0')
	    return (get.stock);
	  return (NULL);
	}
      buffer[get.cmpt] = '\0';
      if (get.cmpt != READ_SIZE && buffer[get.cmpt - 1] != '\n')
	{
	  buffer[get.cmpt] = '\n';
	  buffer[get.cmpt + 1] = '\0';
	}
      if (!(ptr = 0) && (do_it(&get, buffer, &ptr)) == -1)
	return (get.stock);
    }
  return (NULL);
}
