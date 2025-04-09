#include "kifu.h"

Kifu::Kifu() {
}
Kifu::~Kifu() {
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
	this->List<Piece>::Insert(piece, this->ablist<Piece>::GetLength());
}
void Kifu::retract_piece() {
	Remove_index(ablist<Piece>::length);
	std::cout << "piece removed" << std::endl;
}
Piece Kifu::get_piece(int i) {
	Piece result;
	result = this->Find_index(i)->data;
	return result;
}
void Kifu::print_kifu() {
	ListNode<Piece>* current_node = this->head;
	while (current_node != nullptr) {
		std::cout << current_node->get_data();
		current_node = List<Piece>::GetNext(*current_node);
	}
}