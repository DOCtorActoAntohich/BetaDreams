// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <exception>

#include "App.h"
#include "Log.h"



int main(int argc, char** argv) {
	beta::Log::info("Welcome to Beta::Dreams. Initialization begins now.");
	beta::App app;
	beta::Log::info("Successfully initialized.");

	try {
		beta::Log::info("Running Beta::Dreams.");
		app.run();
	}
	catch (std::exception& ex) {
		beta::Log::error(ex.what());
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	beta::Log::info("App closed.");

	return 0;
}
