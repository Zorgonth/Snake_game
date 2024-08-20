TARGET = snake_game

CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = main.cpp food.cpp Snake.cpp


SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(SFML_LIBS)

install_linux:
	@if ! dpkg -s libsfml-dev &>/dev/null; then \
		echo "Installing SFML on Linux..."; \
		sudo apt-get install -y libsfml-dev; \
	else \
		echo "SFML is already installed on Linux."; \
	fi

install_mac:
	@if ! brew list sfml &>/dev/null; then \
		echo "Installing SFML on macOS..."; \
		brew install sfml; \
	else \
		echo "SFML is already installed on macOS."; \
	fi



clean:
	rm -f $(TARGET)

re: clean all


.PHONY: clean install_linux install_mac re


all: $(TARGET)
