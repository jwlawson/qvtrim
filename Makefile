# define any compile-time flags
# Using cygwin -std=gnu++11 should be used rather than -std=c++11
CXXFLAGS = -Wall -std=gnu++11 -march=native
OPT = -g -O3

# Specify base directory
BASE_DIR = .

# Specify source directory
SRC_DIR = $(BASE_DIR)/src
INC_DIR = $(BASE_DIR)/include

# define the output directory for .o
OBJ_DIR = $(BASE_DIR)/build

# define any directories containing header files
INCLUDES = -I$(BASE_DIR)/include -I$(HOME)/include

# define library paths
LFLAGS = -L$(HOME)/lib

# define any libraries to link into executable
LIBS = -lqv

# define the C source files
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# define the C object files
_OBJS = $(SRCS:.cc=.o)

# Puts objs in obj_dir
OBJS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(_OBJS))

# define the executable file
MAIN = qvtrim

.PHONY: clean

all:    $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPT) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(OPT) $(INCLUDES) -c $< -o $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) *.o *~ $(OBJ_DIR)/*.o

