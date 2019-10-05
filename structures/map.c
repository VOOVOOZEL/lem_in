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

#include "map.h"

unsigned			map_hash(const char *str)
{
	unsigned		hash;

	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) ^ *str++;
	return (hash);
}

t_map_node_t		*map_newnode(const char *key, void *value, int vsize)
{
	t_map_node_t	*node;
	int				ksize;
	int				voffset;

	ksize = strlen(key) + 1;
	voffset = ksize + ((sizeof(void*) - ksize) % sizeof(void*));
	node = malloc(sizeof(*node) + voffset + vsize);
	if (!node)
		return (NULL);
	memcpy(node + 1, key, ksize);
	node->hash = map_hash(key);
	node->value = ((char*)(node + 1)) + voffset;
	memcpy(node->value, value, vsize);
	return (node);
}

int		map_bucketidx(t_map_base_t *m, unsigned hash)
{
	return (hash & (m->nbuckets - 1));
}

void	map_addnode(t_map_base_t *m, t_map_node_t *node)
{
	int	n;

	n = map_bucketidx(m, node->hash);
	node->next = m->buckets[n];
	m->buckets[n] = node;
}

t_map_node_t		*swap_nodes(t_map_base_t *m)
{
	int				i;
	t_map_node_t	*next;
	t_map_node_t	*node;
	t_map_node_t	*nodes;

	nodes = NULL;
	i = m->nbuckets;
	while (i--)
	{
		node = (m->buckets)[i];
		while (node)
		{
			next = node->next;
			node->next = nodes;
			nodes = node;
			node = next;
		}
	}
	return (nodes);
}

int	map_resize(t_map_base_t *m, int nbuckets)
{
	t_map_node_t	*nodes;
	t_map_node_t	*node;
	t_map_node_t	*next;
	t_map_node_t	**buckets;

	nodes = swap_nodes(m);
	buckets = realloc(m->buckets, sizeof(*m->buckets) * nbuckets);
	if (buckets != NULL)
	{
		m->buckets = buckets;
		m->nbuckets = nbuckets;
	}
	if (m->buckets)
	{
		memset(m->buckets, 0, sizeof(*m->buckets) * m->nbuckets);
		node = nodes;
		while (node)
		{
			next = node->next;
			map_addnode(m, node);
			node = next;
		}
	}
	return (buckets == NULL) ? -1 : 0;
}

static t_map_node_t	**map_getref(t_map_base_t *m, const char *key)
{
	unsigned		hash;
	t_map_node_t	**next;

	hash = map_hash(key);
	if (m->nbuckets > 0)
	{
		next = &m->buckets[map_bucketidx(m, hash)];
		while (*next)
		{
			if ((*next)->hash == hash && !strcmp((char*)(*next + 1), key))
				return (next);
			next = &(*next)->next;
		}
	}
	return (NULL);
}

void				map_deinit_(t_map_base_t *m)
{
	t_map_node_t	*next;
	t_map_node_t	*node;
	int				i;

	i = m->nbuckets;
	while (i--)
	{
		node = m->buckets[i];
		while (node)
		{
			next = node->next;
			free(node);
			node = next;
		}
	}
	free(m->buckets);
}

void				*map_get_(t_map_base_t *m, const char *key)
{
	t_map_node_t	**next;

	next = map_getref(m, key);
	return (next ? (*next)->value : NULL);
}

int	free_node(t_map_node_t *node)
{
	if (node)
		free(node);
	return (-1);
}

int					map_set_(t_map_base_t *m, const char *key,
					void *value, int vsize)
{
	int				n;
	int				err;
	t_map_node_t	*node;
	t_map_node_t	**next;

	next = map_getref(m, key);
	if (next)
	{
		memcpy((*next)->value, value, vsize);
		return (0);
	}
	node = map_newnode(key, value, vsize);
	if (node == NULL)
		return (-1);
	if (m->nnodes >= m->nbuckets)
	{
		n = (m->nbuckets > 0) ? (m->nbuckets << 1) : 1;
		err = map_resize(m, n);
		if (err)
			free_node(node);
	}
	map_addnode(m, node);
	m->nnodes++;
	return (0);
}

void				map_remove_(t_map_base_t *m, const char *key)
{
	t_map_node_t	*node;
	t_map_node_t	**next;

	next = map_getref(m, key);
	if (next)
	{
		node = *next;
		*next = (*next)->next;
		free(node);
		m->nnodes--;
	}
}

t_map_iter_t		map_iter_(void)
{
	t_map_iter_t	iter;

	iter.bucketidx = -1;
	iter.node = NULL;
	return (iter);
}

const char	*next_bucket(t_map_base_t *m, t_map_iter_t *iter)
{
	if (++iter->bucketidx >= m->nbuckets)
		return (NULL);
	iter->node = m->buckets[iter->bucketidx];
	while (iter->node == NULL)
	{
		if (++iter->bucketidx >= m->nbuckets)
			return (NULL);
		iter->node = m->buckets[iter->bucketidx];
	}
	return (NULL);
}

const char	*map_next_(t_map_base_t *m, t_map_iter_t *iter)
{
	if (iter->node)
	{
		iter->node = iter->node->next;
		if (iter->node == NULL)
			return (next_bucket(m, iter));
	}
	else
		return (next_bucket(m, iter));
	return (char*)(iter->node + 1);
}

#if 0
int					main(void)
{
	map_int_t		m;
	map_vector_t	t;
	t_vector		vector;
	int				*val;
	t_vector		*val2;

	MAP_INIT(&m);
	MAP_INIT(&t);

	vector_init(&vector);
	vector_set(&vector, 10, 21312984);
	MAP_SET(&m, "testkey", 123);
	MAP_SET(&m, "test", 222);
	MAP_SET(&t, "test", vector);
	val = MAP_GET(&m, "testkey");
	if (val)
		printf("value: %d\n", *val);
	else
		printf("value not found\n");
	val = MAP_GET(&m, "test");
	if (val)
		printf("value: %d\n", *val);
	else
		printf("value not found\n");
	MAP_SET(&m, "test", 224);
	val = MAP_GET(&m, "test");
	if (val)
		printf("value: %d\n", *val);
	else
		printf("value not found\n");
	val2 = MAP_GET(&t, "test");
	for (size_t i = 0; i < 11; i++)
	{
		printf("%d\n", val2->data[i]);
	}
	
}
#endif
