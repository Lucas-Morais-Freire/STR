COMP = g++
FLAGS = -Wall -Wextra -std=c++20 -g #-O3

TARGET = main.exe
SRCS = main.cpp src/engine.cpp src/shader.cpp src/circle.cpp C:/Projetos/glad/src/glad.cpp 
INCLUDE_PATHS = include C:/Projetos/glad/include C:/Projetos/glfw/include C:/Projetos/glm-1.0.1
LIBS_PATHS = C:/Projetos/glfw/build/src
LIBS = opengl32 glfw3 gdi32

INCLUDE_FLAGS = $(patsubst %,-I%,$(INCLUDE_PATHS))
LIBS_PATHS_FLAGS = $(patsubst %,-L%,$(LIBS_PATHS))
LIBS_FLAGS = $(patsubst %,-l%,$(LIBS))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
DEPS = $(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS)))

test:
	@echo $(DEPS)

all: $(TARGET)

$(TARGET): $(DEPS) $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) -o $(TARGET) $(INCLUDE_FLAGS) $(LIBS_PATHS_FLAGS) $(LIBS_FLAGS)

%.d: %.cpp
	$(COMP) $(FLAGS) -MMD -MP -c $< -o $(@D)/$(*F).o -MF $@ $(INCLUDE_FLAGS)

-include $(DEPS)

%.o: %.cpp
	$(COMP) $(FLAGS) -c $< -o $@ $(INCLUDE_FLAGS)

run: $(TARGET)
	.\$(TARGET)

clean:
	del $(subst /,\,$(OBJS) $(TARGET))