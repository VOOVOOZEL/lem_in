#include "../../gnl/get_next_line.h"
#include "../../structures/vector.h"

typedef struct  s_pos
{
    int         x;
    int         y;
    char        *name;
}               t_pos;

typedef struct  s_pair
{
    int         to;
    int         weight;
}               t_pair;

typedef struct  s_lem
{
    int         ants;
    int         flag_ants;
    int         flag_start;
    int         flag_end;
    t_pos       start;
    t_pos       end;
    // t_pos       coords[4000];
    t_vec       conn;
}               t_lem;
