/*
** function.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Sun Feb  1 16:44:56 2015 Jean-Baptiste Grégoire
** Last update Mon Feb  9 13:41:46 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

t_header	*g_used = NULL;
t_header	*g_free = NULL;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
  char		good;
  t_header	*block;

  printf("MALLOC %lu\n", size);
  if ((int64_t)(size) < 0)
    {
      errno = ENOMEM;
      return (NULL);
    }
  if (size % REG_SIZE != 0)
    size += REG_SIZE - (size % REG_SIZE);
  pthread_mutex_lock(&g_mutex);
  if (!g_free)
    malloc_init(&g_free);
  good = 1;
  while (good)
    {
      block = first_fit(&g_used, &g_free, size);
      if (block)
	{
	  pthread_mutex_unlock(&g_mutex);
	  printf("FIN MALLOC\n");
	  return (block->addr);
	}
      else if (add_new_page(&g_free) == -1)
	good = 0;
    }
  pthread_mutex_unlock(&g_mutex);
  printf("FIN MALLOC\n");
  return (NULL);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  printf("CALLOC\n");
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

  it = g_used;
  printf("break : %p\n", sbrk(0));
  while (it)
    {
      printf("%p - %p : %lu octets\n", it->addr,
	     (void *)((size_t)(it->addr) + it->size), it->size);
      it = it->next;
    }
}
