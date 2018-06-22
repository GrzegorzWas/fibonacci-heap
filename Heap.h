#pragma once
#define HEAP_EMPTY -2147483647
#define KEY_NOT_FOUND -1
struct Node {
	Node* parent;
	Node* left_sibling;
	Node* right_sibling;
	Node* child;
	int value;
	int degree;
	bool is_looser;

	Node(int value) :parent(nullptr), left_sibling(nullptr),
		right_sibling(nullptr), child(nullptr), 
		degree(0), is_looser(false)
	{
		this->value = value;
	}

};


/**
this class represents Fibonacci extended with additional
functionality of finding and replacing given keys
the assumption is that it contains positive integers
**/
class Heap
{
public:
	/**
	add value to heap
	**/
	void push(int value);

	/**
	deletes max key from heap, performs cleanup and returns 
	deleted key's value
	**/
	int pop_max();

	/**
	merges current heap with other heap by merging their
	root lists
	**/
	void merge_with(Heap* heap);

	/**
	performs search for key
	if key exists in current heap replace it with new key
	otherwise return KEY_NOT_FOUND
	**/
	int replace_key(int key, int new_key);
	
	/**
	prints all keys from heap according to their hierarchy
	**/
	void print_structure();

	/**
	prints all keys from heap in descending order
	**/
	void print();

	Heap();
	~Heap();

private:
	Node* max_root;
	Node* first_root;

	/**
	the same as push although instead of int
	it pushes existing node
	**/
	void push_tree(Node* node);
	void insert_between(Node* left, Node* new_node, Node* right);

	void disconnect(Node* node);
	void cut_out(Node* node);
	
	/**
	disconnect node and deallocate its memory
	**/
	void remove(Node* node);

	void update_max(Node* prev_max);

	/**
	recursive traversal on all of the keys, looking for
	key with specific value
	**/
	Node* find_node_with_key(Node* root, int key);
	
	/**
	merges two trees
	**/
	Node* merge(Node* t1, Node* t2);

	void print_roots();
	void print_structure(Node* root, int indent = 0);
	
	/**
	recursive traversal on all of the keys counting occurence
	count for each one (used for printing in descending order)
	**/
	void fill_print_buffer(Node* root);

	int* print_buffer;
};

