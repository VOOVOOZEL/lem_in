NAME = lem-in

HEADER = ./lem_in/inc/lem_in.h

FLAGS = -Wall -Werror -Wextra -fsanitize=address

SOURCES = main.c

SRCS = $(addprefix $(SOURCES))

OBJS = $(SOURCES:.c=.o)

DIR_S = ./lem_in/src/

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./gnl/libprintf
	@gcc $(FLAGS) -I $(HEADER) -L ./gnl/libprintf -lftprintf ./gnl/get_next_line.c -o $(NAME) $(OBJS)

%.o : $(DIR_S)/%.c
	@gcc $(FLAGS) -I $(HEADER) -c  ./lem_in/src/$(SOURCES)

clean:
	@make clean -C ./gnl/libprintf
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C ./gnl/libprintf
	@/bin/rm -f $(NAME)
	@/bin/rm -f filler.trace

re: fclean all
