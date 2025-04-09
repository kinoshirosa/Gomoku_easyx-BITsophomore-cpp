#ifndef _GAME_H_
#define _GAME_H_

#include "piece.h"
#include "board.h"
#include "messagebox.h"
#include "button.h"
#include "textbox.h"
#include "kifu.h"
#include <iostream>
#include <windows.h>
#include <locale.h>

extern int x_coord;
extern int y_coord;
extern piece_color current_color;

piece_color game();

#endif