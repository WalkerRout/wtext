OBJS = src/*.c src/include/extensions/*.c

OBJ_NAME_WIN = bin/WText.exe
OBJ_NAME_MAC = bin/WText
OBJ_NAME = $(OBJ_NAME_MAC)

DEFAULT_SDL_MAC = -I  usr/local/Cellar/sdl2/2.0.20/include -L /usr/local/Cellar/sdl/2.0.20/lib -std=c11 -w -lSDL2main -lSDL2
DEFAULT_SDL_WIN = -I C:/Development/SDL2_MinGW_64Bit/include -L C:/Development/SDL2_MinGW_64Bit/lib -std=c11 -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
DEFAULT_SDL = $(DEFAULT_SDL_MAC)

all: build run

build: $(OBJS)
	gcc $(OBJS) $(DEFAULT_SDL) -o $(OBJ_NAME)

run: $(OBJ_NAME)
	./$(OBJ_NAME)

clean:
	clear
	rm ./$(OBJ_NAME)
	@echo "Removed $(OBJ_NAME)"
