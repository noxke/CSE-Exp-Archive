TARGET=task1
all: $(TARGET)
LLVM_CONFIG = llvm-config
LLVM_CXXFLAGS = $(shell $(LLVM_CONFIG) --cxxflags --ldflags --system-libs --libs core)

OBJS = $(TARGET).o

%.o: %.cpp
	g++ -g -o $@ $< $(LLVM_CXXFLAGS)  -c 

$(TARGET): $(OBJS)
	g++ -g -o $@ $(OBJS) $(LLVM_CXXFLAGS) 

clean:
	$(RM) -rf $(OBJS)