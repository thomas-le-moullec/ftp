/*
** reading.c for reading in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu May 18 11:17:06 2017 Thomas LE MOULLEC
** Last update Sun May 21 12:02:36 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char            *client_read(int client_fd, int octets)
{
  char          *buffer;
  int           size;

  if ((buffer = malloc(sizeof(*buffer) * octets)) == NULL)
    handle_error_sys("Malloc Failed");
  if ((size = read(client_fd, buffer, octets)) <= 0)
    return (NULL);
  buffer[size] = '\0';
  return (buffer);
}

bool            check_end_order_retr(char *client_res, bool end,
				     int fd, int client_fd)
{
  if (client_res == NULL)
    {
      end = true;
      close(fd);
      close(client_fd);
    }
  if (end == false)
    dprintf(client_fd, "%s", client_res);
  return (end);
}

bool            check_end_order_stor(char *client_res, bool end,
				     int fd, int client_fd)
{
  if (client_res == NULL)
    {
      end = true;
      close(fd);
      close(client_fd);
    }
  if (end == false)
    dprintf(fd, "%s", client_res);
  return (end);
}

bool		check_tokens(char **tokens, int fd)
{
  int		x;

  x = 0;
  if (tokens == NULL)
    {
      dprintf(fd, "530 Error PORT Connect\r\n");
      return (false);
    }
  while (tokens[x] != NULL)
    x++;
  if (x != 6)
    {
      dprintf(fd, "530 Error PORT Connect\r\n");
      return (false);
    }
  return (true);
}

char		*get_ip(char **tokens, int y, int i)
{
  char		*buf;
  int		size;
  int		x;

  size = strlen(tokens[0]) + strlen(tokens[1]) \
    + strlen(tokens[2]) + strlen(tokens[3]);
  buf = malloc(sizeof(char) * (size + 1));
  while (tokens != NULL && tokens[y] != NULL && y < 4)
    {
      x = 0;
      while (tokens[y][x] != '\0')
	{
	  buf[i] = tokens[y][x];
	  i++;
	  x++;
	}
      if (y != 3)
	buf[i++] = '.';
      y++;
    }
  buf[i] = '\0';
  return (buf);
}
