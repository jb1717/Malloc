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
t_header	*g_free_list = NULL;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	init_value_malloc(size_t *size)
{
  if (*size % REG_SIZE != 0)
    *size += REG_SIZE - (*size % REG_SIZE);
  pthread_mutex_lock(&g_mutex);
  if (!g_free_list)
    malloc_init(&g_free_list);
}

void		*malloc(size_t size)
{
  char		good;
  t_header	*block;

  if ((int64_t)(size) < 0)
    {
      errno = ENOMEM;
      return (NULL);
    }
  init_value_malloc(&size);
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
