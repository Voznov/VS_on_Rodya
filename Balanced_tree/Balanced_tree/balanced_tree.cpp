#include "balanced_tree.h"

balanced_tree::node* balanced_tree::node::rotate_right()
{
	node* tmp = left;
	
	left = tmp->right;
	if(left)
		left->parent = this;
	tmp->right = this;
	tmp->parent = parent;
	parent = tmp;
	fix_height();
	tmp->fix_height();
	return tmp;
}

balanced_tree::node * balanced_tree::node::rotate_left()
{
	node* tmp = right;
	
	right = tmp->left;
	if(right)
		right->parent = this;
	tmp->left = this;
	tmp->parent = parent;
	parent = tmp;
	fix_height();
	tmp->fix_height();
	return tmp;
}

balanced_tree::node* balanced_tree::node::balance()
{
	fix_height();
	if (balance_factor() == 2)
	{
		if (right->balance_factor() < 0)
			right = right->rotate_right();
		return rotate_left();
	}
	if (balance_factor() == -2)
	{
		if (left->balance_factor() > 0)
			left = left->rotate_left();
		return rotate_right();
	}
	return this;
}

signed int balanced_tree::node::balance_factor()
{
	return (right ? right->height : 0) - (left ? left->height : 0);
}

balanced_tree::node * balanced_tree::node::find_min()
{
	return (left ? left->find_min() : this);
}

void balanced_tree::node::fix_height()
{
	int hl = left ? left->height : 0;
	int hr = right ? right->height : 0;
	height = (hl > hr ? hl : hr) + 1;
}

balanced_tree::node::node(int _key, node* _parent)
{
	key = _key;
	parent = _parent;
	height = 1;
	left = nullptr;
	right = nullptr;
}

balanced_tree::node::~node()
{
	delete left;
	delete right;
}

balanced_tree::node* balanced_tree::node::insert(int _key)
{
	if (_key < key)
	{
		if (!left)
			left = new node(_key, this);
		else
			left = left->insert(_key);
	}
	if (_key > key)
	{
		if (!right)
			right = new node(_key, this);
		else
			right = right->insert(_key);
	}
	
	return balance();
}

balanced_tree::node* balanced_tree::node::remove(int _key)
{
	if (_key < key)
	{
		if (!left)
			return this;
		else
			left = left->remove(_key);
	}
	if (_key > key)
	{
		if (!right)
			return this;
		else
			right = right->remove(_key);
	}
	if (_key == key)
	{
		if (!right)
		{
			node* tmp = left;
			if(tmp)
				tmp->parent = parent;
			left = nullptr;
			delete this;
			return tmp;
		}
		node* min = right->find_min();
		key = min->key;
		if (min->right)
		{
			min->key = min->right->key;
			min = min->right;
		}
		node* tmp = min->parent;
		if (tmp->left == min)
			tmp->left = nullptr;
		else
			tmp->right = nullptr;
		delete min;
		while (tmp != this)
		{
			tmp->balance();
			tmp = tmp->parent;
		}
	}
	return balance();
}

balanced_tree::balanced_tree()
{
	parent_root = new node(0, nullptr); 
	root = nullptr;
	parent_root->left = root;
}

balanced_tree::balanced_tree(balanced_tree & obj)
{
	parent_root = new node(0, nullptr);
	root = nullptr;
	parent_root->left = root;
	for (balanced_tree::iterator it = obj.begin(); it != obj.end(); ++it)
		this->insert(*it);
}

balanced_tree::~balanced_tree()
{
	delete root;
}

void balanced_tree::insert(int key)
{
	if (!root)
	{
		root = new node(key, parent_root);
		parent_root->left = root;
	}
	else
	{
		root = root->insert(key);
		parent_root->left = root;
	}
}

void balanced_tree::remove(int key)
{
	root = root->remove(key);
	parent_root->left = root;
}

void balanced_tree::clear()
{
	delete root;
	root = nullptr;
}

void balanced_tree::operator+=(int key)
{
	this->insert(key);
}

void balanced_tree::operator-=(int key)
{
	this->remove(key);
}

balanced_tree& balanced_tree::operator+(int key)
{
	balanced_tree b(*this);
	b += key;
	return b;
}

balanced_tree& balanced_tree::operator-(int key)
{
	balanced_tree b(*this);
	b -= key;
	return b;
}

void balanced_tree::operator+=(balanced_tree& e)
{
	for (balanced_tree::iterator it = e.begin(); it != e.end(); ++it)
		this->insert(*it);
}

void balanced_tree::operator-=(balanced_tree& e)
{
	for (balanced_tree::iterator it = e.begin(); it != e.end(); ++it)
		this->remove(*it);
}

balanced_tree& balanced_tree::operator+(balanced_tree& e)
{
	balanced_tree b(*this);
	b += e;
	return b;
}

balanced_tree& balanced_tree::operator-(balanced_tree& e)
{
	balanced_tree b(*this);
	b -= e;
	return b;
}

/////////////////////////////////////////////////

balanced_tree::iterator balanced_tree::begin()
{
	return (root ? root->find_min() : nullptr);
}

balanced_tree::iterator balanced_tree::end()
{
	return parent_root;
}

balanced_tree::iterator::iterator()
{
}

int balanced_tree::iterator::operator*()
{
	return (nodeptr ? nodeptr->key : 0);
}

void balanced_tree::iterator::operator=(node * _node)
{
	nodeptr = _node;
}

bool balanced_tree::iterator::operator==(iterator x)
{
	return (this->nodeptr == x.nodeptr);
}

bool balanced_tree::iterator::operator!=(iterator x)
{
	return (this->nodeptr != x.nodeptr);
}

void balanced_tree::iterator::operator++()
{
	if (!nodeptr)
		return;
	if (nodeptr->right)
		nodeptr = nodeptr->right->find_min();
	else
	{
		while (nodeptr->parent->right == nodeptr)
			nodeptr = nodeptr->parent;
		nodeptr = nodeptr->parent;
	}
}

void balanced_tree::iterator::operator+=(unsigned int i)
{
	for (unsigned int j = 0; j < i; ++j)
		this->operator++();
}

balanced_tree::iterator & balanced_tree::iterator::operator+(unsigned int i)
{
	iterator it(*this);
	it += i;
	return it;
}

unsigned int balanced_tree::iterator::operator-(iterator x)
{
	unsigned int result = 0;
	if(nodeptr->key < *x)
		return result;
	iterator _x(x);
	while (operator!=(_x))
	{
		++_x;
		++result;
	}
	return result;
}

