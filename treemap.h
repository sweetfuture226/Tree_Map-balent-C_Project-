// Header for BST problem

#ifndef TREEMAP_H
#define TREEMAP_H 1

#include <stdio.h>

// Type of tree nodes
typedef struct node {
  char key[128];                // key for the node
  char val[128];                // value for the node
  struct node *left;            // left branch,  NULL if not present
  struct node *right;           // right branch, NULL if not present
} node_t;

// Type of tree itself
typedef struct {
  node_t *root;                 // root of tree, NULL if tree empty
  int size;                     // number of nodes in tree
} treemap_t;

// tree functions which will be tested in binary

// Initialize the given tree to have a null root and have size 0.
void treemap_init(treemap_t *tree);
// Inserts given key/value into a binary search tree. Uses an 
// ITERATIVE(loopy) aporoach to insertion which starts a pointer at
// the root of the tree and changes its location until the correct
// insertion point is located. If the key given already exits in the
// tree, no new node is created; the existing value is changed to the
// parameter 'val' and 0 is returned. If no node with the given key
// is found, a new node is created and with the given key/val, added
// to the tree, and 1 is returned. Makes use of strcpy() to ease
// copying characters between memory locations.
int treemap_add(treemap_t *tree, char key[], char val[]);
// Searches the tree for given 'key' and returns its associated
// value. Uses an ITERATIVE (loopy) search approach which starts a
// pointer at the root of the tree and changes it until the search key
// is found or determined not to be in the tree. If a matching key is
// found, returns a pointer to its value. If no matching key is found,
// returns NULL.
char *treemap_get(treemap_t *tree, char key[]);
// Eliminate all nodes in the tree setting its contens empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
void treemap_clear(treemap_t *tree);
// Prints the key/val pairs of the tree in reverse order at fiffering
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure. See the related node_print_revorder() for additional
// detals.
void treemap_print_revorder(treemap_t *tree);
// Print all the data in the tree in pre-order with indentation
// correspoinding to the depth of the tree. Makes use of 
// node_write_preorder() for this.
void treemap_print_preorder(treemap_t *tree);
// Saves the tree by opening the named file, writeing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
void treemap_save(treemap_t *tree, char *fname);
// Clears the given tree then loads new elements to it from the
// named. Repeated calls to treemap_add() are used to add strings read
// from the file. If the tree is stored in pre-order in the file, its
// exact structure will be restored. Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes are made to the tree.
int treemap_load(treemap_t *tree, char *fname);

// node functions, not tested but useful as helpers
char *node_get(node_t *cur, char key[]);
char *node_get2(node_t *cur, char key[], node_t * o_node);
void node_add(node_t * cur, char key[], char val[]);
// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
// node.
void node_remove_all(node_t *cur);
// Recursive helper function which prints all key/val pairs in the
// tree rooted at node 'cur' in reverse order. Traverses right
// subtree, prints cur node's key/val, then tranverses left tree.
// Parameter 'indent' indicates how far to indent (2 spaces per indent
// level).
void node_print_revorder(node_t *cur, int indent);
void node_print_preorder(node_t *cur, int indent);
// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.
void node_write_preorder(node_t *cur, FILE *out, int depth);

#endif
