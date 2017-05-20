/*
** handle_client.c for handle_client in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 14:54:20 2017 Thomas LE MOULLEC
** Last update Sat May 20 19:47:22 2017 Thomas LE MOULLEC
*/

#include "ftp.h"

bool		get_param(char *client_res, t_handler *control, int i)
{
  int		j;

  j = 0;
  if (client_res[i] == CRLF1)
    {
      control->client.param = strdup("");
      return (true);
    }
  control->client.param = malloc(sizeof(*control->client.param) * \
				 (strlen(client_res) + 1));
  while (client_res[i] != '\0' && client_res[i] != CRLF1 && client_res[i] != CRLF2)
    {
      if (control->client.param[j] != SP1 && control->client.param[j] != SP2)
	{
	  control->client.param[j] = client_res[i];
	  j++;
	}
      i++;
    }
  control->client.param[j] = '\0';
  return (true);
}

bool		get_order(t_handler *control, char *client_res)
{
  int		i;

  i = 0;
  if ((control->client.cmd = malloc(sizeof(*client_res) * 10000)) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1 && client_res[i] != SP1 && client_res[i] != SP2)
    {
      control->client.cmd[i] = tolower(client_res[i]);
      i++;
    }
  control->client.cmd[i] = '\0';
  if (i == 0 && client_res[i] == CRLF1)
    return (false);
  while (client_res[i] == SP1 || client_res[i] == SP2)
    i++;
  return (get_param(client_res, control, i));
}

bool			exec_order(t_handler *control, t_connect *server)
{
  int			i;
  static t_command_tab *fct = NULL;

  i = 0;
  if (fct == NULL)
    {
      if ((fct = malloc(sizeof(*fct))) == NULL)
	handle_error_sys("Malloc Failed");
      initialise_cmd(fct);
    }
  if (check_authentification(control, server) == false)
    return (false);
  while (i < NBR_CMD)
    {
      if (strcmp(control->client.cmd, fct->cmd[i]) == 0)
	return ((fct->cmd_tab[i])(server, control));
      i++;
    }
  dprintf(server->client_fd, "%s", UNKNOWN_CMD);
  return (false);
}

bool		check_line(char *client_res)
{
  int		i;

  i = 0;
  while (client_res[i] != '\0')
    {
      if (client_res[i] == CRLF2)
	return (true);
      i++;
    }
  return (false);
}

char		*my_strcat(char *first, char *second)
{
  int		i;
  int		j;
  char		*str;

  i = 0;
  j = 0;
  str = malloc(sizeof(*str) * (strlen(first) + strlen(second) + 1));
  while (first[i] != '\0')
    str[j++] = first[i++];
  i = 0;
  while (second[i] != '\0')
    str[j++] = second[i++];
  str[j] = '\0';
  return (str);
}

bool		handle_client(t_connect *server, t_handler *control)
{
  char		*client_res;
  char		**tokens;
  int		x;
  bool		end;

  end = false;
  client_res = NULL;
  server->client_ip = inet_ntoa(server->s_in_client.sin_addr);
  dprintf(server->client_fd, "%s", WELCOME);
  control->client.param = strdup("");
  while (end == false)
    {
      x = 0;
      tokens = NULL;
      client_res = client_read(server->client_fd, 10000);
      if (client_res == NULL)
	end = true;
      if (end == false)
	{
	  tokens = my_str_to_wordtab(client_res, CRLF2);
	  while (tokens != NULL && tokens[x] != NULL)
	    {
	      if ((get_order(control, tokens[x])) == true)
		{
		  exec_order(control, server);
		  if (strcmp(control->client.cmd, QUIT) == 0)
		    end = true;
		  control->client.param = strdup("");
		  control->client.param = NULL;
		  control->client.cmd = NULL;
		}
	      x++;
	    }
	  x = 0;
	  if (tokens != NULL)
	    {
	      while (tokens[x] != NULL)
		free(tokens[x++]);
	      free(tokens);
	    }
	}
    }
  if (close(server->client_fd) == -1)
    return (false);
  return (true);
}
