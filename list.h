#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both m_head and m_tail pointers
// and the m_size of the list.  Note that you have to keep the m_head,
// m_tail and m_size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Item>
class List {
public:

	List();

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item &item);
	void	push_rear(const Item &item);
	void	insert(int index, const Item &item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Item	front() const;
	Item	rear() const;
	Item	get(int index) const;

	int		size() const;
	int		find(const Item &item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both m_head and m_tail points for 
	// Fast insertion/deletion from both ends.
	Node*	m_head;
	Node*	m_tail;

	// Keep track of number of nodes in the list
	int		m_size;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual 
//  class yet, not until we actually instantiate the list) 
//  we need to keep the implementation together with 
//  the definition.  There are ways to simulate having 
//  separate "implementation/definition" with templates, 
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Item>
class List<Item>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};



/* List default constructor
//		Set m_head and m_tail pointer to point to nothing, m_size is zero
//		Already implemented, nothing to do.
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}


/* Copy constructor  
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {
	/* TODO */
	if (other.empty()) {
		this->m_size = 0;
		this->m_tail = nullptr;
		this->m_head = nullptr;
	}
	else
	{
		Node* temp = other.m_head;
		for (int i = 0; i < other.m_size; i++) {
			this->push_rear(temp->item);
			temp = temp->next;
		}
	}
}
/* Overloaded assignment operator 
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	/* TODO */
	if (this == &other) {
		return *this;
	}else
	{
		//delete the current one
		Node* kill;
		while (m_tail != nullptr) {
			kill = m_tail;
			m_tail = m_tail->prev;
			delete kill;
			m_size--;
		}
		m_head = nullptr;
		m_tail = nullptr;
		//generate the new node
		Node* temp = other.m_head;
		for (int i = 0; i < other.m_size; i++) {
			this->push_rear(temp->item);
			temp = temp->next;
		}
	}
	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	/* TODO */
	Node* temp;
	while (m_tail != nullptr) {
		temp = m_tail;
		m_tail = m_tail->prev;
		delete temp;
		m_size--;
	}
	m_head = nullptr;
	m_tail = nullptr;
}

/* List print
*/		
template<typename Item>
void List<Item>::print() const {
	/* TODO */
	if (!empty()) {
		using namespace std;
		Node* it = m_head;

		if (m_size == 1) {
			cout << it->item <<endl;
		}else{
			while (it != m_tail) {
				cout << it->item << " ";
				it = it->next;
				}
			cout << it->item << endl;
			}
	}
	return;
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
	/* TODO */
	return m_size == 0;
}


/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item &item) {
	/* TODO */
	if (this->empty()) {
		Node* temp = new Node;
		temp->item = item;
		m_head = temp;
		m_tail = temp;
	}
	else {
		Node* temp = new Node;
		temp->item = item;
		temp->next = m_head;
		m_head->prev = temp;
		m_head = temp;
	}
	m_size++;
}

/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item &item) {
	/* TODO */
	if (this->empty()) {
		Node* temp = new Node;
		temp->item = item;
		m_head = temp;
		m_tail = temp;
	}
	else {
		//not empty
		Node* temp = new Node;
		temp->item = item;
		temp->prev = m_tail;
		m_tail->next = temp;
		m_tail = temp;
	}
	m_size++;
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item &item) {
	/* TODO */
	if (index <= 0) {
		push_front(item);
	}
	else if (index >= this->size()) {
		push_rear(item);
	}
	else
	{
		Node* it = m_head;
		for (int i = 0; i < index; i++) {
			it = it->next;
		}
		Node* add = new Node(item,it->prev,it);
		it->prev->next = add;
		it->prev = add;
		m_size++;
	}
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {
	// Force check that the m_head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_head != nullptr); 

	/* TODO */

	return m_head->item;
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {

	// Force check that the m_tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_tail != nullptr);

	/* TODO */
	
	return m_tail->item;
	
}

/* List get
//		returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < m_size);

	/* TODO */
	Node* findit = m_head;
	for (int i = 0; i < index; i++) {
		findit = findit->next;
	}
	return findit->item;
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
	/* TODO */
	return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item &item) const {

	if (empty()) {
		return -1;
	}
	else {
		int index = 0;
		Node* it = m_head;
		while (it != nullptr) {
			if (it->item == item) {
				return index;
			}
			else {
				it = it->next;
				index++;
			}
		}
		//end of list, doesn't find it --> doesn't exist
		return -1;
	}
}

/* List pop_front
*/		
template<typename Item>
bool List<Item>::pop_front() {

	/* TODO */
	if (empty()) {
		return false;
	}
	if (m_size == 1) {
		delete m_head;
		this->m_head = nullptr;
		this->m_tail = nullptr;
		m_size--;
		return true;
	}
	else {
		Node* kill = m_head;
		m_head = m_head->next;
		m_head->prev = nullptr;
		delete kill;
		m_size--;
		return true;
	}
}

/* List pop_rear
*/	
template<typename Item>
bool List<Item>::pop_rear() {
	/* TODO */
	if (empty()) {
		return false;
	}
	if (m_size == 1) {
		delete m_tail;
		this->m_head = nullptr;
		this->m_tail = nullptr;
		m_size--;
		return true;
	}
	else {
		Node* kill = m_tail;
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
		delete kill;
		m_size--;
		return true;
	}
}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {

	/* TODO */
	if (index > m_size || index < 0) {
		return false;
	}
	Node* kill = m_head;
	for (int i = 0; i < index; i++) {
		kill = kill->next;
	}
	if (kill == m_head) {
		pop_front();
	}else if (kill == m_tail) {
		pop_rear();
	}else {
		//kill the middle one is trickly
		kill->prev->next = kill->next;
		kill->next->prev = kill->prev;
		delete kill;
		m_size--;	
	}
	return true;
}







































































#endif // _X_XMMXX