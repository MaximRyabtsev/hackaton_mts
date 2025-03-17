TARGET = app
CC = g++ 
CONFIG = `pkg-config -libs sdl3 sdl3-image sdl3-ttf`

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) -arch arm64 $(OBJ) $(CONFIG) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) -arch arm64 -c $< -o $@

clean :
	rm -f $(TARGET) $(PREF_OBJ)*.o