#include "messagebox.h"

static double textX;
static double textY;
static double scaledWidth;
static double scaledHeight;
static double scaledX;
static double scaledY;
static int width_per_char;
const int text_start_position = 5;

SMessageBox::SMessageBox(int x, int y, int width, int height,
	std::wstring text,
	COLORREF default_bk_color,
	COLORREF default_text_color,
	double scale) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_scale = scale;
	max_length = (_width - 2 * text_start_position) / (20 * scale);
	if_init = false;
	
	_default_bk_color = default_bk_color;
	_default_text_color = default_text_color;
	_text = text;
	_displaying_text = L"";
}

void SMessageBox::init_smb() {
	setfillcolor(_default_bk_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);
	if_init = true;
}
bool SMessageBox::print_text() {
	if (_text == _displaying_text) {
		return true;
	}
//	if (textwidth(_text.c_str()) > max_length) {
//		std::cout << "MessageBox over range" << std::endl;
//		_text = _displaying_text;
//		return false;
//	}
	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_default_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(_height * _scale, 0, _T("Î¢ÈíÑÅºÚ"));
	textX = _x + text_start_position;
	textY = _y + text_start_position;
	
	setfillcolor(_default_bk_color);
	solidrectangle(textX, textY, textX + textwidth(_displaying_text.c_str()), scaledY + textheight(_displaying_text.c_str()));
	_displaying_text = _text;
	outtextxy(textX, textY, _displaying_text.c_str());
}
void SMessageBox::edit_text(std::wstring text) {
	_text = text;
}
void SMessageBox::run() {
	if (!if_init) {
		init_smb();
	}
	print_text();
}