#include <iostream>
#include <algorithm>
#include <SDL.h>

#include "Window.h"

int main(int argc, char* args[]) {
	Window window(argc, args);

	window.run();

	return 0;
}