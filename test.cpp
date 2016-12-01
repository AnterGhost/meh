#include <iostream>
#include <algorithm>
// #include <GL/gl.h>
// #include <GL/glx.h>
#include <dlfcn.h>

template <typename T> T GetNextFunction(const char* filename, const char* symbol) {
	return reinterpret_cast<T>(dlsym(dlopen(filename, RTLD_NOW), symbol));
}

typedef void (*SDL_GL_SwapBuffers_t) ();
SDL_GL_SwapBuffers_t oSDL_GL_SwapBuffers = NULL;

extern "C" void* SDL_GL_SwapBuffers(){

	printf("Dongs?\n");

};

void __attribute__((constructor)) init() {
	oSDL_GL_SwapBuffers = GetNextFunction<SDL_GL_SwapBuffers_t>("./bin/linux64/libSDL2-2.0.so.0", "SDL_GL_SwapBuffers");
}
