
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lSDL2_image -lSDL2_ttf -lSDL2_mixer  -lSDL2_net -lalut -lopenal -llua -ldl
INC = -I ../include -I ../include/game -I ../include/render -I ../include/util -I/usr/local/include/SDL2/ -I/usr/include/SDL2/
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

Game:
	@$(MAKE) -C game

all: Cryolite Game

Debug: all

Release:
	@export CFLAGS+="-O3"
	@$(MAKE) -C engine
	@$(MAKE) -C game
	@$(MAKE) -C server
	
clean:
	@$(MAKE) -C engine clean
	@$(MAKE) -C game clean

launch: all
	./game/game
