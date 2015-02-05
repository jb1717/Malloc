/*
** malloc.h for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
** 
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
** 
** Started on  Thu Jan 29 11:59:28 2015 Jean-Baptiste Grégoire
** Last update Thu Feb  5 16:44:36 2015 Jean-Baptiste Grégoire
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>
# include <errno.h>

# include <stdio.h>

# define MIN(a, b)		((a) < (b) ? (a) : (b))
# define MALLOC_PAGE_SIZE	getpagesize()
# if __x86_64__
#  define REG_SIZE		8
# else
#  define REG_SIZE		4
# endif
# define RAISE_ERROR(where)	\
do				\
{				\
  perror(where);		\
  return (-1);			\
} while (0)

enum		e_move
  {
    RIGHT = 0,
    LEFT
  };

enum		e_algo
  {
    WORST_FIT_ALGO = 0,
    BEST_FIT_ALGO,
    FIRST_FIT_ALGO
  };

typedef struct	s_header t_header;

typedef struct	s_header
{  
  size_t	size;
  void		*addr;
  t_header	*next;
}		t_header;

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		*calloc(size_t nmemb, size_t size);
void		show_alloc_mem();

/* list.c */
void		list__add(t_header **list, t_header *elem);
void		list__delete(t_header **list, t_header *elem);

/* algorithm.c */
t_header	*first_fit(t_header **used_list, t_header **free_list,
			   size_t size);

/* utils.c */
int		malloc_init(t_header **free_list);
int		add_new_page(t_header **free_list);
void		*move_memory(t_header *block, size_t size);
void		merge_free_space(t_header **free_list, t_header *block1,
				 t_header *block2, enum e_move side);

#endif /* !MALLOC_H_ */
