/*
** free.c for malloc in /home/patoche/rendu/PSU_2014_malloc/src
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.net>
**
** Started on  Tue Feb  3 23:01:20 2015 Hugo Prenat
** Last update Thu Feb 12 17:35:11 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

void		resize(t_header *p, size_t size, t_header **free_list)
{
  t_header	*new_free;

  new_free = ((void *)(size_t)(p->addr) + size);
  new_free->size = p->size - size - sizeof(t_header);
  new_free->addr = (void *)((size_t)(new_free) + sizeof(t_header));
  new_free->next = NULL;
  list__add(free_list, new_free);
  p->size = size;
}
