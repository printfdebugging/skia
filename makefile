export LD_LIBRARY_PATH=./libs/skia/out/Shared
SKIA_SHARED=./libs/skia/out/Shared/libskia.so

$(SKIA_SHARED):
	[ ! -f "$@" ] && bash ./scripts/build-skia.sh

skia-raster: ./src/skia-raster-backend-example.cpp $(SKIA_SHARED)
	g++ $< -o exe \
		-I./libs/skia \
		-L./libs/skia/out/Shared \
		-lskia \
		-lglfw

skia-opengl: ./src/skia-opengl-backend-example.cpp $(SKIA_SHARED)
	g++ $< -o exe \
		-I./libs/skia \
		-L./libs/skia/out/Shared \
		-lskia \
		-lglfw

run: skia-opengl
	./exe

clean:
	rm -rf ./exe
