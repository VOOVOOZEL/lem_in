#define VECTOR_INITIAL_CAPACITY 100
#define VECTOR(v) ((t_vec)v)

typedef struct	s_vector{
  size_t	size;
  size_t	capacity;
  void		*data;
}				        t_vector;

typedef t_vector *t_vec;

void			vector_init(t_vector *vector, size_t size);
void			vector_append(t_vector *vector, void *value, size_t size);
void			*vector_get(t_vector *vector, size_t index, size_t size);
void			vector_set(t_vector *vector, size_t index, void *value, size_t size);
void			vector_double_capacity_if_full(t_vector *vector);
void			vector_free(t_vector *vector);