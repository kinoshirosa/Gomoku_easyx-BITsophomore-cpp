#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_
// this TextBox only work well with single line text
// further version will update soon
#include "graphics.h"
#include "conio.h"
#include <string>
#include <windows.h>
#include <cstdio>
#include <iostream>

typedef enum text_display_status {
	DEFAULT_TEXTBOX_DISPLAY,
	SELECTED_TEXTBOX_DISPLAY,
	INPUTING_TEXTBOX_DISPLAY
} text_display_status;

const std::wstring default_string = L"";

class TextBox {
private:
	int _x;
	int _y;
	int _width;
	int _height;
	double _scale;
	double _cursor_freq;

	int max_length;
	int cursor_length;
	int cursor_position;
	bool if_show_cursor;
	bool if_selected;
	bool if_inputing;
	text_display_status tus;

	COLORREF _default_bk_color;
	COLORREF _selected_bk_color;
	COLORREF _default_text_color;
	COLORREF _selected_text_color;
	std::wstring _text;
	std::wstring _default_text;

public:
	TextBox(int x, int y, int width, int height, std::wstring text = L"",
		COLORREF default_bk_color = WHITE,
		COLORREF selected_bk_color = LIGHTBLUE,
		COLORREF default_text_color = LIGHTGRAY,
		COLORREF selected_text_color = BLACK,
		double scale = 0.7, double cursor_freq = 2);
	// TextBox字符串操作
	const std::wstring& get_text() const;
	bool is_empty();
	void clear_text();
	void set_text(std::wstring);
	void input_text(ExMessage& msg_k);
	// TextBox行为判定
	bool check_selected(ExMessage& msg);
	bool check_inputing(ExMessage& msg);
	// TextBox图形化
	void init_textbox();
	void select_textbox();
	void input_textbox(ExMessage& msg_k);
	//void input_textbox_deepseekver(ExMessage& msg_k); invalid function
	// cursor控制
	void update_cursor();
	void show_cursor();
	void clear_cursor();

	void run(ExMessage& msg_m);
};

#endif // !_TEXT_BOX_H_
