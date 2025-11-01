CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC
LDFLAGS = -lcurl

# JSON library is header-only, assuming it's installed in /usr/include/nlohmann
# Or you can download it from: https://github.com/nlohmann/json

TARGET = chillar
SOURCES = main.cpp transaction.cpp currency_converter.cpp transaction_manager.cpp
HEADERS = transaction.hpp currency_converter.hpp transaction_manager.hpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "✓ Build successful! Run with: ./$(TARGET)"

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned build artifacts"

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

.PHONY: all clean run rebuild