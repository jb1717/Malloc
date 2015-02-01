/*
** malloc.h for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:59:28 2015 Jean-Baptiste Grégoire
** Last update Sun Feb  1 14:41:40 2015 Jean-Baptiste Grégoire
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <stdlib.h>
# include <time.h>

# include <stdio.h>

# define MALLOC_PAGE_SIZE	getpagesize()

enum		e_move
  {
    TO_FREE = 0,
    TO_USED
  };

enum		e_algo
  {
    WORST_FIT_ALGO = 0,
    BEST_FIT_ALGO,
    FIRST_FIT_ALGO
  };

typedef struct	s_header
{
  size_t	size;
  void		*addr;
  struct s_header *next;
}		t_header;

void		*malloc(size_t size);
void		*add_block_to_used(t_header **used, t_header **free_list,
				   t_header **prev, size_t size);
void		switch_block(t_header **used_list, t_header **free_list,
			     t_header *perv, enum e_move dest);
void		add_new_page(void *addr, t_header **free_list);
void		delete_from_used(t_header **used_list, t_header *prev);

#endif /* !MALLOC_H_ */
