#include "piece.h"
#include <iostream>

Piece::Piece(piece_color color, int x, int y) {
	_x = x;
	_y = y;
	_color = color;
}
bool place_check(Piece piece1, Piece piece2, int size) {	// true为位置可以落子，false为不可落子
	if (piece1.get_x() < 0 || piece1._x >= size || piece2._y < 0 || piece2._y >= size) {
		std::cout << "DO NOT SET ON REPEATED PLACE" << std::endl;
		return false;
	}
	if (piece1._x != piece2._x || piece1._y != piece2._y) {
		return true;
	}
	else {
		if (piece1._color == NONE || piece2._color == NONE) {
			return true;
		}
		else
			return false;
	}

}
std::ostream& operator<< (std::ostream& os, const Piece& piece) {
	if (piece.get_color() == NONE) {
		std::cout << "NONE PIECE" << std::endl;
		return os;
	}
	if (piece.get_color() == BLACK_PIECE) {
		std::cout << "BLACK x: " << piece.get_x() << "y: " << piece.get_y() << std::endl;
	}
	if (piece.get_color() == WHITE_PIECE) {
		std::cout << "WHITE x: " << piece.get_x() << "y: " << piece.get_y() << std::endl;
	}
}