#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void	vector_init(t_vector *vector, size_t size)
{
	vector->size = 0;
	vector->capacity = VECTOR_INITIAL_CAPACITY * size;
	vector->data = malloc(vector->capacity);
}

void	vector_append(t_vector *vector, void *value, size_t size)
{
	char *p;
	char *data;

	p = (char*)value;
	vector->size += size;
	vector_double_capacity_if_full(vector);
	data = (char*)((size_t)vector->data + vector->size - size);
	while (size--)
	{
		printf("p[size] %p\n", &(p[size]));
		data[size] = p[size];
	}
	printf("\n");
}

void	*vector_get(t_vector *vector, int index, size_t size)
{
	if (index >= vector->size || index < 0)
	{
		printf("Index %d out of bounds for vector of size %zu\n", index, vector->size);
		exit(1);
	}
	return ((void*)(vector->data + size * index));
}

void	vector_set(t_vector *vector, int index, void *value, size_t size)
{
	char *p;
	char *data;
	void *zero;

	zero = malloc(size);
	bzero(zero, size);
	while (index >= vector->size)
		vector_append(vector, zero, size);
	free(zero);
	p = (char*)value;
	data = (char*)(vector->data + size * index);
	while (size--)
		data[size] = p[size];
}

void	vector_double_capacity_if_full(t_vector *vector)
{
	if (vector->size >= vector->capacity)
	{
		vector->capacity *= 2;
		vector->data = realloc(vector->data, sizeof(void*) * vector->capacity);
	}
}

void	vector_free(t_vector *vector)
{
	free(vector->data);
}

int		main() {
	t_vector vector;
	vector_init(&vector, sizeof(int));

	for (int i = 200; i > -50; i--) {
		vector_append(&vector, &i, sizeof(int));
	}

	int d = 21312984;
	vector_set(&vector, 27, &d, sizeof(int));

	printf("Heres the value at 27: %d\n", *((int*)vector_get(&vector, 27, sizeof(int))));

	vector_free(&vector);
}
