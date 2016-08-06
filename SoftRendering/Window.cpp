#include "Window.h"

#include "Camera.h"
#include "Vector3.h"

using XMATH::Vector3;

Window::Window(int argc, char * args[], int width, int height, const char * title) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init failed.\n");
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		SDL_Quit();
		fprintf(stderr, "SDL_SetVideoMode failed.\n");
	}

	_screen = screen;
	SDL_WM_SetCaption(title, NULL);

	_width = width;
	_height = height;

	_canvas = new Canvas((uint32_t*)screen->pixels, _width, _height);
	Camera camera(Vector3(0, 0, -5), Vector3(0, 0, 0), Vector3(0, 1, 0), 45, float(_width) / _height, 0.1f, 100.0f);
	_canvas->setCamera(camera);

	const char *modelPath = "cube.XI3d";
	const char *texturePath = "cube.XIimage";
	if (argc > 2) {
		modelPath = args[1];
		texturePath = args[2];
	}
	
	_mesh = new Mesh(modelPath, texturePath);
}

void Window::run(){

	while (_running) {
		SDL_LockSurface(_screen);

		updateInput();

		update();

		clear();

		draw();

		show();
	}
}

void Window::updateInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		HandleEvent(&event);
	}
}

void Window::HandleEvent(const SDL_Event * event) {
	uint8_t eventType = event->type;

	if (eventType == SDL_QUIT) {
		quit();
	}
	else if (eventType == SDL_KEYDOWN) {
		onKeyDownEvent(event);
	}
	else if (eventType == SDL_KEYUP) {
		onKeyUpEvent(event);
	}
	else if (eventType == SDL_MOUSEBUTTONDOWN) {
		onMouseButtonDownEvent(event);
	}

}

void Window::update() {
	static const float transform = 0.05f;

	//translate
	if (keyStatus[SDLK_UP]) {
		_mesh->position.y += transform;
	}
	if (keyStatus[SDLK_DOWN]) {
		_mesh->position.y -= transform;
	}
	if (keyStatus[SDLK_LEFT]) {
		_mesh->position.x -= transform;
	}
	if (keyStatus[SDLK_RIGHT]) {
		_mesh->position.x += transform;
	}

	//rotate
	if (keyStatus[SDLK_w]) {
		_mesh->rotation.x += transform;
	}
	if (keyStatus[SDLK_s]) {
		_mesh->rotation.x -= transform;
	}
	if (keyStatus[SDLK_a]) {
		_mesh->rotation.y += transform;
	}
	if (keyStatus[SDLK_d]) {
		_mesh->rotation.y -= transform;
	}

}
