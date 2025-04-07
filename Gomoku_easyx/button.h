#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <string>
#include "graphics.h"
#include "conio.h"

typedef enum button_display_status {
	DEFAULT_BUTTON_DISPLAY,
	POINTED_BUTTON_DISPLAY,
	CLICKED_BUTTON_DISPLAY
} button_display_status;

class Button {
private:
	int _x;
	int _y;
	int _width;
	int _height;
	double _scale;					// 文字相对图形的缩放比例
	std::wstring _text;
	COLORREF _default_color;
	COLORREF _pointed_color;
	COLORREF _clicked_color;
	COLORREF _text_color;
	bool if_pointed;
	bool if_clicked;
	button_display_status bus;
public:
	Button(int x, int y, int width, int height, 
		std::wstring text = L"", 
		COLORREF default_color = RGB(255, 255, 255),
		COLORREF pointed_color = RGB(245, 245, 245),
		COLORREF clicked_color = RGB(187, 255, 255),
		COLORREF text_color = RGB(50, 50, 50),
		double scale = 0.7) :
		_x(x), _y(y), _width(width), _height(height), _scale(scale),
		_text(text), _default_color(default_color), _pointed_color(pointed_color), _clicked_color(clicked_color), _text_color(text_color) {
		if_pointed = false;
		if_clicked = false;
		bus = POINTED_BUTTON_DISPLAY;
	}
	// Button图形化
	void init_button();
	void point_button();
	void click_button();
	// Button行为判定
	bool check_pointed(ExMessage& msg);
	bool check_clicked(ExMessage& msg);
	// Button运行
	bool run(ExMessage& msg);

};

#endif // !_BUTTON_H_
