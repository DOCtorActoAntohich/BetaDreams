#include "App.h"

#include <iostream>
#include <exception>


int main(int argc, char** argv) {
	beta::App app;

	try {
		app.run();
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
