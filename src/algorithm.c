/*
** algorithm.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 16:12:39 2015 Jean-Baptiste Grégoire
** Last update Mon Feb  2 22:58:19 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

t_header	*first_fit(t_header **used_list, t_header **free_list,
			   size_t size)
{
  t_header	*it;
  t_header	*new;

  it = *free_list;
  while (it)
    {
      if (it->size == size + sizeof(t_header))
	{
	  list__delete(free_list, it);
	  list__add(used_list, it);
	  return (it);
	}
      else if (it->size > size + sizeof(t_header))
	{
	  new = (void *)((size_t)(it->addr) + it->size - size - sizeof(t_header));
	  new->size = size;
	  new->addr = (void *)((size_t)(new) + sizeof(t_header));
	  it->size = it->size - size - sizeof(t_header);
	  list__add(used_list, new);
	  return (new);
	}
      it = it->next;
    }
  return (NULL);
}

t_header	*best_fit(t_header **used_list, t_header **free_list,
			  size_t size)
{
  t_header	*it;
  t_header	*min;

  it = *free_list;
  min = NULL;
  while (it)
    {
      if (!min && size + sizeof(t_header) <= it->size)
	min = it;
      if (min && min->size > it->size)
	min = it;
      it = it->next;
    }
  if (!min)
    return (NULL);
  list__delete(free_list, min);
  list__add(used_list, min);
  return (min);
}
