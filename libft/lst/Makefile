.PHONY: clean fclean re
CC = gcc
CFLAGS = -Wall -Wextra -Werror
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = lst
FILES = ft_lstadd.c \
	ft_lstaddb.c \
	ft_lstdel.c \
	ft_lstdelnode.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstpushb.c \
	ft_lstpushf.c \
	ft_lsttostr.c
OBJS = $(FILES:.c=.o)

all: $(addprefix $(ODIR), $(OBJS))

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
