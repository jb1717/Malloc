/*
** malloc.h for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:59:28 2015 Jean-Baptiste Grégoire
** Last update Fri Jan 30 16:17:04 2015 Jean-Baptiste Grégoire
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>

# define MALLOC_PAGE_SIZE	getpagesize()

enum		e_move
  {
    TO_FREE = 0,
    TO_USED
  };

typedef struct	s_header
{
  size_t	size;
  void		*addr;
  struct s_header *next;
}		t_header;

void		*malloc(size_t size);

#endif /* !MALLOC_H_ */
