#include "kifu.h"

Kifu::Kifu() {
	_phead = nullptr;
}
Kifu::~Kifu() {
	delete[] _phead;
}
Kifu::Kifu(const Kifu& kifu) {
	CopyKifu(kifu);
}
Kifu& Kifu::CopyKifu(const Kifu& kifu) {
	if (this != &kifu) {
		this->Kifu::List<Piece>::Copy(kifu);
	}
	return *this;
}
void Kifu::operator= (const Kifu& kifu) {
	if (this != &kifu) {
		this->List<Piece>::Copy(kifu);
	}
}

void Kifu::set_piece(const Piece& piece) {
	this->List<Piece>::Insert(piece, this->ablist<Piece>::GetLength() + 1);
}
void Kifu::retract_piece() {
	Remove_index(ablist<Piece>::length);
}
Piece Kifu::get_piece(int i) {
	Piece result;
	result = this->Find_index(i)->data;
	return result;
}
void Kifu::print_kifu() {
	ListNode<Piece>* current_node = _phead;
	while (List<Piece>::GetNext(*current_node)->next != nullptr) {
		std::cout << current_node->data << std::endl;
		current_node = List<Piece>::GetNext(*current_node);
	}
}
