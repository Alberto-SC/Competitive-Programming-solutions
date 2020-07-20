CFLAGS   += -DVERSION="\"$(VERSION)\""
CXXFLAGS += -DVERSION="\"$(VERSION)\""

CXXFLAGS += -std=c++11 -O2

ifeq ($(shell uname -s), Darwin)
  CXXFLAGS += -Wl,-stack_size -Wl,0x8000000
else ifeq ($(shell uname -s), MSYS_NT-10.0)
  CXXFLAGS += -Wl,-stack -Wl,0x8000000
else
  CXXFLAGS += -fsplit-stack
endif

TARGET = checker

build: $(TARGET)

$(TARGET): $(TARGET).cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-rm -f $(TARGET)
