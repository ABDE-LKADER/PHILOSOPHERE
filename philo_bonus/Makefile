NAME		=	philo_bonus

SRCS		=	

OBJS		=	$(SRCS:.c=.o)
HEADER		=	includes/

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -fr

GREEN		=	"\033[1;32m"
YELOW		=	"\033[1;33m"
REDCL		=	"\033[1;31m"
RESET		=	"\033[0m"

all: start $(NAME) finish

start:
	@printf "\n"
	@echo $(GREEN)"Starting build..."
	@sleep 1
	@printf "Loading [ "

finish:
	@echo $(GREEN) ] 100%$(RESET)
	@echo $(GREEN)Project built.$(RESET)
	@printf "\n"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ -o $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c -I includes $< -o $@
	@printf $(GREEN)"."$(RESET)

clean:
	@$(RM) $(OBJS)
	@echo $(YELOW)Cleaning up 🧹💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(REDCL)Purging all files 🗑️$(RESET)

re: fclean all
