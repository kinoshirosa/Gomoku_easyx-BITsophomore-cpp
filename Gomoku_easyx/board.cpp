#include "board.h"
#include <cstdlib>
#include <stdio.h>
#include <string>

Board::Board(int size) :
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
bool Board::set_piece(piece_color color, int x, int y) {
	if (x > _size - 1 || x < 0 || y > _size - 1 || y < 0) {
		std::cout << "PIECE EXCEEDED RANGE" << std::endl;
		return false;
	}
	_pboard[x][y].set_color(color);
	return true;
}
bool Board::set_piece(const Piece& piece) {
	return set_piece(piece.get_color(), piece.get_x(), piece.get_y());
}
bool Board::check_piece_range(int x, int y) {
	if (x < 0 || x > _size - 1 || y < 0 || y > _size - 1) {
		std::cout << "DO NOT EXCEED BOARD RANGE" << std::endl;
		return false;
	}
	return true;
}
bool Board::check_piece_range(const Piece& piece) {
	return check_piece_range(piece.get_x(), piece.get_y());
}
bool Board::check_piece_repeat(int x, int y) {
	if (_pboard[x][y].get_color() == NONE) {
		return true;
	}
	std::cout << "DO NOT SET ON REPEATED PLACE" << std::endl;
	return false;
}
bool Board::check_piece_repeat(const Piece& piece) {
	return check_piece_repeat(piece.get_x(), piece.get_y());
}
bool Board::if_win(const piece_color color, const int a, const int b) {
	int i, j;
	int interval = 25;
	int instruct_size = 2;
	//横向
	for (i = a - 4, j = b; i <= a; i++) {
		if (i >= 0 && i < _size - 4 &&
			(_pboard[i][j].get_color() == _pboard[i + 1][j].get_color()) && 
			(_pboard[i][j].get_color() == _pboard[i + 2][j].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 3][j].get_color()) && 
			(_pboard[i][j].get_color() == _pboard[i + 4][j].get_color()) &&
			_pboard[i][j].get_color() != NONE) {
			return 1;
		}
	}

	//纵向
	for (i = a, j = b - 4; j <= b; j++) {
		if (j >= 0 && j < _size - 4 &&
			(_pboard[i][j].get_color() == _pboard[i][j + 1].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i][j + 2].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i][j + 3].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i][j + 4].get_color()) &&
			_pboard[i][j].get_color() != NONE) {
			return 1;
		}
	}

	//右下
	for (i = a - 4, j = b - 4; i <= a || j <= b; i++, j++) {
		if (i >= 0 && i < _size - 4 && j >= 0 && j < _size - 4 &&
			(_pboard[i][j].get_color() == _pboard[i + 1][j + 1].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 2][j + 2].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 3][j + 3].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 4][j + 4].get_color()) &&
			_pboard[i][j].get_color() != NONE) {
			return 1;
		}
	}

	//左下
	for (i = a - 4, j = b + 4; i <= a || j >= b; i++, j--) {
		if (i >= 0 && i < _size - 4 && j >= 4 && j < _size &&
			(_pboard[i][j].get_color() == _pboard[i + 1][j - 1].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 2][j - 2].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 3][j - 3].get_color()) &&
			(_pboard[i][j].get_color() == _pboard[i + 4][j - 4].get_color()) &&
			_pboard[i][j].get_color() != NONE) {
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

void Board::print_board_console() {
	system("cls");
	for (int i = 0; i <= _size; i++) {
		for (int j = 0; j <= _size; j++) {
			if (i == _size) {
				if (j == _size) {
					printf("\n");
					return;
				}
				printf("%c ", j + 'A');
			}
			else if (j == _size) {
				printf("%d", i + 1);
			}
			else if (_pboard[i][j].get_color() == BLACK_PIECE)
				std::cout << "● ";
			else if (_pboard[i][j].get_color() == WHITE_PIECE)
				std::cout << "○ ";
			else if (i == 0 && j == 0)
				std::cout << "┌ "; 
			else if (i == 0 && j == _size - 1)
				std::cout << "┐ ";
			else if (i == _size - 1 && j == 0)
				std::cout << "└ ";
			else if (i == _size - 1 && j == _size - 1)
				std::cout << "┘ ";
			else if (i == 0)
				std::cout << "┬ ";
			else if (i == _size - 1)
				std::cout << "┴ ";
			else if (j == 0)
				std::cout << "├ ";
			else if (j == _size - 1)
				std::cout << "┤ ";
			else
				std::cout << "┼ ";

		}
		std::cout << "\n";
	}
}