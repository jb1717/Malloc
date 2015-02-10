/*
** main.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Fri Jan 30 19:35:34 2015 Jean-Baptiste Grégoire
** Last update Tue Feb 10 18:34:16 2015 Jean-Baptiste Grégoire
*/

#include <stdio.h>
#include "malloc.h"

int	main(void)
{
  char *toto;
  char *tutu;
  char *titi;
  char *tete;
  char *tata;

  toto = malloc(10);
  tutu = malloc(10);
  titi = malloc(10);
  tata = malloc(10);
  tete = malloc(10);
  free(tete);
  free(tutu);
  free(titi);
  free(tata);
  free(tete);
  return (0);
}
