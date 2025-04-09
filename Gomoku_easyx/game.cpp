// the most important API is get_coord()
// the piece_color in game() is pre-determined, no need to seed parameter
#include "game.h"

// board operating parameters
	const int default_size = 15;
	const Piece zero_piece{ NONE, -1, -1 };
	const int refreash_frequency = 10;			// reload the kifu to board every 10 while circulation
	const int max_move = default_size * default_size;
	static bool get_new_piece = false;
	static int x_coord;
	static int y_coord;
	int x_input;
	int y_input;
	static int x_mouse_pointing;
	static int y_mouse_pointing;
	static int x_mouse_pointed;
	static int y_mouse_pointed;
	int x_remain;
	int y_remain;
	static piece_color current_color = BLACK_PIECE;

	static bool confirm_negedge_indicator = true;
	static bool Lbutton_negedge_indicator = true;

// board graphic parameters
	const int interval = 25;
	int length = default_size * interval;
	const int stone_size = 10;
	const int instruct_size = 2;
	const double mouse_precision = 0.3;
	const COLORREF default_line_color = BLACK;
	const COLORREF default_instruct_color = YELLOW;

// function prototypes
	void init_board(Board& board);
	void get_coord_console(int& x, int& y);
	piece_color to_opponent(const piece_color& color);
	void mouse_get_piece(ExMessage& msg, Board& board, Piece& new_piece);
	void flush_board(Board& board, Piece& new_piece);
	void flush_board(Board& board, Kifu& new_kifu);
	void set_piece_reminder(SMessageBox& smb, piece_color current_color, int& move);
	void multiple_game();

;
// the  return of piece_color indicates the winning side
piece_color game() {
	setlocale(LC_ALL, "");
	// board configures
	Board board(default_size);
	Piece new_piece;
	current_color = BLACK_PIECE;
	Kifu new_kifu;
	int move = 1;
	IMAGE img_bk;
	HWND get_hwnd = GetHWnd();
	COLORREF bk_color = RGB(0xff, 0xcd, 0x96);
	
	// graphic configures
	initgraph(600, 600, EX_SHOWCONSOLE);
	setbkcolor(bk_color);
	cleardevice();
	//loadimage(&img_bk, _T("./board_bk.jpg"));
	//putimage(0, 0, &img_bk);
	SetWindowText(get_hwnd, L"五子棋");
	
	Button button_resign(450, 200, 100, 30, L"投子认负");
	Button button_retract(450, 250, 100, 30, L"悔  棋");
	Button button_confirm(400, 450, 100, 30, L"确认落子");
	
	TextBox textbox_x(100, 450, 120, 30, L"输入横坐标");
	TextBox textbox_y(250, 450, 120, 30, L"输入纵坐标");
	SMessageBox smbox(100, 500, 400, 30, L"第1手 黑方落子");
	// information configures
	ExMessage msg;

	// board initiative module
		board.init_board();
		//board.print_board_console();
		board.print_board_easyx(interval, instruct_size, bk_color, default_line_color);
	while (1) {
	// coordination input module: can be adjust to easyx module or windows module
		//get_coord_console(x_coord, y_coord);
		peekmessage(&msg, -1);
		button_resign.run(msg);
		button_confirm.run(msg);
		button_retract.run(msg);
		textbox_x.run(msg);
		textbox_y.run(msg);
		smbox.run();
		flush_board(board, new_piece);
		// resign working area
			if (button_resign.run(msg)) {
				if (current_color == BLACK_PIECE) {
					smbox.edit_text(L"第" + std::to_wstring(move) + L"手 " + L"黑方认输，白方中盘胜");
					std::cout << "WHILE WIN BY RESIGNATION" << std::endl;
					smbox.run();
				}
				if (current_color == WHITE_PIECE) {
					smbox.edit_text(L"第" + std::to_wstring(move) + L"手 " + L"白方认输，黑方中盘胜");
					std::cout << "BLACK WIN BY RESIGNATION" << std::endl;
					smbox.run();
				}
				current_color = to_opponent(current_color);
				return current_color;
				break;
			}
		// retract working area
			if (!button_retract.run(msg) && !button_confirm.run(msg)) {
				confirm_negedge_indicator = true;
			}
			else if (button_retract.run(msg) && confirm_negedge_indicator) {
				confirm_negedge_indicator = false;
				if (new_kifu.get_length() == 0) {
					std::cout << "No piece to retract" << std::endl;
					smbox.edit_text(L"没有落子，无法悔棋");
					smbox.run();
				}
				else {
					new_kifu.retract_piece();
					board.get_board()[new_piece.get_x()][new_piece.get_y()] = zero_piece;
					board.erase_piece_easyx(interval, instruct_size, stone_size, new_piece.get_x() + 1, new_piece.get_y() + 1, bk_color, default_line_color);
					new_piece = new_kifu.get_piece(new_kifu.get_length());		
					std::cout << "new piece set to previous" << std::endl;
					move--;
					set_piece_reminder(smbox, current_color, move);
					current_color = to_opponent(current_color);
					// board.print_board_easyx(interval, instruct_size, bk_color, default_line_color);
					// flush_board(board, new_piece);
					std::cout << "board easyx reflushed" << std::endl;
				}
			}

		//input from mouse click
			mouse_get_piece(msg, board, new_piece);
		// confirm working area
			// input from textbox
			if (!button_retract.run(msg) && !button_confirm.run(msg)) {
				confirm_negedge_indicator = true;
			}
			if (button_confirm.run(msg) && confirm_negedge_indicator) {	// get input to coordination
				confirm_negedge_indicator = false;
				get_new_piece = true;
				std::wstring x_coord_wchar;
				std::wstring y_coord_wchar;
				x_coord_wchar = textbox_x.get_text();
				y_coord_wchar = textbox_y.get_text();
				try {
					x_coord = std::stoi(x_coord_wchar);
					std::wcout << L"Converted number: " << x_coord << std::endl;
				}
				catch (const std::invalid_argument& e) {
					std::wcerr << L"Invalid argument: " << e.what() << std::endl;
				}
				catch (const std::out_of_range& e) {
					std::wcerr << L"Out of range: " << e.what() << std::endl;
				}
				try {
					y_coord = std::stoi(y_coord_wchar);
					std::wcout << L"Converted number: " << y_coord << std::endl;
				}
				catch (const std::invalid_argument& e) {
					std::wcerr << L"Invalid argument: " << e.what() << std::endl;
				}
				catch (const std::out_of_range& e) {
					std::wcerr << L"Out of range: " << e.what() << std::endl;
				}
				textbox_x.clear_text();
				textbox_x.run(msg);
				textbox_y.clear_text();
				textbox_y.run(msg);
				x_input = x_coord - 1;
				y_input = y_coord - 1;
				new_piece.set(current_color, x_input, y_input);
			}
			
			
			if (!get_new_piece) {
				continue;
			}
		// 下一步可以把创建bool get_input(ExMessage& msg)，把上述过程放到这个函数里面，但是会重复出现button.run()作为判断条件
		// 所以函数编写方式有待研究
		// input on-board module
			
			
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
			board.print_piece_easyx(interval, instruct_size, stone_size, x_coord, y_coord, current_color);
			flush_board(board, new_piece);
			set_piece_reminder(smbox, current_color, move);
			//board.print_board_console();
			//new_kifu.print_kifu();
		// winning check module
			if (board.if_win(new_piece)) {
				if (new_piece.get_color() == BLACK_PIECE) {
					smbox.edit_text(L"第" + std::to_wstring(move - 1) + L"手 " + L"黑方连珠胜");
					std::cout << "BLACK WIN BY MAKING FIVE" << std::endl;
					smbox.run();
					break;
				}
				if (new_piece.get_color() == WHITE_PIECE) {
					smbox.edit_text(L"第" + std::to_wstring(move - 1) + L"手 " + L"白方连珠胜");
					std::cout << "WHITE WIN BY MAKING FIVE" << std::endl;
					smbox.run();
					break;
				}
				/*std::cout << "view kifu?[Y/N]\n";
				char ch = getchar();
				if (ch == 'Y' || ch == 'y')
					new_kifu.print_kifu();*/
				//return current_color;
			}
			if (!(move < max_move)) {
				smbox.edit_text(L"和棋");
				smbox.run();
				current_color = NONE;
				break;
			}
			current_color = to_opponent(current_color);
	}
	if (new_piece.get_color() == BLACK_PIECE) {
		smbox.edit_text(L"BLACK WIN BY MAKING FIVE");
		std::cout << "BLACK WIN BY MAKING FIVE" << std::endl;
	}
	if (new_piece.get_color() == WHITE_PIECE) {
		smbox.edit_text(L"WHITE WIN BY MAKING FIVE");
		std::cout << "WHITE WIN BY MAKING FIVE" << std::endl;
	}
	std::cout << "view kifu?[Y/N]\n";
	char ch;
	std::cin >> ch;
	if (ch == 'Y' || ch == 'y')
		new_kifu.print_kifu();
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
void flush_board(Board& board, Kifu& new_kifu) {
	// 将键盘信息刷新到界面，但是因为是遍历，所以要少用
	Piece new_piece = new_kifu.get_piece(new_kifu.get_length());
	for (int i = 0; i < default_size; i++) {
		for (int j = 0; j < default_size; j++) {
			if (board.get_board()[i][j].get_color() == NONE) {
				setfillcolor(default_line_color);
				solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
			}
			if (board.get_board()[i][j].get_color() == BLACK_PIECE) {
				setfillcolor(BLACK);
				solidcircle((i + 1) * interval, (j + 1) * interval, stone_size);
				if (board.get_board()[i][j] == new_piece) {
					setfillcolor(YELLOW);
					solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
				}
			}
			if (board.get_board()[i][j].get_color() == WHITE_PIECE) {
				setfillcolor(WHITE);
				solidcircle((i + 1) * interval, (j + 1) * interval, stone_size);
				if (board.get_board()[i][j] == new_piece) {
					setfillcolor(RED);
					solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
				}
			}
		}
	}
}
void flush_board(Board& board, Piece& new_piece) {
	// 将键盘信息刷新到界面，但是因为是遍历，所以要少用
	for (int i = 0; i < default_size; i++) {
		for (int j = 0; j < default_size; j++) {
			if (board.get_board()[i][j].get_color() == NONE) {
				setfillcolor(default_line_color);
				solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
			}
			if (board.get_board()[i][j].get_color() == BLACK_PIECE) {
				setfillcolor(BLACK);
				solidcircle((i + 1) * interval, (j + 1) * interval, stone_size);
				if (board.get_board()[i][j] == new_piece) {
					setfillcolor(YELLOW);
					solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
				}
			}
			if (board.get_board()[i][j].get_color() == WHITE_PIECE) {
				setfillcolor(WHITE);
				solidcircle((i + 1) * interval, (j + 1) * interval, stone_size);
				if (board.get_board()[i][j] == new_piece) {
					setfillcolor(RED);
					solidcircle((i + 1) * interval, (j + 1) * interval, instruct_size);
				}
			}
		}
	}
	//std::cout << "board on easyx flushed" << std::endl;
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
// 文本框输入落子
// 鼠标输入落子
void mouse_get_piece(ExMessage& msg, Board& board, Piece& new_piece) {
	
	if (msg.message == WM_LBUTTONUP) {
		if (!Lbutton_negedge_indicator) {
			Lbutton_negedge_indicator = true;
		}
	}
	if (msg.message != WM_LBUTTONDOWN) {
		if (msg.x >= (default_size + 0.5) * interval || msg.x <= 0.5 * interval || msg.y >= (default_size + 0.5) * interval || msg.y <= interval * 0.5) {
			return;	// 如果鼠标在范围之外直接停止扫描，减少时间消耗
		}
		
		x_mouse_pointing = msg.x / interval;
		y_mouse_pointing = msg.y / interval;
		x_remain = msg.x % interval;
		y_remain = msg.y % interval;
		if (x_remain > mouse_precision * interval && x_remain < interval - mouse_precision * interval ||
			y_remain > mouse_precision * interval && y_remain < interval - mouse_precision * interval) {
			flush_board(board, new_piece);
			return;
		}
		if (x_remain > interval - mouse_precision * interval) {
			x_mouse_pointing++;
		}
		if (y_remain > interval - mouse_precision * interval) {
			y_mouse_pointing++;
		}
		if (x_mouse_pointed != x_mouse_pointing || y_mouse_pointed != y_mouse_pointing) {
			setfillcolor(BLACK);
			solidcircle((x_mouse_pointed) * interval, (y_mouse_pointed) * interval, instruct_size);
			x_mouse_pointed = x_mouse_pointing;
			y_mouse_pointed = y_mouse_pointing;
		}
		setfillcolor(YELLOW);
		solidcircle((x_mouse_pointed) * interval, (y_mouse_pointed) * interval, instruct_size);
	}
	else if (msg.message == WM_LBUTTONDOWN && Lbutton_negedge_indicator == true) {
		//std::cout << "mouse clicked" << std::endl;
		Lbutton_negedge_indicator = false;
		x_coord = msg.x / interval;
		y_coord = msg.y / interval;
		x_remain = msg.x % interval;
		y_remain = msg.y % interval;
		if (x_remain > mouse_precision * interval && x_remain < interval - mouse_precision * interval ||
			y_remain > mouse_precision * interval && y_remain < interval - mouse_precision * interval) {
			return;
		}
		else {
			get_new_piece = true;
			//std::cout << "mouse input" << std::endl;
			if (x_remain > interval - mouse_precision * interval) {
				x_coord++;
			}
			if (y_remain > interval - mouse_precision * interval) {
				y_coord++;
			}
		}
		x_input = x_coord - 1;
		y_input = y_coord - 1;
		new_piece.set(current_color, x_input, y_input);
	}
}
void set_piece_reminder(SMessageBox& smb, piece_color current_color, int& move) {
	if (current_color == BLACK_PIECE) {
		smb.edit_text(L"第"+std::to_wstring(move) + L"手 " + L"白方落子");
	}
	else if (current_color == WHITE_PIECE) {
		smb.edit_text(L"第" + std::to_wstring(move) + L"手 " + L"黑方落子");
	}
}

void multiple_game() {
	bool game_status = true;
	piece_color winning_color = NONE;
	int black_score = 0;
	int white_score = 0;
	std::wstring messagebox_msg;

	while (game_status) {
		winning_color = game();
		HWND get_hwnd = GetHWnd();
		SetWindowText(get_hwnd, L"五子棋");
		if (winning_color == BLACK_PIECE) {
			black_score++;
			messagebox_msg = L"黑方胜利，双方比分：" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"再来一局？";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"提示", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == WHITE_PIECE) {
			white_score++;
			messagebox_msg = L"白方胜利，双方比分：" + std::to_wstring(black_score) + L":" + std::to_wstring(white_score) + L"再来一局？";
			int isok = MessageBox(get_hwnd, messagebox_msg.c_str(), L"提示", MB_OKCANCEL);
			if (IDCANCEL == isok)
			{
				game_status = false;
			}
		}
		else if (winning_color == NONE) {
			int isok = MessageBox(get_hwnd, L"平局，再来一局？", L"提示", MB_OKCANCEL);
			if (isok == IDOK)
			{
				printf("你点击了OK\n");
			}
			else if (IDCANCEL == isok)
			{
				printf("你点击了取消\n");
				game_status = false;
			}
		}
	}
	std::cout << "Press enter to exit" << std::endl;
	//std::cout << std::wstring(L"按下回车键退出").c_str() << std::endl;
	closegraph();
}