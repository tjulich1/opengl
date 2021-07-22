OBJS = src/*.cpp
INCLUDE_PATH = -Iinclude
LIB_PATH = -Llib
LINKER_FLAGS = -lmingw32 -lSDL2main -lglew32 -lSDL2 -lOpenGL32
NAME = test_opengl

all: $(OBJS)
	g++ $(OBJS) $(INCLUDE_PATH) $(LIB_PATH) $(LINKER_FLAGS) -o $(NAME) 