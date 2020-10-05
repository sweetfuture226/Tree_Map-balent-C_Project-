#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Initialize the given tree to have a null root and have size 0.
void treemap_init(treemap_t *tree){

	tree->root = NULL;
	tree->size = 0;
}

char *node_get(node_t *cur, char key[]){

	char * _p_ch_datas;
	struct node * _cur_node, * _left_node, * _right_node;

	if (cur == NULL){
	
		return NULL;
	}
	
	_cur_node = cur;

	if (strcmp( _cur_node->key, key) == 0){

		return _cur_node->val;
	} 

	_left_node = _cur_node->left;
	_right_node = _cur_node->right;

	if (_left_node != NULL){

		_p_ch_datas = node_get( _left_node, key);
		if (_p_ch_datas != NULL){

			return _p_ch_datas;
		}
	}

	if (_right_node != NULL){

		_p_ch_datas = node_get( _right_node, key);
		if (_p_ch_datas != NULL){

			return _p_ch_datas;
		}
	}

	return NULL;
}

// Searches the tree for given 'key' and returns its associated
// value. Uses an ITERATIVE (loopy) search approach which starts a
// pointer at the root of the tree and changes it until the search key
// is found or determined not to be in the tree. If a matching key is
// found, returns a pointer to its value. If no matching key is found,
// returns NULL.
char *treemap_get(treemap_t *tree, char key[]){

	return node_get( tree->root, key);
}
// Inserts given key/value into a binary search tree. Uses an 
// ITERATIVE(loopy) aporoach to insertion which starts a pointer at
// the root of the tree and changes its location until the correct
// insertion point is located. If the key given already exits in the
// tree, no new node is created; the existing value is changed to the
// parameter 'val' and 0 is returned. If no node with the given key
// is found, a new node is created and with the given key/val, added
// to the tree, and 1 is returned. Makes use of strcpy() to ease
// copying characters between memory locations.
int treemap_add(treemap_t *tree, char key[], char val[]){

	char * _p_ch_datas;

	if (tree->root == NULL || tree->size == 0){
	
		struct node * _new_node = malloc( sizeof  *_new_node);

		strcpy( _new_node->key, key);
		strcpy( _new_node->val, val);
		_new_node->left = NULL;
		_new_node->right = NULL;
		tree->root = _new_node;
		tree->size = 1;
		return 0;
	}
	
	_p_ch_datas = treemap_get( tree, key);

	if (_p_ch_datas != NULL){
	
		strcpy( _p_ch_datas, val);
		printf("modified existing key\n");
		return 0;
	} else {
	
		node_add( tree->root, key, val);
		tree->size++;
	}

	return 1;
}

int  get_direction( char i_ch_left[], char i_ch_right[]){

	bool _b_is;
	int _i, _len_left, _len_right, _mn_len, _i_dir;
	
	_len_left = strlen( i_ch_left);
	_len_right = strlen( i_ch_right);
	
	if (_len_left < _len_right){
	
		_mn_len = _len_left;
	} else {
	
		_mn_len = _len_right;
	}
	
	_b_is = false;
	for (_i = 0; _i < _mn_len; _i++){
	
		if (i_ch_left[ _i] != i_ch_right[ _i]){
		
			_b_is = true;		
			if (i_ch_left[ _i] > i_ch_right[ _i]){
			
				_i_dir = -1;
			} else {
			
				_i_dir = 1;
			}
			break;
		}
	}
	
	if (!_b_is){
	
		if (_len_left < _len_right){
		
			_i_dir = 1;
		} else {
		
			_i_dir = -1;
		}
	}
	
	return _i_dir;
}

void node_add(node_t * cur, char key[], char val[]){

	bool _b_add;
	bool _b_right;
	
	int _i_dir;
	
	struct node * _left_node, * _right_node;
	
	_b_add = false;
	_b_right = true;
	
	if (cur == NULL){
	
		return;
	}
	
	_left_node = cur->left;
	_right_node = cur->right;

	_i_dir = get_direction( cur->key, key);
	
	if (_left_node == NULL && _right_node == NULL){
	
		_b_add = true;
		if (_i_dir < 0){

			_b_right = false;
		} else {

			_b_right = true;
		}
	} else if (_left_node == NULL){

		if (_i_dir < 0){
		
			_b_add = true;
			_b_right = false;
		} else {
		
			node_add( _right_node, key, val);
		}
	} else if (_right_node == NULL){
	
		if (_i_dir > 0){
		
			_b_add = true;
			_b_right = true;		
		} else {
		
			node_add( _left_node, key, val);
		}
	} else {
	
		if (_i_dir < 0){
		
			node_add( cur->left, key, val);
		} else {

			node_add( cur->right, key, val);
		}
	}
	
	if (_b_add){
	
		struct node * _new_node = malloc( sizeof  *_new_node);

		strcpy( _new_node->key, key);
		strcpy( _new_node->val, val);
		_new_node->left = NULL;
		_new_node->right = NULL;
		if (_b_right){

			cur->right = _new_node;
		} else {

			cur->left = _new_node;
		}
	}	
}

// Prints the key/val pairs of the tree in reverse order at fiffering
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure. See the related node_print_revorder() for additional
// detals.
void treemap_print_revorder(treemap_t *tree){

	if (tree == NULL){
	
		return;
	}
	node_print_revorder( tree->root, 0);
}

// Recursive helper function which prints all key/val pairs in the
// tree rooted at node 'cur' in reverse order. Traverses right
// subtree, prints cur node's key/val, then tranverses left tree.
// Parameter 'indent' indicates how far to indent (2 spaces per indent
// level).
void node_print_revorder(node_t *cur, int indent){

	int _i, _count;
	
	if (cur == NULL){
	
		return;
	}

	if (cur->right != NULL){

		node_print_revorder( cur->right, indent + 1);
	}

	_count = indent;
	for (_i = 0; _i < _count; _i++){
	
		printf("  ");
	}
	
	printf("%s -> %s\n", cur->key, cur->val);
	 
	if (cur->left != NULL){

		node_print_revorder( cur->left, indent + 1);
	}	
}

// Print all the data in the tree in pre-order with indentation
// correspoinding to the depth of the tree. Makes use of 
// node_write_preorder() for this.
void treemap_print_preorder(treemap_t *tree){

	if (tree == NULL){
	
		return;
	}
	node_print_preorder( tree->root, 0);
}

void node_print_preorder(node_t *cur, int indent){

	int _i, _count;
	
	if (cur == NULL){
	
		return;
	}

	_count = indent;
	for (_i = 0; _i < _count; _i++){
	
		printf("  ");
	}
	
	printf("%s %s\n", cur->key, cur->val);

	if (cur->left != NULL){

		node_print_preorder( cur->left, indent + 1);
	}	
	 
	if (cur->right != NULL){

		node_print_preorder( cur->right, indent + 1);
	}
}

// Eliminate all nodes in the tree setting its contens empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
void treemap_clear(treemap_t *tree){

	if (tree == NULL){
	
		return;
	}

	node_remove_all( tree->root);
	treemap_init( tree);
}

// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
// node.
void node_remove_all(node_t *cur){

	if (cur == NULL){
	
		return;
	}
	
	if ( cur->left != NULL){

		node_remove_all( cur->left);
	}
	
	if ( cur->right != NULL){

		node_remove_all( cur->right);
	}
	
	strcpy( cur->key, "");
	strcpy( cur->val, "");
	free( cur);
	cur = NULL;
}

// Saves the tree by opening the named file, writeing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
void treemap_save(treemap_t *tree, char *fname){

	FILE * _file;
	
	_file = NULL;
	_file = fopen( fname, "wt");
	if (_file == NULL){
				
		return;
	}
	fseek( _file, 0L, SEEK_SET);
	node_write_preorder( tree->root, _file, tree->size);
	fclose( _file);
}

// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.
void node_write_preorder(node_t *cur, FILE *out, int depth){
	
	if (cur == NULL){
	
		return;
	}

	fprintf( out, "%s %s\n", cur->key, cur->val);
	 
	if (cur->left != NULL){

		node_write_preorder( cur->left, out, depth);
	}		

	if (cur->right != NULL){

		node_write_preorder( cur->right, out, depth);
	}	
}

// Clears the given tree then loads new elements to it from the
// named. Repeated calls to treemap_add() are used to add strings read
// from the file. If the tree is stored in pre-order in the file, its
// exact structure will be restored. Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes are made to the tree.
int treemap_load(treemap_t *tree, char *fname){

	int _len_key, _len_value;
	FILE * _file;
	char _ch_key[ 255];
	char _ch_value[ 255];
	
	_file = NULL;
	_file = fopen( fname, "rt");
	if (_file == NULL){
				
		return 0;
	}
	fseek( _file, 0L, SEEK_SET);
	
	while( fscanf( _file, "%s %s\n", _ch_key, _ch_value) != EOF){
	
		_len_key = strlen( _ch_key);
		_len_value = strlen( _ch_value);
		if (_len_key > 0 && _len_value > 0){

			treemap_add( tree, _ch_key, _ch_value);
		}
	}	
	fclose( _file);
	return 1;
}
