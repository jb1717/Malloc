##
## Makefile for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
## 
## Made by Jean-Baptiste Grégoire
## Login   <gregoi_j@epitech.net>
## 
## Started on  Thu Jan 29 11:23:28 2015 Jean-Baptiste Grégoire
## Last update Sun Feb  1 19:43:48 2015 Jean-Baptiste Grégoire
##

DEBUG		= yes

SHARED_LIB_NAME	= libmy_malloc_$(HOSTTYPE).so

LIB_NAME	= libmy_malloc.so

SRC		= src/function.c	\
		  src/algorithm.c	\
		  src/list.c		\
		  src/utils.c

OBJ		= $(SRC:.c=.o)

RM		= rm -f

CC		= gcc

INCLUDE 	= includes/

CFLAGS		= -W -Wall -Wextra -fPIC  -I $(INCLUDE)

LIB		= -pthread

ifeq ($(DEBUG),yes)
	CFLAGS 	+= -g3
else
	CFLAGS	+= -O2
endif

$(SHARED_LIB_NAME):	$(OBJ)
		$(CC) -shared -o $(SHARED_LIB_NAME) $(OBJ) $(LIB)
		export LD_PRELOAD=$(SHARED_LID_NAME)
		# ln -s $(SHARED_LIB_NAME) $(LIB_NAME)

all:		$(SHARED_LIB_NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(SHARED_LIB_NAME)

re:		fclean all

.PHNOY:		re fclean clean all
