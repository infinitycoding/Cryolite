SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
INC += -I include -I ../engine/include -I ../engine/include/render

all: $(OBJS)
	$(CC) $^ ../engine/engine.a $(LDFLAGS) -o game

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@rm `find -name '*.o'` game
