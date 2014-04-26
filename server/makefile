SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: $(OBJS)
	$(CC) $^ ../engine/engine.a $(LDFLAGS) -o server

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -Iinclude -c -o $@ $<

clean:
	@rm `find -name '*.o'` server
