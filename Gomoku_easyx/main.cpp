#include "button.h"
#include "textbox.h"
#include "game.cpp"
#include <windows.h>
#include <locale.h>
#include <string>
// main runs on game.cpp -- go to game.cpp file

//std::wstring x_coord_wchar;
//std::wstring y_coord_wchar;
//static int x_coord;
//static int y_coord;

int main() {
	multiple_game();
	getchar();
	closegraph();
	return 0;
}