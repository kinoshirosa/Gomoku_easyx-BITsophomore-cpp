configuration
	|
	----enum piece_color {NONE, BLACK, WHITE}
	----cpplist.h
	----class piece
		|
		---- variable: 
				piece_color _color;
				int x;
				int y;
		---- functions:
	----class kifu: piece chain list
	----class pieceboard: a matrix, using vector<vector<piece_color>>
	----function start_game
		|
		----function init_game: create a board or set current board to {0}