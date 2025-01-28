#include "Field.h"
#include "Exceptions.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

void test_game()
{
	Game gm;
	gm.startGame();
}

int main() 
{
	try {

		test_game();

		return EXIT_SUCCESS;
	}
	catch (const MyException& e) {
		std::cout << "it's unexpected: " << e.GetErrorText() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "it's unexpected: " << e.what() << std::endl;
	}
	return 0;
}