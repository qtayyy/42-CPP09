NAME = PmergeMe

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address

SRC = main.cpp PmergeMe.cpp PmergeMeDeque.cpp PmergeMeVector.cpp

OBJ =  $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

bench: CFLAGS += -DBENCHMARK

bench: $(NAME)_bench
	bash ./bash_scripts/autobenchmark.sh
	

$(NAME)_bench: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)_bench

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME) $(NAME)_bench

re: fclean all
