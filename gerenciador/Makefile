COMP = g++
TARGET = main
SRCS = $(wildcard src/*.cpp)
FLAGS = -Wall -Wextra -g # -O3
INCLUDE_PATHS = include
LIB_PATHS =
LIBS =

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
INCLUDE_FLAGS = $(patsubst %,-I%,$(INCLUDE_PATHS)) `pkg-config --cflags gtkmm-4.0`
LIB_PATH_FLAGS =
LIB_FLAGS = $(patsubst %,-l%,$(LIBS)) `pkg-config --libs gtkmm-4.0`

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(DEPS) $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) -o $@ $(LIB_PATH_FLAGS) $(LIB_FLAGS)

-include $(DEPS)

%.o %.d: %.cpp
	$(COMP) $(FLAGS) -MMD -MP -MF $*.d -c $< -o $*.o $(INCLUDE_FLAGS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: $(TARGET)
	./$(TARGET)