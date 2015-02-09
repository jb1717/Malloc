/*
** free.c for malloc in /home/patoche/rendu/PSU_2014_malloc/src
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.net>
**
** Started on  Tue Feb  3 23:01:20 2015 Hugo Prenat
** Last update Mon Feb  9 23:48:10 2015 Hugo Prenat
*/

#include "malloc.h"

extern t_header	*g_free_list;
pthread_mutex_t	g_mutex_r = PTHREAD_MUTEX_INITIALIZER;

void		resize(t_header *p, size_t size)
{
  t_header	*new_free;

  new_free = ((void *)(size_t)(p->addr) + size);
  new_free->size = p->size - size - sizeof(t_header);
  new_free->addr = (void *)((size_t)(new_free) + sizeof(t_header));
  new_free->next = NULL;
  list__add(&g_free_list, new_free);
  p->size = size;
}

void		*realloc(void *ptr, size_t size)
{
  t_header	*p;

  if (!ptr)
    return (malloc(size));
  if (size == 0)
    {
      free(ptr);
      return (NULL);
    }
  pthread_mutex_lock(&g_mutex_r);
  p = (void *)((size_t)(ptr) - sizeof(t_header));
  if (p->size == size)
    {
      pthread_mutex_unlock(&g_mutex_r);
      return (ptr);
    }
  else if ((p->size > size) && (p->size - size > sizeof(t_header)))
    {
      resize(p, size);
      pthread_mutex_unlock(&g_mutex_r);
      return (ptr);
    }
  pthread_mutex_unlock(&g_mutex_r);
  return (move_memory(p, size));
}
