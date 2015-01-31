/*
** malloc.c for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:54:58 2015 Jean-Baptiste Grégoire
** Last update Sat Jan 31 16:12:03 2015 Jean-Baptiste Grégoire
*/

#include "malloc.h"

/*
** - This function split the memory of the free block. Add the used part on the used_list
** and the free one to the free_list. I'm not sure about the special case
** (juste one block on one list, or no blok at all for exemple).
*/
void			*add_block_to_used(t_header **used, t_header **free_list,
					  t_header **prev, size_t size)
{
  t_header		*new;
  size_t		sub_block_size;

  if ((*prev)->next == NULL)
    {
      sub_block_size = (*prev)->size - size - sizeof(t_header);
      new = *prev;
      new->size = size;
      new->addr = new + sizeof(t_header);
      *prev = new->addr + size;
      (*prev)->size = sub_block_size;
      new->next = *used;
      *used = new;
      *free_list = *prev;
    }
  else
    {
      sub_block_size = (*prev)->next->size - size - sizeof(t_header);
      new = (*prev)->next;
      new->size = size;
      new->addr = new + sizeof(t_header);
      (*prev)->next = new->addr + size;
      (*prev)->next->size = sub_block_size;
      new->next = *used;
      *used = new;
    }
  return (new);
}

/*
** - This function switch a block from one list to the other.
** - 'dest' is the destination of the block
** - When we call this function we have to be sure that prev->next is not NULL.
*/
void			switch_block(t_header **used_list, t_header **free_list,
				     t_header *prev, enum e_move dest)
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
      /* printf("size demandé + header = %d ///// free_size = %d\n", size + sizeof(t_header), it->size); */
      if (size + sizeof(t_header) == it->size)
	{
	  switch_block(&used_list, &free_list, prev, TO_USED);
	  return (it);
	}
      else if (size + sizeof(t_header) < it->size)
	{
	  printf("coucou\n");
	  return (add_block_to_used(&used_list, &free_list, &prev, size));
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
  add_block_to_used(&used_list, &free_list, &prev_min, size);
  printf("coucou\n");
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
      printf("coucou\n");
      add_block_to_used(&used_list, &free_list, &prev_max, size);
      return (max);
    }
  return (NULL);
}

void			add_new_page(void *addr, t_header **free_list)
{
  t_header		*it;
  t_header		*new;

  it = *free_list;
  while (it)
    {
      printf("adress it = %p et sa size %lu\n", it->addr, it->size);
      printf("%p %p\n", (void*)(it->addr + it->size), addr);
      if (it->addr + it->size == addr)
	{
	  printf("Heyyyyyyyy\n");
	  it->size += MALLOC_PAGE_SIZE;
	  return ;
	}
      it = it->next;
    }
  new = addr;
  new->addr = new + sizeof(t_header);
  new->size = MALLOC_PAGE_SIZE - sizeof(t_header);
  new->next = *free_list;
  *free_list = new;
}

void			*manage_algo(t_header **used, t_header **free, size_t size)
{
  void			*addr;
  char			algo;
  char			run;

  run = 1;
  while (run)
    {
      algo = 2;//rand() % 3;
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
	  if ((addr = sbrk(MALLOC_PAGE_SIZE)) == (void *)(-1))
	    return (NULL);
	  add_new_page(addr, &free);
	  addr = NULL;
	}
      /* printf("%p\n", addr); */
    }
  return (addr);
}

void			*malloc(size_t size)
{
  static t_header	*_used = NULL;
  static t_header	*_free = NULL;

  printf("Etat de l'espace disponible :\n");

  t_header *it = _free;
  while (it)
    {
      printf("Il a y %lu octets de dispo à l'adresse %p\n", it->size, it->addr);
      it = it->next;
    }

  printf("////////\n");

  if (!_free)
    {
      _free = sbrk(MALLOC_PAGE_SIZE + sizeof(t_header));
      _free->addr = _free + sizeof(t_header);
      _free->size = MALLOC_PAGE_SIZE;
      _free->next = NULL;
      srand(time(NULL));
    }
  return (manage_algo(&_used, &_free, size));
}
