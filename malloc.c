/*
** malloc.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:54:58 2015 Jean-Baptiste Grégoire
** Last update Fri Jan 30 17:08:06 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

/*
** - This function split the memory of the free block. Add the used part on the used_list
** and the free one to the free_list. I'm not sure about the special case
** (juste one block on one list, or no blok at all for exemple).
*/
void			add_block_to_used(t_header **used, t_header *prev,
					  t_header *current, size_t size)
{
  t_header		*new;
  size_t		sub_block_size;

  sub_block_size = current->size - size - sizeof(t_header);
  new = current;
  new->size = size;
  new->next = *used;
  *used = new;
  current = new + sizeof(t_header) + size;
  current->size = sub_block_size;
  current->next = NULL;
  prev->next = current;
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

/*
** - This function just search from the first block of memory large enought to contain the size asked.
*/
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
	  return (it);
	}
      else if (size + sizeof(t_header) < it->size)
	{
	  add_block(prev, it, size);
	  return (it);
	}
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
