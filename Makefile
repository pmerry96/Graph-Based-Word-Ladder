default: 
	echo Usage: ./wordladder

all:
	g++ -o wordladder -std=c++11 main.cpp

clean:
	rm -f wordladder
