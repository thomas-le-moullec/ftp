##
## Makefile for Makefile in /home/le-mou_t/rendu/TEK2/C/PSU_2016_myftp
## 
## Made by Thomas LE MOULLEC
## Login   <le-mou_t@epitech.net>
## 
## Started on  Sat May 13 11:39:49 2017 Thomas LE MOULLEC
## Last update Sat May 20 20:23:53 2017 Thomas LE MOULLEC
##

CC		= gcc

NAME		= server

RM		= rm -rf

IFLAGS		= -I./Include/

CFLAGS		= -W -Wall -Wextra $(IFLAGS)

SRCSPATH	= ./Sources/

SRCS		= $(SRCSPATH)main.c		\
	  	$(SRCSPATH)handle_errors.c	\
	  	$(SRCSPATH)handle_client.c	\
	  	$(SRCSPATH)display.c		\
		$(SRCSPATH)server.c		\
		$(SRCSPATH)initialisation.c	\
		$(SRCSPATH)authentification.c	\
		$(SRCSPATH)directory.c		\
		$(SRCSPATH)basics.c		\
		$(SRCSPATH)transfert.c		\
		$(SRCSPATH)reading.c		\
		$(SRCSPATH)list.c		\
		$(SRCSPATH)free.c		\
		$(SRCSPATH)my_str_to_wordtab.c	\

OBJS		= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
