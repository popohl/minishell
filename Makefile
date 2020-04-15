# Folders and Names
NAME		= minishell
SRCSDIR		= srcs
OBJSDIR		= objs
INCLUDES	= .
EXTLIB		= libft

# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -g3

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

SRCS	= $(subst ./srcs/,,$(wildcard ./srcs/*.c))
OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Compiling $@"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(EXTLIB)/$(EXTLIB).a:
	@echo "Compiling $@"
	@$(MAKE) -s -C $(EXTLIB)

clean:
	rm -rf $(OBJSDIR)
	$(MAKE) -C $(EXTLIB) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(EXTLIB) fclean

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test
