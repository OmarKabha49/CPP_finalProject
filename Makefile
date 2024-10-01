# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -g

# SFML library paths
SFML_LIB = /usr/local/lib # Update this to your SFML library path if different
SFML_INCLUDE = /usr/local/include # Update this to your SFML include path if different

# SFML Libraries (for windowing, graphics, system)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories and Files
SRCDIR = .
OBJDIR = obj
BINDIR = bin
EXECUTABLE = monopoly

# List of all source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Convert source files to object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Target to create object directory if not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Target to create the binary directory if not exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule to build the executable
$(BINDIR)/$(EXECUTABLE): $(OBJDIR) $(BINDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) -L$(SFML_LIB) $(SFML_LIBS)

# Rule to compile object files from source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

# Rule to clean the build
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Rule to run the program
.PHONY: run
run: $(BINDIR)/$(EXECUTABLE)
	./$(BINDIR)/$(EXECUTABLE)
