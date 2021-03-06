##
## Makefile for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
## 
## Made by Jean-Baptiste Grégoire
## Login   <gregoi_j@epitech.net>
## 
## Started on  Thu Jan 29 11:23:28 2015 Jean-Baptiste Grégoire
## Last update Mon Feb  9 22:55:02 2015 Jean-Baptiste Grégoire
##

DEBUG		= 	no

SHARED_LIB_NAME	=	libmy_malloc_$(HOSTTYPE).so

LIB_NAME	=	libmy_malloc.so

SRC		=	src/function.c	\
			src/algorithm.c	\
			src/list.c	\
			src/free.c	\
			src/realloc.c	\
			src/utils.c

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

CC		=	gcc

INCLUDES	=	includes/

CFLAGS		=	-W -Wall -Wextra -fPIC -I $(INCLUDES)

ifeq ($(DEBUG),yes)
	CFLAGS 	+= -g3
else
	CFLAGS	+= -O3
endif

$(SHARED_LIB_NAME):	$(OBJ)
		$(CC) -shared -o $(SHARED_LIB_NAME) $(OBJ)
		ln -fs $(SHARED_LIB_NAME) $(LIB_NAME)

all:		$(SHARED_LIB_NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(SHARED_LIB_NAME)

re:		fclean all

.PHNOY:		re fclean clean all
