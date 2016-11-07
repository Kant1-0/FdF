# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/02 11:44:08 by qfremeau          #+#    #+#              #
#    Updated: 2016/11/02 13:41:14 by qfremeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC =		clang
CFLAGS =	-Wall -Wextra -Werror
ADDFLAGS =	

# Default rule
DEFRULE =	all

# Binary
NAME =		fdf
DST =		

# Directories
SRCDIR =	srcs
OBJDIR =	objs
INCDIR =	includes\
			minilibx\
			libft/includes\
			/usr/X11/include

# Sources
SRC = \
			main.c\
			fdf_list.c\
			fdf_error.c\
			fdf_parse.c\
			fdf_pixel.c\
			fdf_image.c\
			fdf_draw_line.c\
			fdf_draw_rect.c\
			fdf_move.c\
			fdf_zoom.c\
			fdf_maths.c\
			fdf_hook.c\
			fdf_hexa_to_int.c\
			fdf_color_hex.c\
			fdf_color_rgb.c\
			fdf_utils.c\
			fdf_exit.c

OBJ =		$(SRC:.c=.o)

# Prefixes
MLIBX =		-L/usr/local/lib -lmlx -lm -framework OpenGL -framework AppKit
LIBFT =		-Llibft/ -lft


# Paths foreach
LIBP =		$(addprefix -L, $(LIBNAME)/)
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCP =		$(foreach dir, $(INCDIR), -I$(dir))

# **************************************************************************** #
# SPECIAL CHARS

LOG_CLEAR		= \033[2K
LOG_UP			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BOLD		= \033[1m
LOG_UNDERLINE	= \033[4m
LOG_BLINKING	= \033[5m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# **************************************************************************** #
# RULES

.PHONY: glu

# Main rules
default:
	@echo -e "$(LOG_BOLD)Default execution: rule $(DEFRULE)$(LOG_NOCOLOR)"
	@make $(DEFRULE)
	@echo -e "$(LOG_BOLD)Execution finished     $(LOG_NOCOLOR)ヽ(ヅ)ノ"
	

glu: re
	@make clean

all: mlibxcomp libftcomp $(OBJDIR) $(NAME)

re: fclean all

# Compilation rules
libftcomp:
	@make all -C libft/

mlibxcomp:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build minilibx$(LOG_NOCOLOR)"
	@make all -C minilibx/
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)minilibx$(LOG_NOCOLOR) compiled.......... $(LOG_GREEN)✓$(LOG_NOCOLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)........................ $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(NAME)$(LOG_NOCOLOR)"
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJP)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -o $@ $^ $(INCP) $(MLIBX) $(LIBFT)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR) compiled............... $(LOG_GREEN)✓$(LOG_NOCOLOR)"

# MrProper's legacy
clean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean --force minilibx$(LOG_NOCOLOR)"
	@make clean -C minilibx/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean libft$(LOG_NOCOLOR)"
	@make clean -C libft/

fclean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean minilibx$(LOG_NOCOLOR)"
	@make clean -C minilibx/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean libft$(LOG_NOCOLOR)"
	@make fclean -C libft/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion.............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -f $(NAME)
