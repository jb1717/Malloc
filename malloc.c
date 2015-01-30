/*
** malloc.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:54:58 2015 Jean-Baptiste Grégoire
** Last update Fri Jan 30 16:42:04 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

void			add_block(t_header *prev, t_header *current, size_t size)
{
  t_header		*new;
  size_t		sub_block_size;

  sub_block_size = current->size - size - sizeof(t_header);
  new = current;
  new->size = size;
  current = current + sizeof(t_header) + size;
  current->size = sub_block_size;
  new->next = current;
  prev->next = new;
}

/*
** - This function switch a block from one list to the other.
** - 'dest' is the destination of the block
** - When we call this function we have to be sure that prev->next is not NULL.
*/
void			switch_block(t_header **used_list, t_header **free_list,
				     t_header *prev, e_move dest)
{
  t_header		*current;

  if (!prev)
    return ;
  current = prev->next;
  prev->next = prev->next->next;
  if (dest == TO_FREE)
    {
      current->next = *free_list;
      *free_list = current;
    }
  else if (dest == TO_USED)
    {
      current->next = *used_list;
      *used_list = current;      
    }
}

void			*first_fit(t_header *used_list, t_header *free_list, size_t size)
{
  t_header		*it;
  t_header		*prev;

  it = free_list;
  prev = it;
  while (it)
    {      
      if (size + sizeof(t_header) == it->size)
	{
	  switch_block(&used_list, &free_list, &prev, TO_USED);
	}
      else if (size + sizeof(t_header) < it->size)
	add_block(prev, it, size);
      if (it != free_list)
	prev = prev->next;
      it = it->next;
    }
  return (NULL);
}

void			*best_fit(t_header *used_list, t_header *free_list, size_t size)
{
}

void			*malloc(size_t size)
{
  static t_header	*_used = NULL;
  static t_header	*_free = NULL;

  if (!_free)
    {
      _free = sbrk(MALLOC_PAGE_SIZE + sizeof(t_header));
      _free->addr = _free + sizeof(t_header);
      _free->size = MALLOC_PAGE_SIZE;
      _free->next = NULL;
    }
  
}
