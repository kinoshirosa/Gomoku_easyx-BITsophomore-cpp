#include "textbox.h"

static double textX;
static double textY;
static double scaledWidth;
static double scaledHeight;
static double scaledX;
static double scaledY;
static int width_per_char;
const int text_start_position = 5;
bool key_negedge_indicator = true;
wchar_t input_char = L'0';

TextBox::TextBox(
	int x, int y, int width, int height, 
	std::wstring input_string,
	COLORREF default_bk_color,
	COLORREF selected_bk_color,
	COLORREF default_text_color,
	COLORREF selected_text_color,
	double scale, double cursor_freq) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_scale = scale;
	_cursor_freq = cursor_freq;

	_default_bk_color = default_bk_color;
	_selected_bk_color = selected_bk_color;
	_default_text_color = default_text_color;
	_selected_text_color = selected_text_color;

	_default_text = input_string;
	_text = L"";
	tus = INPUTING_TEXTBOX_DISPLAY;
	cursor_position = 0;
	if_selected = if_inputing = if_show_cursor = false;
	max_length = (_width - 2 * text_start_position) / (20 * scale);
	cursor_length = 0;
}

const std::wstring& TextBox::get_text() const {
	return _text;
}
bool TextBox::is_empty() {
	return _text == L"";
}
void TextBox::clear_text() {
	_text = L"";
	cursor_position = 0;
}
void TextBox::set_text(std::wstring text) {
	_text = text;
	cursor_position = text.length();
}
void TextBox::input_text(ExMessage& msg_k) {
	if (msg_k.message == WM_CHAR && key_negedge_indicator == true) { // && key_negedge_indicator == true
		key_negedge_indicator = false;
		std::cout << "getting chars: " << msg_k.ch << std::endl;
		clear_cursor();
		switch (msg_k.ch)
		{
		case L'\b':				// 用户按退格键，删掉一个字符
			if (!_text.empty() && cursor_position > 0)
			{
				std::cout << "deleted char: " << _text[cursor_position - 1] << std::endl;;
				int x_last = _x + textwidth(_text.substr(0, cursor_position--).c_str()) + text_start_position;
				int x_start = _x + textwidth(_text.substr(0, cursor_position).c_str());
				_text.erase(cursor_position, 1);
				setfillcolor(_default_bk_color);
				solidrectangle(x_start, textY, x_last, textY + textheight(_T("微软雅黑")));
			}
			break;
		case L'\r':
		case L'\n':
			std::cout << std::flush;
			cursor_position = _text.length();
			if_inputing = false;
			clear_cursor();
			tus = DEFAULT_TEXTBOX_DISPLAY;
			break;
		default:				// 用户按其它键，接受文本输入
			if (textwidth(_text.substr(0, cursor_position).c_str()) < _width - 2 * text_start_position &&
				cursor_position >= 0 && cursor_position <= _text.length())
			{
				_text.insert(cursor_position, 1, msg_k.ch);
				//printf("get char %s", msg_k.ch);
				//printf("current text string: %s", _text.c_str());
				std::cout << "append char:" << msg_k.ch << std::endl;
				std::cout << "current text: " << _text.c_str() << std::endl;
				cursor_position++;
			}
			else {
				if (textwidth(_text.substr(0, cursor_position).c_str()) > _width - 2 * text_start_position)
					std::cout << "string exceed range!" << std::endl;
				else
					std::cout << "current cursor position: " << cursor_position << std::endl;
			}
		}
	}
	else if (msg_k.message == WM_KEYUP && key_negedge_indicator == false) {
		key_negedge_indicator = true;
	}
}

bool TextBox::check_selected(ExMessage& msg) {
	if (msg.x > _x && msg.x < _x + _width && msg.y > _y && msg.y < _y + _height) {
		if_selected = true;
	}
	else {
		if_selected = false;
	}
	return if_selected;
}
bool TextBox::check_inputing(ExMessage& msg) {
	if (!check_selected(msg) && msg.message == WM_LBUTTONDOWN) { //&& msg.message == WM_LBUTTONDOWN
		if_inputing = false;
		//cursor_position = textwidth(_text.c_str());
	}
	if (if_inputing) {
		return true;
	}
	if (if_selected && msg.message == WM_LBUTTONDOWN) {
		if_inputing = true;
	}
	return if_inputing;
}

void TextBox::init_textbox() {
	if (tus == DEFAULT_TEXTBOX_DISPLAY) {
		return;
	}
	if_show_cursor = false;
	std::cout << "stop input mode" << std::endl;
	clear_cursor();
	setfillcolor(_default_bk_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);

	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_default_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(_height * _scale, 0, _T("微软雅黑"));
	textX = _x + text_start_position;
	textY = _y + text_start_position;
	if(_text == L"")
		outtextxy(textX, textY, _default_text.c_str());
	else
		outtextxy(textX, textY, _text.c_str());
	tus = DEFAULT_TEXTBOX_DISPLAY;
}
void TextBox::select_textbox() {
	if (tus == SELECTED_TEXTBOX_DISPLAY)
		std::cout << "stop input mode" << std::endl;
		return;
	if_show_cursor = false;
	update_cursor();
	setfillcolor(_selected_bk_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);

	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_selected_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(_height * _scale, 0, _T("微软雅黑"));
	//textX = scaledX + (scaledWidth - textwidth(_text.c_str())) / 2;
	//textY = scaledY + (scaledHeight - textheight(_T("微软雅黑"))) / 2;
	textX = _x + text_start_position;
	textY = _y + text_start_position;
	if (_text == L"")
		outtextxy(textX, textY, _default_text.c_str());
	else
		outtextxy(textX, textY, _text.c_str());
	tus = SELECTED_TEXTBOX_DISPLAY;
}
void TextBox::input_textbox(ExMessage& msg_k) {
	if (tus != INPUTING_TEXTBOX_DISPLAY) {
		printf("start input mode\n");
		if_show_cursor = true;
		update_cursor();
		setfillcolor(_default_bk_color);
		fillrectangle(_x, _y, _x + _width, _y + _height);

		scaledWidth = _width * _scale;
		scaledHeight = _height * _scale;
		scaledX = _x + (_width - scaledWidth) / 2;
		scaledY = _y + (_height - scaledHeight) / 2;
		tus = INPUTING_TEXTBOX_DISPLAY;
	}
	update_cursor();
	input_text(msg_k);
	settextcolor(_selected_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(_height * _scale, 0, _T("微软雅黑"));
	textX = _x + text_start_position;
	textY = _y + text_start_position;
	
	outtextxy(textX, textY, _text.c_str());
}

void TextBox::update_cursor() {
	if (tus != INPUTING_TEXTBOX_DISPLAY)
		return;
	static DWORD lastTick = GetTickCount();  // 记录初始时间
	DWORD currentTick = GetTickCount();     // 获取当前时间

	// 检查是否达到500毫秒间隔
	if (currentTick - lastTick >= 500) {
		if_show_cursor = !if_show_cursor;  // 切换光标状态
		lastTick = currentTick;    // 重置计时
	}
	if (!if_show_cursor)
		clear_cursor();
	else 
		show_cursor();
}
void TextBox::show_cursor() {
	if (if_show_cursor) {
		setlinecolor(BLACK);
		int cursor_x = _x + 5 + textwidth(_text.substr(0, cursor_position).c_str());
		line(cursor_x, _y + 2 + _height / 8, cursor_x, _y + _height * 7 / 8 - 2);
	}
}
void TextBox::clear_cursor() {
	setlinecolor(_default_bk_color);
	int cursor_x = _x + 5 + textwidth(_text.substr(0, cursor_position).c_str());
	line(cursor_x, _y + 2 + _height / 8, cursor_x, _y + _height * 7 / 8 - 2);
}

void TextBox::run(ExMessage& msg_m) {
	if (check_inputing(msg_m)) {
		input_textbox(msg_m);
		return;
	}
	if (check_selected(msg_m)) {
		select_textbox();
		return;
	}
	init_textbox();
	return;
}