.PHONY: clean fclean re
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wconversion#remove last one
ODIR = objs/
SDIR = srcs/
IDIR = includes/
NAME = client
FILES =
OBJS = $(FILES:.c=.o)

all: $(addprefix $(ODIR), $(OBJS))#add message
	@$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<#Change it

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<

clean:
	@echo "\x1b[31mRemoving the object files of $(NAME)\x1b[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean

re:
	@$(MAKE) fclean
	@$(MAKE)