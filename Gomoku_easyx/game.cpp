// the most important API is get_coord()
// the piece_color in game() is pre-determined, no need to seed parameter



// board operating parameters
	const int default_size = 15;
	const Piece zero_piece{ NONE, -1, -1 };
	const int refreash_frequency = 10;			// reload the kifu to board every 10 while circulation
	const int max_move = default_size * default_size;
	bool get_new_piece = false;
	int x_coord;
	int y_coord;
	int x_input;
	int y_input;
	int x_remain;
	int y_remain;
	static piece_color current_color = BLACK_PIECE;

	static bool confirm_negedge_indicator = true;
	static bool Lbutton_negedge_indicator = true;

// board graphic parameters
	/*const int interval = 25;
	int length = default_size * interval;
	const int stone_size = 10;
	const int instruct_size = 2;
	const double mouse_precision = 0.3;
	const COLORREF default_line_color = BLACK;
	const COLORREF default_instruct_color = YELLOW;*/

// function prototypes
	void init_board(Board& board);
	void get_coord_console(int& x, int& y);
	piece_color to_opponent(const piece_color& color);
;
// the  return of piece_color indicates the winning side
piece_color game() {
	// setlocale(LC_ALL, "");
	// board configures
	Board board(default_size);
	Piece new_piece;
	current_color = BLACK_PIECE;
	Kifu new_kifu;
	int move = 1;

	// board initiative module
		board.init_board();
		board.print_board_console();
	while (1) {
	// coordination input module: can be adjust to easyx module or windows module
		get_coord_console(x_coord, y_coord);
		// 下一步可以把创建bool get_input(ExMessage& msg)，把上述过程放到这个函数里面，但是会重复出现button.run()作为判断条件
		// 所以函数编写方式有待研究
		// input on-board module
			x_input = x_coord - 1;
			y_input = y_coord - 1;
			new_piece.set(current_color, x_input, y_input);
			
			get_new_piece = false;
		
			if (!board.check_piece_range(new_piece)) {
				continue;
			}
			if (!board.check_piece_repeat(new_piece)) {
				continue;
			}
			board.set_piece(new_piece);
			new_kifu.set_piece(new_piece);
			move++;
			board.print_board_console();
			//new_kifu.print_kifu();
		// winning check module
			if (board.if_win(new_piece)) {
				if (new_piece.get_color() == BLACK_PIECE) {
					std::cout << "BLACK WIN BY MAKING FIVE" << std::endl;
				}
				if (new_piece.get_color() == WHITE_PIECE) {
					std::cout << "WHITE WIN BY MAKING FIVE" << std::endl;
				}
				/*std::cout << "view kifu?[Y/N]\n";
				char ch = getchar();
				if (ch == 'Y' || ch == 'y')
					new_kifu.print_kifu();*/
				return current_color;
			}
			if (!(move < max_move)) {
				std::cout << "A DRAW" << std::endl;
				return NONE;
			}
			current_color = to_opponent(current_color);
	}
	if (new_piece.get_color() == BLACK_PIECE) {
		std::cout << "BLACK WIN BY MAKING FIVE" << std::endl;
	}
	if (new_piece.get_color() == WHITE_PIECE) {
		std::cout << "WHITE WIN BY MAKING FIVE" << std::endl;
	}
	/*std::cout << "view kifu?[Y/N]\n";
	char ch;
	std::cin >> ch;
	if (ch == 'Y' || ch == 'y')
		new_kifu.print_kifu();*/
	return current_color;
}

;
// function declaration
void init_board(Board& board) {
	for (int i = 0; i < default_size; i++) {
		for (int j = 0; j < default_size; j++) {
			board.set_piece(zero_piece);
		}
	}
}
// 这个是最重要的外部接口
void get_coord_console(int& x, int& y) {
	std::cin >> x >> y;
}
// 每下一步就选择反色
piece_color to_opponent(const piece_color& color) {
	if (color == BLACK_PIECE) {
		return WHITE_PIECE;
	}
	else if (color == WHITE_PIECE) {
		return BLACK_PIECE;
	}
	else
		return NONE;
}