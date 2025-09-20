export LD_LIBRARY_PATH=/home/printfdebugging/downloads/skia/skia/out/Shared

skia-raster: ./src/skia-raster-backend-example.cpp
	g++ $^ -o exe \
		-I/home/printfdebugging/downloads/skia/skia \
		-L/home/printfdebugging/downloads/skia/skia/out/Shared \
		-lskia \
		-lglfw

skia-opengl: ./src/skia-opengl-backend-example.cpp
	g++ $^ -o exe \
		-I/home/printfdebugging/downloads/skia/skia \
		-L/home/printfdebugging/downloads/skia/skia/out/Shared \
		-lskia \
		-lglfw

run: skia-raster
	./exe

clean:
	rm -rf ./exe
