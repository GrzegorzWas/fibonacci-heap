#include "Heap.h"
#include <stdio.h>


Heap::Heap() :max_root(nullptr) {}

Heap::~Heap()
{
	while (max_root != nullptr) {
		pop_max();
	}
}

void Heap::push(int value)
{
	Node* new_node = new Node(value);
	if (max_root == nullptr) {
		max_root = new_node;
		first_root = new_node;
	}
	else
		insert_between(max_root, new_node, max_root->right_sibling);

	if (new_node->right_sibling == nullptr) {
		new_node->right_sibling = first_root;
		first_root->left_sibling = new_node;
	}

	if (new_node->value > max_root->value)
		max_root = new_node;

}

void Heap::push_tree(Node * node)
{
	if (node != nullptr) {
		if (max_root == nullptr) {
			max_root = node;
			first_root = node;
		}
		else
			insert_between(max_root, node, max_root->right_sibling);

		if (node->right_sibling == nullptr) {
			node->right_sibling = first_root;
			first_root->left_sibling = node;
		}

		if (node->value > max_root->value)
			max_root = node;
	}
}

int Heap::pop_max()
{
	if (max_root != nullptr) {

		int max_value = max_root->value;
		Node* child = max_root->child;
		Node* first_child = child;
		remove(max_root);

		if (child != nullptr) {
			do {
				child->is_looser = false;
				child->parent = nullptr;
				Node* tmp = child->right_sibling;
				child->right_sibling = nullptr;
				child->left_sibling = nullptr;
				push_tree(child);
				child = tmp;
			} while (child != nullptr && child != first_child);

		}

		//cleanup
		Node* root_array[30];
		for (int i = 0; i < 30; i++) {
			root_array[i] = nullptr;
		}

		Node* t = max_root;
		if (t != nullptr) {
			do {
				Node* x = new Node(*t);
				//Node* x = t;
				x->left_sibling = nullptr;
				x->right_sibling = nullptr;
				while (root_array[x->degree] != nullptr) {
					Node* u = root_array[x->degree];
					root_array[x->degree] = nullptr;
					x = merge(x, u);
				}
				root_array[x->degree] = x;
				t = t->right_sibling;
				if (t != nullptr) {
					if (t->right_sibling == t) {
						cut_out(t->left_sibling);
						break;
					}
					else
						cut_out(t->left_sibling);
				}
			} while (t != nullptr);

			max_root = nullptr;
			first_root = nullptr;
			for (int i = 0; i < 30; i++) {
				if (root_array[i] != nullptr)
					push_tree(root_array[i]);
			}
		}
		return max_value;
	}
	else return HEAP_EMPTY;
}

void Heap::insert_between(Node* left, Node* new_node, Node* right)
{
	if (left != nullptr)
		left->right_sibling = new_node;

	if (right != nullptr)
		right->left_sibling = new_node;

	new_node->left_sibling = left;
	new_node->right_sibling = right;
}

void Heap::remove(Node * node)
{
	disconnect(node);
	delete node;
}

void Heap::cut_out(Node * node)
{
	if(node->right_sibling != nullptr)
		node->right_sibling->left_sibling = nullptr;
	if (node->left_sibling != nullptr)
		node->left_sibling->right_sibling = nullptr;
	delete node;
	node = nullptr;
}

void Heap::disconnect(Node * node)
{
	if (node->parent != nullptr && node->parent->child == node) {
		node->parent->child = node->right_sibling;
	}
	node->parent = nullptr;
	if (node == max_root)
		update_max(max_root);

	if (max_root == nullptr)
		first_root = nullptr;
	else if (node == first_root)
		first_root = node->right_sibling;

	Node* left = node->left_sibling;
	Node* right = node->right_sibling;
	if (left != nullptr)
		left->right_sibling = right;

	if (right != nullptr)
		right->left_sibling = left;
}

void Heap::update_max(Node* prev_max)
{
	Node* new_max = nullptr;
	Node* current_node = prev_max->right_sibling;
	while (current_node != prev_max) {
		if (new_max == nullptr || current_node->value > new_max->value)
			new_max = current_node;
		current_node = current_node->right_sibling;
	}
	max_root = new_max;
}



Node* Heap::merge(Node * t1, Node * t2)
{

	if (t1->value > t2->value) {
		if (t1->child == nullptr) {
			t1->child = t2;
			t2->parent = t1;
		}
		else {
			Node* child = t1->child;
			insert_between(child, t2, child->right_sibling);
			t2->parent = child->parent;
			if (t2->right_sibling == nullptr) {
				t2->right_sibling = child;
				child->left_sibling = t2;
			}
		}
		t1->degree++;
		return t1;
	}
	else {
		if (t2->child == nullptr) {
			t2->child = t1;
			t1->parent = t2;
		}
		else {
			Node* child = t2->child;
			insert_between(child, t1, child->right_sibling);
			t1->parent = child->parent;
			if (t1->right_sibling == nullptr) {
				t1->right_sibling = child;
				child->left_sibling = t1;
			}
		}
		t2->degree++;
		return t2;
	}
}

void Heap::merge_with(Heap * heap)
{
	while (heap->max_root != nullptr) {
		Node* tmp = heap->max_root;	
		heap->disconnect(heap->max_root);
		push_tree(tmp);
	}
}

int Heap::replace_key(int key, int new_key)
{
	Node* n = find_node_with_key(max_root, key);
	if (n != nullptr) {
		n->value = new_key;
		if (n->parent !=nullptr && n->parent->value < n->value) {
			do {
				Node* p = n->parent;
				disconnect(n);
				//print_structure(first_root);
				push_tree(n);
				n->is_looser = false;
				n = p;
			} while (n->is_looser == true);
			if (n->parent == nullptr) {
				n->is_looser = true;
			}
		}
		return 0;
	}
	else
		return -1;
}

void Heap::print_structure()
{
	print_structure(first_root);
}

Node * Heap::find_node_with_key(Node* root, int key)
{
	if (root != nullptr) {
		Node* tmp = root;
		do {
			if (tmp->value == key)
				return tmp;
			else {
				tmp = tmp->right_sibling;
				if (tmp != nullptr && tmp->child != nullptr) {
					Node* found = find_node_with_key(tmp->child, key);
					if (found != nullptr)
						return found;
				}
			}
		} while (tmp != nullptr && tmp != root);
	}
	return nullptr;
}

void Heap::fill_print_buffer(Node * root)
{
	if (root != nullptr) {
		Node* tmp = root;
		do {
			print_buffer[tmp->value - 1]++;
			tmp = tmp->right_sibling;
			if (tmp != nullptr && tmp->child != nullptr) {
				fill_print_buffer(tmp->child);
			}
		} while (tmp != nullptr && tmp != root);
	}
}

void Heap::print()
{
	if (max_root != nullptr) {
		print_buffer = new int[max_root->value]();
		fill_print_buffer(max_root);
		for (int i = max_root->value - 1; i >= 0; i--) {
			for (int j = 0; j < print_buffer[i]; j++) {
				printf("%d ", i + 1);
			}
		}
		printf("\n");
	}
	//delete print_buffer;
}

/***
DEBUG METHODS
***/

void Heap::print_roots()
{
	if (first_root != nullptr) {
		Node* tmp = first_root;
		do {
			printf("%d ", tmp->value);
			tmp = tmp->right_sibling;
		} while (tmp != first_root);
		printf("\n");
	}
}

void Heap::print_structure(Node * root, int indent)
{
	if (root != nullptr) {
		Node* tmp = root;
		do {
			for (int i = 0; i < indent; i++)
				printf(" - ");
			printf(" %d\n",tmp->value);

			print_structure(tmp->child, indent + 1);

			tmp = tmp->right_sibling;	
			if (tmp == nullptr || tmp == root ) {
				return;
			}
		} while (true);
	}
}




