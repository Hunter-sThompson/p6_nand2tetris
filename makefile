
all: main.exe

main.exe:
	g++ -std=c++11 main.cpp parser.cpp assembler.cpp symbolTable.cpp -O2 -o main.exe

test:
	@make main.exe
	./main.exe Max.asm -o Max.hack
	@make clean

clean:
	@rm main.exe
