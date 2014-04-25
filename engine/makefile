SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: $(OBJS)
	ar -rcs engine.a $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@rm `find -name '*.o'` engine.a