SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: $(OBJS)
	$(CC) $(LDFLAGS) $^ ../engine/engine.a -o game

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@rm `find -name '*.o'` game