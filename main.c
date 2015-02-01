/*
** main.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Fri Jan 30 19:35:34 2015 Jean-Baptiste Grégoire
** Last update Sun Feb  1 13:15:49 2015 Jean-Baptiste Grégoire
*/

#include <stdio.h>
#include "malloc.h"

int	main(void)
{
  char	*toto;
  int	i = 0;

  while (i < 10000)
    {
      toto = malloc(100);
      free(toto);
      i++;
    }
  return (0);
}
