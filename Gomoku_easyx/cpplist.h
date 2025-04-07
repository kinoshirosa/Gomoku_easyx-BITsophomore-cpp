#ifndef CPPLIST_H_
#define CPPLIST_H_

#include "ablinklist.h"
#include <iostream>
#include "piece.h"

template<class type>
class List
	: public ablinklist<type> {
public:
	List() { this->head = new ListNode<type>; this->length = 0; }
	List(List<type>& l) { Copy(l); }
	~List() { MakeEmpty(); delete this->head; }
	void MakeEmpty() { ablinklist<type>::MakeEmpty(); }
	bool Insert(type value, int i = 1);
	bool Remove_index(int i);
	bool Remove_value(type value);
	List<type>& Copy(const List<type>& l);
	List<type>& operator= (List<type>& l);
	friend std::ostream& operator<< (std::ostream&, List<type>&);
};

template<class type>
bool List<type>::Insert(type value, int i) {
	ListNode<type>* p = ablinklist<type>::Find_index(i - 1);
	if (p == nullptr)
		return false;
	ListNode<type>* newnode = new ListNode<type>(value, p->next);
	assert(newnode);
	if (newnode == nullptr)
		return false;
	p->next = newnode;
	this->length++;
	return true;
}

template<class type>
bool List<type>::Remove_index(int i) {
	ListNode<type>* p = ablinklist<type>::Find_index(i - 1), * q;
	assert(p && p->next);
	if (p == nullptr || p->next == nullptr) {
		std::cout << "index out of range" << std::endl;
		return false;
	}
	q = p->next;
	p->next = q->next;
	delete q;
	this->length--;
	return true;
}

//	the Remove_value() on the textbook only remove one of the value in linklist
//	shall we try to remove all
template<class type>
bool List<type>::Remove_value(type value) {
	ListNode<type>* p = this->head, * q;
	int indicator = 0;
	while (p->next != nullptr) {
		if (p->next->data == value) {
			q = p->next;
			p->next = q->next;
			delete q;
			indicator++;
			this->length--;
		}
		else {
			p = p->next;
		}
	}
	if (!indicator) {
		std::cout << "NO element with such value eliminated!\n";
		return false;
	}
	std::cout << indicator << "element(s) with such value were eliminated!\n";
	return true;
}

template<class type>
List<type>& List<type>::Copy(const List<type>& l) {
	ListNode<type>* q, * p, * r;
	this->length = l.length;
	this->head = nullptr;
	if (!l.head) {
		return *this;
	}
	this->head = new ListNode<type>;
	if (!this->head)
		return *this;
	this->head->data = (l.head)->data;
	this->head->next = nullptr;
	r = nullptr;
	p = this->head;
	q = l.head->next;
	while (q) {
		r = new ListNode<type>;
		if (!r) {
			return *this;
		}
		r->data = q->data;
		r->next = nullptr;
		p->next = r;
		p = p->next;
		q = q->next;
	}
	return *this;
}

template<class type>
List<type>& List<type>::operator= (List<type>& l) {
	if (this->head)
		MakeEmpty();
	Copy(l);
	return *this;
}

template <class type>
std::ostream& operator<< (std::ostream& os, List<type>& l) {
	ListNode<type>* p = l.head->next;
	os << "length: " << l.length << "\ndata: ";
	while (p) {
		os << p->data << " ";
		p = p->next;
	}
	os << "\ndata display over!" << std::endl;
	return os;
}
#endif