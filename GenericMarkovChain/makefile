CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

EXEC1 = tweets_generator
EXEC2 = snakes_and_ladders

TWEETS_SRC = tweets_generator.c markov_chain.c linked_list.c
SNAKES_SRC = snakes_and_ladders.c markov_chain.c linked_list.c

TWEETS_OBJ = tweets_generator.o markov_chain.o linked_list.o
SNAKES_OBJ = snakes_and_ladders.o markov_chain.o linked_list.o

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(TWEETS_OBJ)
	$(CC) $(CFLAGS) -o $(EXEC1) $(TWEETS_OBJ)

$(EXEC2): $(SNAKES_OBJ)
	$(CC) $(CFLAGS) -o $(EXEC2) $(SNAKES_OBJ)

tweets_generator.o: tweets_generator.c markov_chain.h linked_list.h
	$(CC) $(CFLAGS) -c tweets_generator.c -o tweets_generator.o

snakes_and_ladders.o: snakes_and_ladders.c markov_chain.h linked_list.h
	$(CC) $(CFLAGS) -c snakes_and_ladders.c -o snakes_and_ladders.o

markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	$(CC) $(CFLAGS) -c markov_chain.c -o markov_chain.o

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c -o linked_list.o

clean:
	rm -f $(TWEETS_OBJ) $(SNAKES_OBJ) $(EXEC1) $(EXEC2)

.PHONY: all clean