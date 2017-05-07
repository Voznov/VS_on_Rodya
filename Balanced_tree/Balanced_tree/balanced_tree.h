#pragma once

class balanced_tree 
{
private:
	class node
	{
	public:
		int key;
		unsigned int height;
		node* left;
		node* right;
		node* parent;
		node* rotate_right();
		node* rotate_left();
		node* balance();
		signed int balance_factor();
		node* find_min();
		void fix_height();
		node(int _key, node* _parent);
		~node();
		node* insert(int _key);
		node* remove(int _key);
	};
	node* parent_root;
	node* root;
public:
	balanced_tree();
	balanced_tree(balanced_tree &obj);
	~balanced_tree();
	void insert(int key);
	void remove(int key);
	void clear();
	void operator+=(int key);
	void operator-=(int key);
	balanced_tree& operator+(int key);
	balanced_tree& operator-(int key);
	template<class t> void operator+=(t& e);
	template<class t> void operator-=(t& e);
	template<class t> balanced_tree& operator+(t& e);
	template<class t> balanced_tree& operator-(t& e);
	void operator+=(balanced_tree& e);
	void operator-=(balanced_tree& e);
	balanced_tree& operator+(balanced_tree& e);
	balanced_tree& operator-(balanced_tree& e);
	class iterator
	{
	private:
		node* nodeptr = nullptr;
	public:
		iterator(node* ptr) :nodeptr(ptr){}
		iterator();
		int operator*();
		bool operator==(iterator x);
		bool operator!=(iterator x);
		void operator=(node* _node);
		void operator++();
		void operator+=(unsigned int i);
	};
	class const_iterator
	{
		iterator it;
		const_iterator(iterator _it) :it(_it) {}
	};
	iterator begin();
	iterator end();
};

template<class t>
void balanced_tree::operator+=(t& e)
{
 	for (t::iterator it = e.begin(); it != e.end(); ++it)
		this->insert(*it);
}

template<class t>
void balanced_tree::operator-=(t& e)
{
	for (t::iterator it = e.begin(); it != e.end(); ++it)
		this->remove(*it);
}

template<class t>
balanced_tree& balanced_tree::operator+(t& e)
{
	balanced_tree* b = new balanced_tree(*this);
	b->operator+=(e);
	return (*b);
}

template<class t>
balanced_tree& balanced_tree::operator-(t& e)
{
	balanced_tree b(*this);
	b -= e;
	return b;
}
