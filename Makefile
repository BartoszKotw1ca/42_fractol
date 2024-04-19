FLAGS = -Wall -Wextra -Werror
NAME = fractol
OBJDIR = Obj/
MLX = mlxlibX/libmlx_Linux.a
SRC = main.c julia.c utils.c mandelbrot.c programs.c

OBJ := $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)
	@echo "Compilation completed."

$(NAME): $(OBJ)
	@cc $(FLAGS) $^ -o $@ mlxlibX/libmlx_Linux.a -lXext -lX11 -lm

%.o: %.c
	@cc $(FLAGS) -Imlx_linux -O3 -c $< -o $@

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@echo "Cleared."

re: fclean all

.PHONY: all, clean, fclean, re
