#ifndef LINKLIST_H_
#define LINKLIST_H_
#include <assert.h>
#include <cstdlib>

template <class type>
class ListNode {
public:
	type data;
	ListNode<type>* next;
public:
	ListNode() { next = nullptr; }
	ListNode(const type& item, ListNode <type>* next1 = nullptr) {
		data = item;
		next = next1;
	}
	type get_data() { return data; }
};

template<class type>
class ablist {
protected:
	int length;
public:
	ablist() { length = 0; };
	int GetLength() { return length; }
	virtual type Get(int i) = 0;
	virtual bool Set(type x, int i) = 0;
	virtual void MakeEmpty() = 0;
	virtual bool Insert(type value, int i) = 0;
	virtual bool Remove_index(int i) = 0;
	virtual bool Remove_value(type value) = 0;
};


template <class type>
class ablinklist
	: public ablist<type> {
protected:
	ListNode<type>* head;
public:
	virtual ~ablinklist() {};
	ListNode<type>* GetHead() { return head; }
	ListNode<type>* GetNext(ListNode<type>& n) {
		return n.next;
	}
	type Get(int i);
	bool Set(type X, int i);
	ListNode<type>* Find_value(type value);
	ListNode<type>* Find_index(int i);
	void MakeEmpty();
	virtual bool Insert(type value, int i) = 0;
	virtual bool Remove_index(int i) = 0;
	virtual bool Remove_value(type value) = 0;
};

template <class type>
bool ablinklist<type>::Set(type x, int i) {
	ListNode<type>* p = Find_index(i);
	if (p == nullptr || p == head) {
		return false;
	}
	else {
		p->data = x;
	}
	return true;
}

template<class type>
type ablinklist<type>::Get(int i) {
	ListNode<type>* p = Find_index(i);
	assert(p && p != head);
	if (p == nullptr || p == head)
		exit(1);
	else
		return p->data;
}

template<class type>
void ablinklist<type>::MakeEmpty() {
	//	keep the head node, then delete every node on the approach
	ListNode<type>* q = head->next;
	int i = 1;
	while (i++ <= this->length) {
		head->next = q->next;	// make head point to the next node, thus the node no longer belongs to the linklist
		delete q;				// but q still point to the node removed, so delete the node by pointer q
		q = head->next;			// circulation of the process
	}
	this->length = 0;
}

template<class type>
ListNode<type>* ablinklist<type>::Find_value(type value) {
	ListNode<type>* p = head->next;
	int i = 1;
	while (i++ <= this->length && p->date != value)
		p = p->next;
	return p;
}

template<class type>
ListNode<type>* ablinklist<type>::Find_index(int i) {
	if (i < 0 || i > this->length)
		return nullptr;
	if (i == 0)
		return head;
	ListNode<type>* p = head->next;
	int j = 1;
	while (p != nullptr && j < i) {
		p = p->next;
		j++;
	}
	return p;
}


#endif