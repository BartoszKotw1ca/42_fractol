FLAGS = -Wall -Wextra -Werror
NAME = fractol
OBJDIR = Obj/

SRC =	main.c julia.c utils.c mandelbrot.c

OBJ := $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)
	@echo "Compilation completed."

$(NAME): $(OBJ)
	@cc $(FLAGS) -I./mlxlibX -L./libmlx -lXext -lX11 $^ -o $@

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@cc $(FLAGS) -c $< -o $@

%.o: %.c
	@cc $(FLAGS) -Imlx_linux -O3 -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@echo "Cleared."

re: fclean all

.PHONY: all, clean, fclean, re
