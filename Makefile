SRC = *.cpp glad.c

default:
	g++ $(SRC) -o build/main -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32