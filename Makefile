CXX			=	c++

ifdef DEBUG
	CXXFLAGS	=	-std=c++98 -g3 -fsanitize=address
else ifdef LEAKS
	CXXFLAGS	=	-std=c++98 -g	
else
	CXXFLAGS	=	-std=c++98 -Wall -Werror -Wextra -pedantic-errors
endif

NAME		=	ft_containers

SRCS		=	main.cpp\

OBJS		=	$(SRCS:%.cpp=%.o)

INCL_PATH	=	./includes

COMPILE_MSG = @echo $(BOLD)$(PURPLE) $(NAME) is compiled 📢 $(RESET)

######################### Color #########################

GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
PURPLE="\033[35m"
L_PURPLE="\033[1;35m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"

########################## Rule ##########################

.PHONY		:	all
all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@$(CXX) $(CXXFLAGS) $(OBJS) -I $(INCL_PATH) -o $@
				$(COMPILE_MSG)

%.o			:	%.cpp
				@$(CXX) $(CXXFLAGS) -I $(INCL_PATH) -c $< -o $@
				@echo $(CUT)$(YELLOW) Compiling with $(CXXFLAGS)...$(RESET)
				@echo $(CUT)$(YELLOW)'  ' [$(notdir $^)] to [$(notdir $@)] $(RESET)

.PHONY		:	clean
clean		:
				@rm -f $(OBJS)
				@echo $(L_RED) Remove OBJ files 👋 $(RESET)

.PHONY		:	fclean
fclean		:	clean
				@rm -f $(NAME)
				@echo $(L_RED) Remove $(NAME) 🧹 $(RESET)

.PHONY		:	re
re			:	fclean
				$(MAKE) all

.PHONY		:	debug
debug		:
				@make DEBUG=1
				@echo $(CUT)$(L_BLUE)$(BOLD) It\'s DEBUG TIME 🤪$(RESET)


.PHONY		:	leaks
leaks		:
				@make LEAKS=1
				@echo $(CUT)$(L_BLUE)$(BOLD) Is there Leaks? 🚰$(RESET)
