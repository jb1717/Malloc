/*
** malloc.h for malloc in /home/gregoi_j/rendu/PSU_2014_malloc
**
** Made by Jean-Baptiste Grégoire
** Login   <gregoi_j@epitech.net>
**
** Started on  Thu Jan 29 11:59:28 2015 Jean-Baptiste Grégoire
** Last update Wed Apr 15 17:06:10 2015 Hugo Prenat
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <stdlib.h>
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

enum		e_move
  {
    RIGHT = 0,
    LEFT
  };

typedef struct	s_header	t_header;
typedef struct	s_shortcut	t_shortcut;

typedef struct	s_header
{
  size_t	size;
  void		*addr;
  t_header	*next;
}		t_header;

typedef struct	s_shortcut
{
  t_header	*ptr;
  t_shortcut	*next;
}		t_shortcut;

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
t_header	*best_fit(t_header **used_list, t_header **free_list,
			   size_t size);

/* utils.c */
int		malloc_init(t_header **free_list);
int		init_value_malloc(size_t *size, pthread_mutex_t *m_mutex,
				  t_header **free_list);
int		add_new_page(t_header **free_list);
void		*move_memory(t_header *block, size_t size);
void		merge_free_space(t_header **free_list, t_header *block1,
				 t_header *block2, enum e_move side);

/* realloc.c */
void		resize(t_header *p, size_t size, t_header **free_list);

/* free.c */
void		free_link(t_header *p, t_header **free_list);

#endif /* !MALLOC_H_ */
