#include <iostream>
#include "Game.h"
#include "Menu.h"
#include <conio.h>




void showMenu()
{
	while (true)
	{
		system("cls");

		std::cout << R"(
	 ####### ###   ## ####### ##  ## #######
	 ###     ####  ## ##   ## ## ### ##
	 ####### ## ## ## ####### ###### ####### 
	     ### ##  #### ##   ## ## ### ##  
	 ####### ##   ### ##   ## ##  ## #######
	 

	1.Start Game
	2.View HighScore
	3.Exit
	)" << '\n';

		std::cout << "Enter your choise:";

		char choise = _getch();

		if (choise == '1')
		{
			Game game;
			game.run();
		}
		else if (choise == '2')
		{
			system("cls");
			std::ifstream file("highscore.txt");
			int hs = 0;
			if (file.is_open());
			{
				file >> hs;
				file.close();
			}
			std::cout << "Curent High Score:" << hs << std::endl;
			std::cout << "Press any key to retur to menu";
			_getch();
		}
		else if (choise == '3')
		{
			std::cout << "GoodBye";
			break;
		}
	}
}