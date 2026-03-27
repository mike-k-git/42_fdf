MAKEFLAGS += --no-print-directory

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -MMD -DP

NAME = fdf

SRC = main.c           \
	  argument.c       \
	  event_keyboard.c \
	  event_mouse.c    \
	  mlx.c            \
	  map.c            \
	  renderer.c       \
	  errors.c         \
	  points.c         \
	  line.c           \
	  rotation.c       \
	  color.c          \
	  utils.c          \
	  projection.c     \
	  info.c

OBJDIR = obj

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)

LIBFTDIR = ./42_libft
LIBFT    = $(LIBFTDIR)/libft.a

MLXDIR = ./minilibx-linux
MLX    = $(MLXDIR)/libmlx.a

LIBFTPRINTFDIR = ./42_ft_printf
LIBFTPRINTF    = $(LIBFTPRINTFDIR)/libftprintf.a

LIBGNLDIR = ./42_get_next_line
LIBGNL    = $(LIBFTPRINTFDIR)/libgnl.a

LDFLAGS = -L$(MLXDIR) -L$(LIBFTDIR) -L$(LIBFTPRINTFDIR) -L$(LIBGNLDIR) -lft -lmlx -lXext -lX11 -lm -lz
INCLUDES = -I$(MLXDIR)         \
		   -I$(LIBFTDIR)       \
		   -I$(LIBFTPRINTFDIR) \
		   -I$(LIBGNLDIR)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR)

$(LIBFTPRINTF):
	@$(MAKE) -s -C $(LIBFTPRINTFDIR)

$(LIBGNL):
	@$(MAKE) -s -C $(LIBGNLDIR)

$(MLX):
	@$(MAKE) -s -C $(MLXDIR)

$(NAME): $(MLX) $(LIBFT) $(LIBFTPRINTFDIR) $(LIBGNL) $(OBJ)
	@echo "Linking fdf"
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@echo "Removing objects"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing binary and mlx"
	@rm -f $(NAME)
	@rm -rf $(MLX)
	@$(MAKE) fclean -s -C $(LIBFTDIR)
	@$(MAKE) fclean -s -C $(LIBGNLDIR)

re: fclean all

.PHONY: all fclean re clean

-include $(DEP)
