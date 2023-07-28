NAME = webserv
CXX = c++
CXXFLAGS = -std=c++98 -pedantic  -Wall -Wextra -Werror -g3 -fsanitize=address


CONFIGSRCS = ConfParser.cpp \
						httpBlock/HttpBlock.cpp \
						httpBlock/HttpBase.cpp \
						LocationBlock/LocBlock.cpp \
						serverBlock/ServBlock.cpp \
						Tools/ParseTool.cpp \
						otherBlock/OtherBlock.cpp

CONFIGOBJS = $(addprefix ./modules/config/, $(CONFIGSRCS:.cpp=.o))

WEBSERVSRCS = Kserver.cpp \
							WebServ.cpp \
							Kqueue.cpp

WEBSERVOBJS = $(addprefix ./modules/webserv/, $(WEBSERVSRCS:.cpp=.o))

MAINSRC = main.cpp
MAINOBJ = $(addprefix ./, $(MAINSRCS:.cpp=.o))

OBJS  =  $(CONFIGOBJS) $(WEBSERVOBJS) $(MAINOBJ)

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp
		$(CXX) $(CXXFLAGS) -o $@ -c $^


clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
