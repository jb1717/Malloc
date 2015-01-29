##
## Makefile for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
## 
## Made by Jean-Baptiste Grégoire
## Login   <gregoi_j@epitech.net>
## 
## Started on  Thu Jan 29 11:23:28 2015 Jean-Baptiste Grégoire
## Last update Thu Jan 29 11:48:02 2015 Jean-Baptiste Grégoire
##

SHARED_LIB_NAME	=	libmy_malloc_$(HOSTTYPE).so

LIB_NAME	=	libmy_malloc.so

SRC		=	malloc.c

OBJ		=	$(SRC:.c=.o)

CLFAGS		=	-W -Wall -Wextra

CC		=	gcc

RM		=	rm -f

$(SHARED_LIB_NAME):	$(OBJ)
		$(CC) -shared -o $(SHARED_LIB_NAME) $(OBJ)
		export LD_PRELOAD=$(PWD)/$(SHARED_LIB_NAME)
		ln -s $(SHARED_LIB_NAME) $(LIB_NAME)

all:		$(SHARED_LIB_NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(SHARED_LIB_NAME)

re:		fclean all

.PHNOY:		re fclean clean all
