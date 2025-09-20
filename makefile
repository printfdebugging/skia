export LD_LIBRARY_PATH=/home/printfdebugging/downloads/skia/skia/out/Shared

main: main.cpp
	g++ main.cpp -o main \
		-I/home/printfdebugging/downloads/skia/skia \
		-L/home/printfdebugging/downloads/skia/skia/out/Shared \
		-lskia \
		-lglfw \

run: main
	./main

clean:
	rm -rf ./main
