/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:48:41 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/10 20:57:45 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "vector.h"

struct t_map_node_t;
typedef struct t_map_node_t	t_map_node_t;

typedef struct				s_map_base_t
{
	t_map_node_t			**buckets;
	unsigned				nbuckets;
	unsigned				nnodes;
}							t_map_base_t;

typedef struct				s_map_iter_t
{
	unsigned				bucketidx;
	t_map_node_t			*node;
}							t_map_iter_t;

struct						t_map_node_t {
	unsigned				hash;
	void					*value;
	t_map_node_t			*next;
};

# define MAP_T(T) struct { t_map_base_t base; T *ref; T tmp; }
# define MAP_INIT(m) memset(m, 0, sizeof(*(m)))
# define MAP_DEINIT(m) map_deinit_(&(m)->base)
# define MAP_GET(m, key) ( (m)->ref = map_get_(&(m)->base, key) )
# define MAP_TMP(m, key, value) (m)->tmp = (value), map_set_(&(m)->base, key, &(m)->tmp, sizeof((m)->tmp))
# define MAP_SET(m, key, value) ( MAP_TMP(m, key, value))
# define MAP_REMOVE(m, key) map_remove_(&(m)->base, key)
# define MAP_ITER(m) map_iter_()
# define MAP_NEXT(m, iter) map_next_(&(m)->base, iter)

void						map_deinit_(t_map_base_t *m);
void						*map_get_(t_map_base_t *m, const char *key);
int							map_set_(t_map_base_t *m,
							const char *key, void *value, int vsize);
void						map_remove_(t_map_base_t *m, const char *key);
t_map_iter_t				map_iter_(void);
const char					*map_next_(t_map_base_t *m, t_map_iter_t *iter);

typedef MAP_T(void*) map_void_t;
typedef MAP_T(char*) map_str_t;
typedef MAP_T(int) map_int_t;
typedef MAP_T(char) map_char_t;
typedef MAP_T(float) map_float_t;
typedef MAP_T(double) map_double_t;
typedef MAP_T(t_vector) map_vector_t;

#endif
