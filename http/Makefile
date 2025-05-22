# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -static -static-libgcc -static-libstdc++ -Wall -Wextra

# Source files
SRCS = main.cpp \
       conf/Callbacks.cpp \
       commands/CommandHelper.cpp \
       commands/Filesystem.cpp \
       commands/Execution.cpp \
       commands/Management.cpp

# Header files (for dependency, not mandatory here)
HDRS = conf/Callbacks.h conf/Config.h commands/CommandHelper.h

# Output executable
TARGET = strata-exe

# Link libraries (Windows example)
LIBS = -lwinhttp -lwininet -liphlpapi -lws2_32

# On Windows, add subsystem linker flag for GUI apps (optional)
LDFLAGS_WIN = -Wl,-subsystem,windows

# Detect OS and set linker flags accordingly
ifeq ($(OS),Windows_NT)
    LDFLAGS = $(LDFLAGS_WIN)
else
    LDFLAGS =
    LIBS =  # Adjust or empty on Linux if you don't need Windows libs
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
