
all: main.exe

main.exe:
	g++ -Wall -Wextra -std=c++11 ./src/main.cpp ./src/parser.cpp ./src/assembler.cpp ./src/symbolTable.cpp -O2 -o main.exe

test:
	@make main.exe
	./main.exe pong/Pong.asm -o PongTest.hack
	@make clean

clean:
	@rm main.exe
