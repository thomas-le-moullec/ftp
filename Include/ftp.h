/*
** ftp.h for ftp in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 11:37:16 2017 Thomas LE MOULLEC
** Last update Sun May 14 21:55:32 2017 Thomas LE MOULLEC
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define CRLF1 '\n'
#define CRLF2 '\r'
#define SP1 ' '
#define SP2 '\t'

#define USER "USER"
#define PASSWORD "PASS"

#define PWD "PWD"
#define CDUP "CDUP"
#define CWD "CWD"

#define QUIT "QUIT"
#define HELP "HELP"
#define NOOP "NOOP"
#define DELE "DELE"

#define PASV "PASV"
#define PORT "PORT"
#define RETR "RETR"
#define STOR "STOR"
#define LIST "LIST"

#define NBR_CMD 14

#define WELCOME "Service ready for new user."

#define ERR_AUTH "530 Please login with USER and PASS."
#define ERR_USER "530 Login incorrect."
#define ERR_PASS "332 Need account for login."
#define ALRD_AUTH "530 Can't change from guest user."
#define PASS_FIRST "503 Login with USER first."

#define DEF_USER "Anonymous"
#define DEF_PASS ""

#define ASK_PASS "331 User name okay, need password."
#define SUCCESS_CWD "250 Requested file action okay, completed."
#define SUCCESS_DELE "250 Requested file action okay, completed."
#define SUCCESS_CDUP "200 Command okay."
#define SUCCESS_AUTH "230 User logged in, proceed."
#define SUCCESS_PWD "257 PATHNAME created."
#define SUCCESS_NOOP "200 Command okay."

#define UNKNOWN_CMD "500 Unknown command."

typedef enum
  {
    false,
    true
  } bool;

typedef struct	s_user
{
  const char	*pathUser;
  const char	*userName;
  const char	*passwd;
  bool		is_connected;
}		t_user;

typedef struct	s_connect
{
  int                   fd;
  struct sockaddr_in    s_in;
  int                   port;
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  char                  *client_ip;
  struct protoent       *pe;
  pid_t                 pid;
}		t_connect;

typedef struct	s_client_res
{
  char		*cmd;
  char		*param;
}		t_client_res;

typedef struct	s_handler
{
  t_client_res	client;
  t_user	*user;
}		t_handler;

typedef struct	s_command_tab
{
  char		*cmd[NBR_CMD];
  bool		(*cmd_tab[NBR_CMD])(struct s_connect *, struct s_handler *);
}		t_command_tab;

bool            check_authentification(t_handler *, t_connect *);
void		my_putchar_fd(char, int);
void		my_putstr_fd(char const *, int);
void		handle_error(char const *);
void            handle_error_sys(char const *);
bool		handle_client(struct s_connect *, t_handler *);
void            initialise_connection(struct s_connect *);
bool            run_server(struct s_connect *, t_handler *);
bool            parent_server(int);
char            *client_read(int);
void            initialise_cmd(t_command_tab *);
int             get_param(char *, t_handler *, int);
void            init_cmd_fct(t_command_tab *);
void            init_cmd_order(t_command_tab *);
bool            exec_order(t_handler *, t_connect *);
bool		user_fct(t_connect *, t_handler *);
bool            passwd_fct(t_connect *, t_handler *);
bool            pwd_fct(t_connect *, t_handler *);
bool            cdup_fct(t_connect *, t_handler *);
bool            cwd_fct(t_connect *, t_handler *);
bool		quit_fct(t_connect *, t_handler *);
bool            help_fct(t_connect *, t_handler *);
bool            noop_fct(t_connect *, t_handler *);
bool            pasv_fct(t_connect *, t_handler *);
bool            port_fct(t_connect *, t_handler *);
bool            retr_fct(t_connect *, t_handler *);
bool            stor_fct(t_connect *, t_handler *);
bool            list_fct(t_connect *, t_handler *);
bool            del_fct(t_connect *, t_handler *);
void            initialise_session(t_handler *);
