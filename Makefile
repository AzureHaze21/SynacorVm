NAME	= synacorvm

CC	= g++

RM	= rm -f

SRCS	= ./src/SynacorVm.cpp \
	  ./src/main.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./inc/
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
