CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

NAME = Kserver

SRCS = main.cpp	\
			 Kserver.cpp \

RM = rm -rf

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^

%.o : %.cpp
		$(CC) $(CFLAGS) -o $@ -c $^

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
