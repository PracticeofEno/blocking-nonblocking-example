NAME = ft_webserv
CFLAGS = -Wall -Wextra -Werror -std=c++98
CC = clang++

CFLAGS += -I ./header/ -I ./class/

CLASS_FILES = httpHeader \
			  requestHeader \
			  responseHeader \
			  MyServer

CLASS_SRCS = $(addprefix class/, $(addsuffix .cpp, $(CLASS_FILES))) 

OBJS = $(CLASS_SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) main.cpp $(OBJS)

%.o : %.cpp
	$(CC) $(CFLAGS) -g -c -o $@ $^

clean :
	rm -f $(OBJS) $(C_OBJS)

fclean :
	rm -f $(OBJS) $(C_OBJS) $(NAME)

re : fclean all

map : $(MAP_OBJS)
	$(CC) $(CFLAGS) -g -o map $(MAP_OBJS)
vector :

stack :

.PHONY: clean fclean all re bonus
