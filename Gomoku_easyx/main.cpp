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
	bool game_status = true;
	piece_color winning_color = NONE;
	int black_score = 0;
	int white_score = 0;
	std::wstring messagebox_msg;
	
	while (game_status) {
		winning_color = game();
		HWND get_hwnd = GetHWnd();
		SetWindowText(get_hwnd, L"五子棋");
		if (winning_color == BLACK_PIECE) {
			black_score++;
			messagebox_msg = L"黑方胜利，双方比分：" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"再来一局？";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"提示", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == WHITE_PIECE) {
			white_score++;
			messagebox_msg = L"白方胜利，双方比分：" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"再来一局？";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"提示", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == NONE) {
			int isok = MessageBox(get_hwnd, L"平局，再来一局？", L"提示", MB_OKCANCEL);
			if (isok == IDOK)
			{
				printf("你点击了OK\n");
			}
			else if (IDCANCEL == isok)
			{
				printf("你点击了取消\n");
				game_status = false;
			}
		}
	}
	std::cout << "Press enter to exit" << std::endl;
	//std::cout << std::wstring(L"按下回车键退出").c_str() << std::endl;
	getchar();
	closegraph();
	return 0;
}