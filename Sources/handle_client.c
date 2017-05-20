/*
** handle_client.c for handle_client in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 14:54:20 2017 Thomas LE MOULLEC
** Last update Sat May 20 13:39:21 2017 Thomas LE MOULLEC
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
  /*  if (client_res[i] != CRLF1)
    {
      printf("PAS DE CRLF1 !\n");
      return (false);
      }*/
  return (true);
}

bool		get_order(t_handler *control, char *client_res)
{
  int		i;

  i = 0;
  //  printf("client_res in get Order =>...%s...\n", client_res);
  if ((control->client.cmd = malloc(sizeof(*client_res) * 10000)) == NULL)
    handle_error_sys("Malloc Failed");
  while (client_res[i] != '\0' && client_res[i] != CRLF1 && client_res[i] != CRLF2 && client_res[i] != SP1 && client_res[i] != SP2)
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
  //  printf("CMD =...%s... && PARAM =...%s...\n", control->client.cmd, control->client.param);
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
      if (client_res[i] == '\n')
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
  //  free(first);
  //  free(second);
  str[j] = '\0';
  return (str);
}

bool		handle_client(t_connect *server, t_handler *control)
{
  char		*client_res;
  char		**tokens;
  char		*tmp;
  int		x;
  bool		end;

  end = false;
  client_res = NULL;
  server->client_ip = inet_ntoa(server->s_in_client.sin_addr);
  dprintf(server->client_fd, "%s", WELCOME);
  control->client.param = strdup("");
  tmp = NULL;
  while (end == false)
    {
      x = 0;
      tokens = NULL;
      if ((client_res = client_read(server->client_fd, 1000)) == NULL)
	end = true;
      //      printf("Client response before static=>...%s...\n", client_res);
      if (tmp != NULL && client_res != NULL)
	client_res = my_strcat(tmp, client_res);
      //      printf("Client response after static=>...%s...\n", client_res);
      if (client_res != NULL)
	{
	  if (check_line(client_res) == true)
	    {
	      tokens = my_str_to_wordtab(client_res, "\n");
	      tmp = NULL;
	    }
	  else
	    tmp = strdup(client_res);
	}
      while (tokens != NULL && tokens[x] != NULL)
	{
	  //	  printf("token =>...%s...\n", tokens[x]);
	  if ((get_order(control, tokens[x])) == true)
	    {
	      //      printf("cmd =>...%s... && param => ...%s...\n", control->client.cmd, control->client.param);
	      //	  printf("cmd => ...%s... && param => ...%s...\n", control->client.cmd, control->client.param);
	      //	      printf("cmd =>...%s... && param =>...%s...\n", control->client.cmd, control->client.param);
	      exec_order(control, server);
	      if (strcmp(control->client.cmd, QUIT) == 0)
		end = true;
	      //	  free(client_res);
	      control->client.param = strdup("");
	      control->client.param = NULL;
	      control->client.cmd = NULL;
	    }
	  //	  free(tokens[x]);
	    //printf("token =...%s...\n", tokens[x]);
	  x++;
	}
    }
  //  if (tokens != NULL)
  //free(tokens);
  if (close(server->client_fd) == -1)
    return (false);
  return (true);
}
