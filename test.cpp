#include <iostream>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glx.h>
#include <SDL2/SDL.h>
#include <dlfcn.h>

bool contextCreated = false;

SDL_GLContext thisContext;
SDL_GLContext oldContext;

GLvoid draw() {
    glColor3f(1.0f, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(0,190.0f);
    glVertex2f(100.0f, 190.0f);
    glVertex2f(100.0f,290.0f);
    glVertex2f(0, 290.0f);
    glEnd();
}

GLvoid init() {
    contextCreated = true;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(10, 10, 10, 10, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1.0);
}

void DoOurStuff(SDL_Window* win){
	//SAVE OLD WINDOW
	oldContext = SDL_GL_GetCurrentContext();
	//HIJACK WINDOW
	if(!contextCreated){
		thisContext = SDL_GL_CreateContext(win);
		SDL_GL_MakeCurrent(win, thisContext);
		init();
		contextCreated = true;
	} else {
		SDL_GL_MakeCurrent(win, thisContext);
	}
	// DRAW STUFF HERE //
	draw();

	//SWAP WINDOW BACK
	SDL_GL_MakeCurrent(win, oldContext);
}

static void (*lib_SDL_GL_SwapWindow)(SDL_Window*) = NULL;

void SDL_GL_SwapWindow(SDL_Window* win) {

	void* handle;
	char* errorstr;

	if(!lib_SDL_GL_SwapWindow){
		handle = dlopen("./bin/linux64/libSDL2-2.0.so.0", RTLD_LAZY);
		if(!handle) {
			fputs(dlerror(), stderr);
			exit(1);
		}

		lib_SDL_GL_SwapWindow = dlsym(handle, "SDL_GL_SwapWindow");

		if( (errorstr = dlerror()) != NULL ) {
			fprintf(stderr, "dlsym fail: %s\n", errorstr);
			exit(1);
		}
	}

	DoOurStuff(win);

	lib_SDL_GL_SwapWindow(win);
}
