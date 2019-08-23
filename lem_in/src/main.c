#include "../inc/lem_in.h"

int main(void)
{
	char    *line;
	char    **tmp;
	t_lem   lem;
	int		index = 0;

	int count_conn = 0;
	int count_coords = 0;

	lem.flag_ants = 0;
	lem.flag_start = 0;
	lem.flag_end = 0;
	lem.ants = 0;
	vector_init(lem.conn);

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
			vector_append(lem.conn, )
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
		else
		{
			tmp = ft_strsplit(line, '-');
			int *from = malloc(sizeof(int));
			int *to = malloc(sizeof(int));
			*from = tmp[0];
			*to
			lem.conn[count_conn].from = tmp[0];
			lem.conn[count_conn].to= tmp[1];
			count_conn++;
			++index;
		}
		
    }
	printf("ant count %d\n", lem.ants);
	printf("start %s %d %d\n", lem.start.name, lem.start.x, lem.start.y);
	printf("end %s %d %d\n", lem.end.name, lem.end.x, lem.end.y);
	
	for (int i = 0; i < count_conn; i++)
	{
		printf("coon %d - %s %s\n", i, lem.conn[i].from, lem.conn[i].to);
	}
	for (int i = 0; i < count_coords; i++)
	{
		printf("coord %d -  %s %d %d\n",i, lem.coords[i].name, lem.coords[i].x, lem.coords[i].y);
	}
	
    return (0);
}
