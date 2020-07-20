CFLAGS   += -DVERSION="\"$(VERSION)\""
CXXFLAGS += -DVERSION="\"$(VERSION)\""

CXXFLAGS += -std=c++11 -O2

TARGET = checker

build: $(TARGET)

$(TARGET): $(TARGET).cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-rm -f $(TARGET)
