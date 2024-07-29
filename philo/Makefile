NAME		=	philo

SRCS		=	

OBJS		=	$(SRCS:.c=.o)
HEADER		=	includes/

MYLB		=	MYLIB
MYAR		=	MYLIB/libar.a

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
SHORT		=	-L$(MYLB) -lar
RM			=	rm -fr

GREEN		=	"\033[1;32m"
YELOW		=	"\033[1;33m"
REDCL		=	"\033[1;31m"
RESET		=	"\033[0m"

all: start $(MYLB) $(NAME) finish

start:
	@printf "\n"
	@echo $(GREEN)"Starting build..."
	@sleep 1
	@printf "Loading [ "

finish:
	@echo $(GREEN) ] 100%$(RESET)
	@echo $(GREEN)Project built.$(RESET)
	@printf "\n"

$(MYLB):
	@make -C $(MYLB) --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ $(SHORT) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER) $(MYAR)
	@$(CC) $(FLAGS) -c -I $(MYLB) -I includes $< -o $@
	@printf $(GREEN)"."$(RESET)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@make clean -C $(MYLB) --no-print-directory
	@echo $(YELOW)Cleaning up 🧹💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make fclean -C $(MYLB) --no-print-directory
	@echo $(REDCL)Purging all files 🗑️$(RESET)

re: fclean all
