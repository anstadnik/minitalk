.PHONY: clean fclean re
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wconversion#remove last one
ODIR = objs/
SDIR = srcs/
IDIR = includes/
LDIR = ../libft/
NAME = server
LIB = $(LDIR)libft.a
FILES = server.c lstfuncs.c
OBJS = $(FILES:.c=.o)

all: $(NAME)
	
$(NAME): $(LIB) $(addprefix $(ODIR), $(OBJS))
	@echo "\x1b[34m\nCompiling $@\x1b[0m"
	@$(CC) $(CFLAGS) -I$(IDIR) -o $@ $^

$(LIB):
	@echo "\x1b[35m\nCompiling $(notdir $@)\x1b[0m"
	@$(MAKE) -C $(dir $@) $(notdir $@)
	@echo "\x1b[35m\n$(notdir $@) compiled\x1b[0m"

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<

clean: clean_objs
	@$(MAKE) -C $(LDIR) clean

clean_objs:
	@echo "\x1b[31mRemoving the object files of $(NAME)\x1b[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean_objs
	@$(MAKE) -C $(LDIR) fclean
	@echo "\x1b[31mRemoving the $(NAME)\x1b[0m"
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)
