#ifndef _PIECE_H_
#define _PIECE_H_
#include <iostream>

typedef enum piece_color {
	NONE,
	BLACK_PIECE,
	WHITE_PIECE
} piece_color;

class Piece {
private:
	int _x;
	int _y;
	piece_color _color;
public:
	Piece(piece_color color = NONE, int x = -1, int y = -1);

	int get_x() const { return _x; }
	int get_y() const { return _y; }
	piece_color get_color() const { return _color; }
	void set_x(int x) { _x = x; }
	void set_y(int y) { _y = y; }
	void set_coord(int x, int y) { set_x(x); set_y(y); }
	void set_color(piece_color color) { _color = color; }
	void set(piece_color& color, int& x, int& y) { set_color(color); set_coord(x, y); };
	void operator= (const Piece& piece) { 
		_x = piece.get_x();
		_y = piece.get_y();
		_color = piece.get_color();
	}
	bool operator== (const Piece& piece) {
		return _x == piece.get_x() && _y == piece.get_y() && _color == piece.get_color();
	}

	friend bool place_check(Piece piece1, Piece piece0, int size);
	friend std::ostream& operator<< (std::ostream& os, const Piece& piece);
};
#endif // !_PIECE_H_
