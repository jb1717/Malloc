/*
** malloc.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:54:58 2015 Jean-Baptiste Grégoire
** Last update Fri Jan 30 19:17:01 2015 Jean-Baptiste Grégoire
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
	  add_block_to_used(&used_list, prev, it, size);
	  return (it);
	}
      if (it != free_list)
	prev = prev->next;
      it = it->next;
    }
  return (NULL);
}

/*
** - This function search the smallest block of memory large enougth to contain the size asked.
*/
void			*best_fit(t_header *used_list, t_header *free_list,
				  size_t size)
{
  t_header		*it;
  t_header		*prev;
  t_header		*min;
  t_header		*prev_min;

  prev = it = free_list;
  prev_min = min = NULL;
  while (it)
    {
      if (!min && size + sizeof(t_header) <= it->size)
	{
	  min = it;
	  prev_min = prev;
	}
      min = ((min && min->size > it->size && it->size + sizeof(t_header) >= size) ? it : min);
      prev_min = ((min && min->size > it->size && it->size + sizeof(t_header) >= size) ? prev : prev_min);
      if (it != free_list)
	prev = prev->next;
      it = it->next;
    }
  if (min == NULL)
    return (NULL);
  add_block_to_used(&used_list, prev_min, min, size);
  return (min);
}

/*
** - This function take the biggest block of memory and take a piece of memory
** if it's large enougth.
*/
void			*worst_fit(t_header *used_list, t_header *free_list,
				   size_t size)
{
  t_header		*it;
  t_header		*prev;
  t_header		*max;
  t_header		*prev_max;

  it = prev = max = prev_max = free_list;
  while (it)
    {
      if (max->size < it->size)
	{
	  max = it;
	  prev_max = prev;
	}
      if (it != free_list)
	prev = prev->next;
      it = it->next;
    }
  if (max->size + sizeof(t_header) >= size)
    {
      add_block_to_used(&used_list, prev_max, max, size);
      return (max);
    }
  return (NULL);
}

void			*manage_algo(t_header *used, t_header *free, size_t size)
{
  void			*addr;
  char			algo;
  char			run;

  algo = rand % 3;
  run = 1;
  while (run)
    {
      if (algo == WORST_FIT_ALGO)
	addr = worst_fit(used, free, size);
      else if (algo == BEST_FIT_ALGO)
	addr = best_fit(used, free, size);
      else
	addr = first_fit(used, free, size);  
      if (addr)
	run = 0;
      else
	{
	  if (sbrk(MALLOC_PAGE_SIZE) == (void *)(-1))
	    return (NULL);
	}
    }
  return (addr);
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
      srand(time());
    }
  return (manage_algo(_used, _free, size));
}
