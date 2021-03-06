/*
** free.c for malloc in /home/patoche/rendu/PSU_2014_malloc/src
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.net>
**
** Started on  Tue Feb  3 23:01:20 2015 Hugo Prenat
** Last update Thu Feb 12 18:50:43 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

void		merge_free_space(t_header **free_list, t_header *block1,
				 t_header *block2, enum e_move side)
{
  if (side == RIGHT)
    block1->size = block1->size + block2->size + sizeof(t_header);
  if (side == LEFT)
    {
      list__delete(free_list, block1);
      block2->size = block2->size + block1->size + sizeof(t_header);
      list__delete(free_list, block2);
      list__add(free_list, block2);
    }
}

void		free_link(t_header *p, t_header **free_list)
{
  t_header	*it;
  char		is_free;

  is_free = 0;
  it = *free_list;
  while (it)
    {
      if ((void *)((size_t)(it->addr) + it->size) == p)
      	{
      	  merge_free_space(free_list, it, p, RIGHT);
      	  is_free = 1;
	  p = it;
      	}
      if ((void *)((size_t)(p->addr) + p->size) == it)
      	{
      	  merge_free_space(free_list, it, p, LEFT);
      	  it = p;
      	  is_free = 1;
      	}
      it = it->next;
    }
  if (!is_free)
    list__add(free_list, p);
}
