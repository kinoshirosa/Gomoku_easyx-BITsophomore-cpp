#include "button.h"

static double textX;
static double textY;
static double scaledWidth;
static double scaledHeight;
static double scaledX;
static double scaledY;

void Button::init_button() {
	if (bus == DEFAULT_BUTTON_DISPLAY)
		return;
	setfillcolor(_default_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);

	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(20 * _scale, 0, _T("Î¢ÈíÑÅºÚ"));
	textX = scaledX + (scaledWidth - textwidth(_text.c_str())) / 2;
	textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
	outtextxy(textX, textY, _text.c_str());
	bus = DEFAULT_BUTTON_DISPLAY;
}
void Button::point_button() {
	if (bus == POINTED_BUTTON_DISPLAY)
		return;
	setfillcolor(_pointed_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);

	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(20 * _scale, 0, _T("Î¢ÈíÑÅºÚ"));
	textX = scaledX + (scaledWidth - textwidth(_text.c_str())) / 2;
	textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
	outtextxy(textX, textY, _text.c_str());
	bus = POINTED_BUTTON_DISPLAY;
}
void Button::click_button() {
	if (bus == CLICKED_BUTTON_DISPLAY)
		return;
	setfillcolor(_clicked_color);
	fillrectangle(_x, _y, _x + _width, _y + _height);

	scaledWidth = _width * _scale;
	scaledHeight = _height * _scale;
	scaledX = _x + (_width - scaledWidth) / 2;
	scaledY = _y + (_height - scaledHeight) / 2;

	settextcolor(_text_color);
	setbkmode(TRANSPARENT);
	settextstyle(20 * _scale, 0, _T("Î¢ÈíÑÅºÚ"));
	textX = scaledX + (scaledWidth - textwidth(_text.c_str())) / 2;
	textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
	outtextxy(textX, textY, _text.c_str());
	bus = CLICKED_BUTTON_DISPLAY;
}

bool Button::check_pointed(ExMessage& msg) {
	if (msg.x > _x && msg.x < _x + _width && msg.y > _y && msg.y < _y + _height) {
		if_pointed = true;
		return true;
	}
	else
		if_pointed = false;
		return false;
}
bool Button::check_clicked(ExMessage& msg) {
	if (msg.message == WM_LBUTTONDOWN) {
		if_clicked = true;
		return true;
	}
	else
		if_clicked = false;
		return false;
}
bool Button::run(ExMessage& msg) {
	if (check_pointed(msg)) {
		if (check_clicked(msg)) {
			click_button();
			return true;
		}
		point_button();
		return false;
	}
	init_button();
	return false;
}