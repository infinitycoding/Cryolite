
LDFLAGS = -lSDL -lGL -lGLU -lSDL_image -lSDL_ttf -lSDL_mixer  -lSDL_net -lalut -lopenal -llua -ldl
INC = -I ../include -I ../include/game -I ../include/render -I ../include/util -I /usr/include/SDL
CFLAGS = -std=gnu++0x
CC = g++

export LDFLAGS
export INC
export CFLAGS
export CC
export LD


Cryolite:
	@$(MAKE) -C engine

Server:
	@$(MAKE) -C server

all: Cryolite Server
	@$(MAKE) -C game


Debug: all

Release:
	@export CFLAGS+="-O3"
	@$(MAKE) -C engine
	@$(MAKE) -C game
	@$(MAKE) -C server
	
clean:
	@$(MAKE) -C engine clean
	@$(MAKE) -C game clean

launch:
	./game/game
