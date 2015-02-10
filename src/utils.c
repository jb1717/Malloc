/*
** utils.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
**
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
**
** Started on  Sun Feb  1 16:50:37 2015 Jean-Baptiste Grégoire
** Last update Tue Feb 10 21:20:50 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

int		malloc_init(t_header **free_list)
{
  if ((*free_list = sbrk(21 * MALLOC_PAGE_SIZE)) == (void *)(-1))
    {
      perror("malloc_init");
      return (-1);
    }
  (*free_list)->size = 21 * MALLOC_PAGE_SIZE - sizeof(t_header);
  (*free_list)->addr = (void *)((size_t)(*free_list) + sizeof(t_header));
  (*free_list)->next = NULL;
  return (0);
}

int		add_new_page(t_header **free_list)
{
  t_header	*new_page;
  t_header	*it;

  if ((new_page = sbrk(21 * MALLOC_PAGE_SIZE))
      == (void *)(-1))
    {
      perror("add_new_page");
      return (-1);
    }
  it = *free_list;
  while (it)
    {
      if ((void *)((size_t)(it->addr) + it->size) == new_page)
	{
	  it->size = it->size + (21 * MALLOC_PAGE_SIZE);
	  return (0);
	}
      it = it->next;
    }
  new_page->addr = (void *)((size_t)(new_page) + sizeof(t_header));
  new_page->size = 21 * MALLOC_PAGE_SIZE - sizeof(t_header);
  new_page->next = NULL;
  list__add(free_list, new_page);
  return (0);
}

void		*move_memory(t_header *block, size_t size)
{
  void		*new;

  if ((new = malloc(size)) == NULL)
    return (NULL);
  memcpy(new, block->addr, MIN(size, block->size));
  free(block->addr);
  return (new);
}
