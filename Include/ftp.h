/*
** ftp.h for ftp in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat May 13 11:37:16 2017 Thomas LE MOULLEC
** Last update Sat May 20 19:36:33 2017 Thomas LE MOULLEC
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
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

#define READ_SIZE (4096)

#define CRLF1 '\r'
#define CRLF2 '\n'
#define SP1 ' '
#define SP2 '\t'

#define USER "user"
#define PASSWORD "pass"

#define PWD "pwd"
#define CDUP "cdup"
#define CWD "cwd"

#define QUIT "quit"
#define HELP "help"
#define NOOP "noop"
#define DELE "dele"
#define TYPE "type"

#define PASV "pasv"
#define PORT "port"
#define RETR "retr"
#define STOR "stor"
#define LIST "list"

#define LOCALHOST "127.0.0.1"

#define NBR_CMD 15

#define WELCOME "220 Service ready for new user.\r\n"

#define ERR_PASV_ACTIF "425 Use PORT or PASV first.\r\n"
#define ERR_CWD "550 Failed to change directory.\r\n"
#define ERR_AUTH "530 Please login with USER and PASS.\r\n"
#define ERR_USER "530 Login incorrect.\r\n"
#define ERR_PASS "332 Need account for login.\r\n"
#define ALRD_AUTH "530 Can't change from guest user.\r\n"
#define PASS_FIRST "503 Login with USER first.\r\n"

#define DEF_USER "anonymous"
#define DEF_PASS ""

#define ASK_PASS "331 User name okay, need password.\r\n"
#define SUCCESS_CWD "250 Requested file action okay, completed.\r\n"
#define SUCCESS_DELE "250 Requested file action okay, completed.\r\n"
#define SUCCESS_CMD "200 Command okay.\r\n"
#define SUCCESS_CDUP "200 Command okay.\r\n"
#define SUCCESS_AUTH "230 User logged in, proceed.\r\n"
#define SUCCESS_PWD "created.\r\n"
#define SUCCESS_NOOP "200 Command okay.\r\n"
#define SUCCESS_QUIT "221 Quit.\r\n"
#define SUCCESS_HELP "214-The following commands are recognized.\r\n"
#define SUCCESS_HELP2 "214 Help OK.\r\n"
#define SUCCESS_PASV "227 Entering Passive Mode "
#define SUCCESS_DATA "150 File status okay; about to open data connection.\r\n"
#define END_DATA "226 Closing data connection.\r\n"

#define UNKNOWN_CMD "500 Unknown command.\r\n"

typedef struct          s_get
{
  int                   j;
  int                   i;
  int                   a;
  char                  *stock;
  int                   cmpt;
}                       t_get;

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
  int		client_fd;
  bool		pasv;
  bool		activ;
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
char            *client_read(int, int);
void            initialise_cmd(t_command_tab *);
bool            get_param(char *, t_handler *, int);
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
bool            check_end_order_retr(char *, bool, int, int);
bool            check_end_order_stor(char *, bool, int, int);
char            **get_argv_ls(char **, t_handler *);
char            *my_strcar(char *, char);
int             do_it(t_get *, char *, int *);
int             check_static(char *, int *, t_get *);
char            *get_next_line(const int);
void            *my_free(void *);
char            **my_str_to_wordtab(char *, char);
