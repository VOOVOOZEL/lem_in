NAME = lem-in

HEADER = ./lem_in/inc/ ./structures/

FLAGS = -Wall -Werror -Wextra -fsanitize=address

SOURCES = ./lem_in/src/main.c ./structures/vector.c ./gnl/get_next_line.c

SRCS = $(addprefix $(SOURCES))

OBJS = $(SOURCES:.c=.o)

DIR_S = ./lem_in/src/

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./gnl/libprintf
	@gcc $(FLAGS) -L ./gnl/libprintf -lftprintf -o $(NAME) $(OBJS)

%.o : $(DIR_S)/%.c
	@gcc $(FLAGS) -I$(HEADER) -c  $(SOURCES)

clean:
	@make clean -C ./gnl/libprintf
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C ./gnl/libprintf
	@/bin/rm -f $(NAME)
	@/bin/rm -f filler.trace

re: fclean all
