/*
** list.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 15:27:08 2015 Jean-Baptiste Grégoire
** Last update Mon Feb  9 22:28:13 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

void		list__add(t_header **list, t_header *elem)
{
  t_header	*it;
  t_header	*save;
  char		stop;

  if (*list == NULL)
    {
      elem->next = *list;
      *list = elem;
      return ;
    }
  stop = 1;
  it = *list;
  while (it && stop)
    {
      if (it->next && it->next->addr < elem->addr)
  	it = it->next;
      else
  	stop = 0;
    }
  save = it->next;
  it->next = elem;
  elem->next = save;
}

void		list__delete(t_header **list, t_header *elem)
{
  t_header	*it;
  t_header	*prev;

  if (!(*list))
    return ;
  it = *list;
  prev = it;
  while (it)
    {
      if (it == elem)
	{
	  if (prev != it)
	    prev->next = prev->next->next;
	  else
	    *list = (*list)->next;
	  it->next = NULL;
	  return ;
	}
      if (it != *list)
	prev = prev->next;
      it = it->next;
    }
}
