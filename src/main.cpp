#include <iostream>
#include "game.h"

int main() {
	try {
		Game game;
		game.run();
	} catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}