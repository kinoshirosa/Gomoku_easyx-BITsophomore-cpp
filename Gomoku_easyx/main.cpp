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
		SetWindowText(get_hwnd, L"������");
		if (winning_color == BLACK_PIECE) {
			black_score++;
			messagebox_msg = L"�ڷ�ʤ����˫���ȷ֣�" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"����һ�֣�";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"��ʾ", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == WHITE_PIECE) {
			white_score++;
			messagebox_msg = L"�׷�ʤ����˫���ȷ֣�" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"����һ�֣�";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"��ʾ", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == NONE) {
			int isok = MessageBox(get_hwnd, L"ƽ�֣�����һ�֣�", L"��ʾ", MB_OKCANCEL);
			if (isok == IDOK)
			{
				printf("������OK\n");
			}
			else if (IDCANCEL == isok)
			{
				printf("������ȡ��\n");
				game_status = false;
			}
		}
	}
	std::cout << "Press enter to exit" << std::endl;
	//std::cout << std::wstring(L"���»س����˳�").c_str() << std::endl;
	getchar();
	closegraph();
	return 0;
}