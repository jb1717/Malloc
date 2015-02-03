/*
** function.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 16:44:56 2015 Jean-Baptiste Grégoire
** Last update Tue Feb  3 11:25:11 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

static t_header *g_used = NULL;
static t_header *g_free = NULL;

void		free(void *ptr)
{
  t_header	*p;
  t_header	*it;
  char		is_free;

  if (!ptr)
    return ;
  is_free = 0;
  p = (void *)((size_t)(ptr) - sizeof(t_header));
  list__delete(&g_used, p);
  it = g_free;
  while (it)
    {
      if ((void *)((size_t)(it->addr) + it->size) == p)
	{
	  merge_free_space(&g_free, it, p, RIGHT);
	  is_free = 1;
	}
      if ((void *)((size_t)(p->addr) + p->size) == it)
	{
	  merge_free_space(&g_free, it, p, LEFT);
	  it = p;
	  is_free = 1;
	}
      it = it->next;
    }
  if (!is_free)
    list__add(&g_free, p);
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
      list__add(&g_free, new_free);
      p->size = size;
      return (ptr);
    }
  else
    return (move_memory(p, size));
}

void		*malloc(size_t size)
{
  char		good;
  t_header	*block;

  if (!g_free)
    malloc_init(&g_free);
  good = 1;
  while (good)
    {
      block = first_fit(&g_used, &g_free, size);
      if (block)
	return (block->addr);
      else
	{
	  if (add_new_page(&g_free) == -1)
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

void		show_alloc_mem()
{
  t_header	*it;

  it = g_free;
  printf("break : %p\n", sbrk(0));
  while (it)
    {
      printf("%p - %p : %lu octets\n", it->addr,
	     (void *)((size_t)(it->addr) + it->size), it->size);
      it = it->next;
    }
}
