#include "../inc/lem_in.h"

int main(void)
{
	char    *line;
	char    **tmp;
	t_lem   lem;

	lem.flag_ants = 0;
	lem.flag_start = 0;
	lem.flag_end = 0;
	lem.ants = 0;
	lem.conn = malloc(sizeof(struct s_vector));
	vector_init(lem.conn, sizeof(struct s_vector));

	while (get_next_line(STDIN_FILENO, &line) > 0)
	{   
		if (lem.flag_ants == 0)
		{
			lem.ants = ft_atoi(line);
			lem.flag_ants++;
		}
		else if (strcmp(line, "##start") == 0 && lem.flag_start == 0)
            lem.flag_start = 1;
    	else if (lem.flag_start == 1)
		{
			tmp = ft_strsplit(line, ' ');
			lem.start.name = tmp[0];
			lem.start.x = ft_atoi(tmp[1]);
			lem.start.y = ft_atoi(tmp[2]);
            lem.flag_start = 0;
        }
		else if (strcmp(line, "##end") == 0 && lem.flag_end == 0)
            lem.flag_end = 1;
    	else if (lem.flag_end == 1)
		{
			tmp = ft_strsplit(line, ' ');
			lem.end.name = tmp[0];
			lem.end.x = ft_atoi(tmp[1]);
			lem.end.y = ft_atoi(tmp[2]);
            lem.flag_end = 0;
        }
		else if (ft_strchr(line, '-'))
		{
			printf("line: %s\n", line);
			tmp = ft_strsplit(line, '-');
			int from;
			int to;
			from = ft_atoi(tmp[0]);
			to = ft_atoi(tmp[1]);
			t_vec vec_from = (t_vec)vector_get(lem.conn, from, sizeof(t_vector));
			t_vec vec_to = (t_vec)vector_get(lem.conn, to, sizeof(t_vector));
			t_pair pair;
			pair.weight = -1;
			pair.to = to;
			if (vec_from)
				vector_append(vec_from, &to, sizeof(int));
			else
			{
				vec_from = malloc(sizeof(t_vector));
				vector_init(vec_from, sizeof(int));
				printf("CHECK\n");
				vector_set(lem.conn, from, vec_from, sizeof(t_vector));
				free(vec_from);
				vec_from = vector_get(lem.conn, from, sizeof(t_vector));
				printf("pointer: %p\n", vec_from);
				vector_append(vec_from, &pair, sizeof(t_pair));
			}
			pair.to = from;
			if (vec_to)
				vector_append(vec_to, &to, sizeof(int));
			else
			{
				vec_to = malloc(sizeof(t_vector));
				vector_init(vec_to, sizeof(int));
				vector_set(lem.conn, to, vec_to, sizeof(t_vector));
				free(vec_to);
				vec_to = vector_get(lem.conn, to, sizeof(t_vector));
				vector_append(vec_to, &pair, sizeof(t_pair));
			}
		}
		
    }
	printf("ant count %d\n", lem.ants);
	printf("start %s %d %d\n", lem.start.name, lem.start.x, lem.start.y);
	printf("end %s %d %d\n", lem.end.name, lem.end.x, lem.end.y);
	
	// for (size_t i = 0; i < lem.conn->size; i++)
	// {
	// 	for (size_t j = 0; j < lem.conn[i].size; j++)
	// 		printf("pupa %d", lem.conn[i].data)
	// }
	
    return (0);
}
