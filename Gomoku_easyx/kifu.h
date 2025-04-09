#ifndef _KIFU_H_
#define _KIFU_H_
#include "cpplist.h"
#include "piece.h"

class Kifu :
	public List<Piece> {
public:
	Kifu();
	~Kifu();
	Kifu(const Kifu& kifu);
	Kifu& CopyKifu(const Kifu& kifu);
	void operator= (const Kifu& kifu);
	int get_length() const { return ablist<Piece>::length; }

	void set_piece(const Piece& piece);	
	void retract_piece();
	Piece get_piece(int i);
	void print_kifu();
};


#endif 