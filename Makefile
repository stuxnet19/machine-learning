all: read_mnist

read_mnist: bin/main.o
	g++ -o $@ $^ -ljpeg

bin/%.o: src/%.cpp src/*.h
	mkdir -p `dirname $@`
	g++ -o $@ -c $<

clean:
	rm read_mnist
	rm -rf bin
