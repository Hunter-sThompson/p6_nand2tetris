
all: main.exe

main.exe:
	g++ main.cpp parser.cpp -O2 -o main.exe

test:
	@make main.exe
	./main.exe Add.asm -o Add.hack
	@make clean

clean:
	@rm main.exe
