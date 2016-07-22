#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include "Mesh.h"
#include "Canvas.h"

static const int windowWidth = 800;
static const int windowHeight = 600;

class Window {
public:
	Window(int argc, char *args[], int width = windowWidth, int height = windowHeight, const char *title = "Screen");
	~Window();

	void run();
private:
	SDL_Surface *_screen;
	Canvas *_canvas;
	Mesh *_mesh;

	int _width;
	int _height;

	bool _running = true;

	bool keyStatus[SDLK_LAST];

	void quit();
	void onKeyDownEvent(const SDL_Event *event);
	void onKeyUpEvent(const SDL_Event *event);
	void onMouseButtonDownEvent(const SDL_Event *event);
	void update();

	void clear();
	void draw();
	void show();

	void updateInput();
	void HandleEvent(const SDL_Event *event);
};

inline
Window::~Window() {
	delete[] _canvas;
	delete[] _mesh;
}

inline
void Window::quit() {
	_running = false;
}

inline 
void Window::onKeyDownEvent(const SDL_Event * event) {
	SDLKey key = event->key.keysym.sym;
	if (key == SDLK_ESCAPE) {
		quit();
	}
	keyStatus[key] = true;
}

inline 
void Window::onKeyUpEvent(const SDL_Event * event) {
	SDLKey key = event->key.keysym.sym;
	keyStatus[key] = false;
}

inline 
void Window::onMouseButtonDownEvent(const SDL_Event * event) { }

inline 
void Window::clear() {
	_canvas->clear();
}

inline 
void Window::draw() {
	_canvas->drawMesh(*_mesh);
}

inline 
void Window::show() {
	SDL_UnlockSurface(_screen);
	SDL_UpdateRect(_screen, 0, 0, 0, 0);
}

#endif