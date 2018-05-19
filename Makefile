.PHONY: clean fclean re client server

TARGETS = client server

all: $(TARGETS)

$(TARGETS):
	@echo "\x1b[36m\nCompiling $@\x1b[0m"
	@$(MAKE) -C $@

clean:
	@for dir in $(TARGETS); do \
		$(MAKE) -C $$dir clean; \
	done

fclean:
	@for dir in $(TARGETS); do \
		$(MAKE) -C $$dir clean; \
	done

re: 
	@$(MAKE) fclean
	@$(MAKE) 
