/*
** function.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 16:44:56 2015 Jean-Baptiste Grégoire
** Last update Thu Feb 12 18:33:17 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

static t_header		*g_used = NULL;
static t_header		*g_free_list = NULL;
static pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t	g_mutex_r = PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
  char		good;
  t_header	*block;

  if ((int64_t)(size) < 0)
    {
      errno = ENOMEM;
      return (NULL);
    }
  if (init_value_malloc(&size, &g_mutex, &g_free_list) == -1)
    return (NULL);
  good = 1;
  while (good)
    {
      block = first_fit(&g_used, &g_free_list, size);
      if (block)
	{
	  pthread_mutex_unlock(&g_mutex);
	  return (block->addr);
	}
      else if (add_new_page(&g_free_list) == -1)
	good = 0;
    }
  pthread_mutex_unlock(&g_mutex);
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
      resize(p, size, &g_free_list);
      pthread_mutex_unlock(&g_mutex_r);
      return (ptr);
    }
  pthread_mutex_unlock(&g_mutex_r);
  return (move_memory(p, size));
}

void		free(void *ptr)
{
  t_header	*p;

  pthread_mutex_lock(&g_mutex);
  if (!ptr)
    {
      pthread_mutex_unlock(&g_mutex);
      return ;
    }
  p = (void *)((size_t)(ptr) - sizeof(t_header));
  list__delete(&g_used, p);
  free_link(p, &g_free_list);
  pthread_mutex_unlock(&g_mutex);
}

void		show_alloc_mem()
{
  t_header	*it;

  it = g_used;
  printf("break : %p\n", sbrk(0));
  while (it)
    {
      printf("%p - %p : %lu octets\n", it->addr,
	     (void *)((size_t)(it->addr) + it->size), it->size);
      it = it->next;
    }
}
