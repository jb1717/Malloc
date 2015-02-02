/*
** function.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 16:44:56 2015 Jean-Baptiste Grégoire
** Last update Mon Feb  2 10:20:51 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

static t_header *_used = NULL;
static t_header *_free = NULL;

void		free(void *ptr)
{
  t_header	*p;
  t_header	*it;

  if (!ptr)
    return ;
  p = (void *)((size_t)(ptr) - sizeof(t_header));
  list__delete(&_used, p);
  it = _free;
  while (it)
    {
      if ((void *)((size_t)(it->addr) + it->size) == p)
	{
	  merge_free_space(&_free, it, p, RIGHT);
	  return ;
	}
      if ((void *)((size_t)(p->addr) + p->size) == it)
	{
	  merge_free_space(&_free, it, p, LEFT);
	  return ;
	}
      it = it->next;
    }
  list__add(&_free, p);
}

void		*realloc(void *ptr, size_t size)
{
  t_header	*p;
  t_header	*new_free;

  if (!ptr)
    return (malloc(size));
  if (size == 0)
    free(ptr);
  p = (void *)((size_t)(ptr) - sizeof(t_header));
  if (p->size == size)
    return (ptr);
  else if ((p->size > size) && (p->size - size > sizeof(t_header)))
    {
      new_free = ((void *)(size_t)(p->addr) + size);
      new_free->size = p->size - size - sizeof(t_header);
      new_free->addr = (void *)((size_t)(new_free) + sizeof(t_header));
      new_free->next = NULL;
      list__add(&_free, new_free);
      p->size = size;
      return (ptr);
    }
  else
    return (move_memory(&_used, p, size));
}

void		*malloc(size_t size)
{
  char		good;
  t_header	*block;

  if (!_free)
    malloc_init(&_free);
  good = 1;
  while (good)
    {
      block = first_fit(&_used, &_free, size);
      if (block)
	return (block->addr);
      else
	{
	  if (add_new_page(&_free) == -1)
	    good = 0;
	}
    }
  return (NULL);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if (nmemb == 0 || size == 0)
    return (NULL);
  if ((ptr = malloc(nmemb * size)) == NULL)
    return (NULL);
  bzero(ptr, nmemb * size);
  return (ptr);
}
