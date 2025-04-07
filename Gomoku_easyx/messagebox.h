#ifndef _SMESSGAEBOX_H_
#define _SMESSAGEBOX_H_
#include <graphics.h>
#include <string>
#include <conio.h>
#include <iostream>

class SMessageBox {
	int _x;
	int _y;
	int _width;
	int _height;
	double _scale;

	int max_length;
	bool if_init;

	COLORREF _default_bk_color;
	COLORREF _default_text_color;
	std::wstring _text;
	std::wstring _displaying_text;
public:
	SMessageBox(int x, int y, int width, int height,
		std::wstring text = L"",
		COLORREF default_bk_color = WHITE,
		COLORREF default_text_color = BLACK,
		double scale = 0.7);
	void init_smb();
	bool print_text();
	void edit_text(std::wstring input_text);
	void run();
};

#endif // !_MESSGAGE_BOX_H_

