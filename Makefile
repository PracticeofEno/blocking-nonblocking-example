NAME = ft_webserv
CFLAGS = -Wall -Wextra -Werror -std=c++98
CC = clang++

CFLAGS += -I ./header/ 

FILES = 

SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(FILES))) 

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : 
	$(CC) $(CFLAGS) -g -o $(NAME) main.cpp

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
