CC = gcc
SRC = main.c \
	  three_point.c \
	  use\#.c \
	  about_assert.c \
	  about_ctype.c \
	  about_errno.c

OBJS = $(patsubst %.c,%.o,$(SRC))
#sinclude $(SRC:.c=.d)

example: $(OBJS)
	gcc $^ -o $@
	./example
	make clean

%.o: %.c
	gcc -c $< -o $@

#%.d: %.c
#	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY:clean

clean:
	rm *.o  example
