# Compiler
CXX = g++

# Target executable name
TARGET = game.exe

# Source files
SRCS = src/main.cpp

# --- PATHS FROM THE OFFICIAL WINDOWS INSTALLER ---
RAYLIB_PATH = C:/raylib/raylib/src

# Include and Library paths (adjust if installed elsewhere)
INCLUDES = -I$(RAYLIB_PATH)
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -Wl,--defsym,stat64i32=_stat64

# Compilation flags
# -mwindows hides the extra console window when running the GUI app (optional)
CXXFLAGS = -Wall -std=c++17 $(INCLUDES)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET)
