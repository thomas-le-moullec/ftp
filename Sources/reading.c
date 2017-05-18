/*
** reading.c for reading in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu May 18 11:17:06 2017 Thomas LE MOULLEC
** Last update Thu May 18 11:18:18 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char            *client_read(int client_fd)
{
  char          *buffer;
  int           size;

  if ((buffer = malloc(sizeof(*buffer) * 1024)) == NULL)
    handle_error_sys("Malloc Failed");
  if ((size = read(client_fd, buffer, 1024)) <= 0)
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
