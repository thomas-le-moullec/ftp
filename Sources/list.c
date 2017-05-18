/*
** list.c for list in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu May 18 12:36:17 2017 Thomas LE MOULLEC
** Last update Thu May 18 14:15:05 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

char            **get_argv_ls(char **av, t_handler *control)
{
  av[0] = strdup("/bin/ls");
  av[1] = strdup("-l");
  if (strcmp(control->client.param, "") != 0)
    av[2] = strdup(control->client.param);
  else
    av[2] = NULL;
  av[3] = NULL;
  return (av);
}

bool            list_fct(t_connect *server, t_handler *control)
{
  char          **av;
  pid_t         pid;
  int           status;

  if (control->pasv == false && control->activ == false)
    {
      dprintf(server->client_fd, "%s", ERR_PASV_ACTIF);
      return (false);
    }
  dprintf(server->client_fd, "%s", SUCCESS_DATA);
  pid = fork();
  if ((av = malloc(sizeof(char *) * 4)) == NULL)
    handle_error_sys("Malloc Failed");
  av = get_argv_ls(av, control);
  if (pid == 0)
    {
      dup2(control->client_fd, 1);
      execve("/bin/ls", av, NULL);
    }
  else
    waitpid(pid, &status, WUNTRACED | WCONTINUED);
  close(control->client_fd);
  dprintf(server->client_fd, "%s", END_DATA);
  return (true);
}
