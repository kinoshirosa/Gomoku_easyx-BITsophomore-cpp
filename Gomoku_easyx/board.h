#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "kifu.h"
#include <graphics.h>
class Board {
private:
	int _size;
	std::vector<std::vector<Piece>> _pboard;
	std::vector<std::vector<int>> _pboard_status;
public:
	Board(int size = 0);
	~Board();
	Board(const Board&);
	void operator= (const Board&);
	int get_size() { return _size; }
	std::vector<std::vector<Piece>>& get_board() { return _pboard; }
	std::vector<std::vector<int>>& get_board_status() { return _pboard_status; }
	// realization
	void init_board();
	bool set_piece(piece_color color, int x, int y);
	bool set_piece(const Piece&);
	bool check_piece_range(int x, int y);
	bool check_piece_range(const Piece&);
	bool check_piece_repeat(int x, int y);
	bool check_piece_repeat(const Piece& piece);
	bool if_win(const piece_color color, const int x, const int y);
	bool if_win(const Piece& piece) { return if_win(piece.get_color(), piece.get_x(), piece.get_y()); };
	void load_kifu(Kifu&);
	// visualization
	void print_board_console();
	void print_board_easyx(const int&,const int&,const COLORREF&);
	void print_piece_easyx(const int& interval, const int& instruct_size, const int& piece_size, const int& x_input, const int& y_input, const piece_color& current_color);
	void print_piece_easyx(const int& interval, const int& instruct_size, const int& piece_size, const Piece& piece);
};
/*
Board::Board(int size = 0) :
	_pboard(size, std::vector<Piece>(size)),
	_pboard_status(size, std::vector<int>(size)) { 
	_size = size;
}

Board::Board(const Board& board) :
	_pboard(board._size, std::vector<Piece>(board._size)),
	_pboard_status(board._size, std::vector<int>(board._size)) {
	_size = board._size;
}
Board::~Board() {
}
void Board::operator= (const Board& board) {
	_size = board._size;
	_pboard = board._pboard;
	_pboard_status = board._pboard_status;
}

void Board::init_board() {
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_pboard[i][j].set_coord(i, j);
		}
	}
}
void Board::set_piece(piece_color color, int x, int y) {
	_pboard[x][y].set_color(color);
}
void Board::set_piece(const Piece& piece) {
	_pboard[piece.get_x()][piece.get_y()].set_color(piece.get_color());
}
bool Board::if_win(const piece_color color, const int a, const int b) {
	int i, j;

	//横向
	for (i = a - 4, j = b; i <= a; i++) {
		if (i > 0 && i < 16 && 
			_pboard[i][j].get_color() == _pboard[i + 1][j].get_color() == _pboard[i + 2][j].get_color() == _pboard[i + 3][j].get_color() == _pboard[i + 4][j].get_color() != NONE) {
			return 1;
		}
	}

	//纵向
	for (i = a, j = b - 4; j <= b; j++) {
		if (j > 0 && j < 16 && 
			_pboard[i][j].get_color() == _pboard[i][j + 1].get_color() == _pboard[i][j + 2].get_color() == _pboard[i][j + 3].get_color() == _pboard[i][j + 4].get_color() != NONE) {
			return 1;
		}
	}

	//右下
	for (i = a - 4, j = b - 4; i <= a || j <= b; i++, j++) {
		if (i > 0 && i < 16 && j > 0 && j < 16 && 
			_pboard[i][j].get_color() == _pboard[i + 1][j + 1].get_color() == _pboard[i + 2][j + 2].get_color() == _pboard[i + 3][j + 3].get_color() == _pboard[i + 4][j + 4].get_color() != NONE) {
			return 1;
		}
	}

	//左下
	for (i = a - 4, j = b + 4; i <= a || j >= b; i++, j--) {
		if (i > 0 && i < 16 && j > 0 && j < 16 && 
			_pboard[i][j].get_color() == _pboard[i + 1][j - 1].get_color() == _pboard[i + 2][j- 2].get_color() == _pboard[i + 3][j - 3].get_color() == _pboard[i + 4][j - 4].get_color() != NONE) {
			return 1;
		}
	}

	return 0;
}
void Board::load_kifu(Kifu& kifu) {
	int length = kifu.get_length();
	for (int i = 1; i < length; i++) {
		set_piece(kifu.get_piece(i));
	}
}
*/
#endif // !_BOARD_H_
