#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  
  nil_node->color = RBTREE_BLACK;
  p->nil = nil_node;
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *x = t->root;
  node_t *y = t->nil;

  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));  // 메모리 할당 실패 시 예외 처리 필요
  if (newNode == NULL) exit(1); 
  newNode->key = key;

  while(x != t->nil) {

    y = x;

    if(key > x->key)
      x = x->right;

    else
      x = x->left;
  }

  if(y == t->nil)
    t->root = newNode;

  else if(y->key > key)
    y->left = newNode;

  else
    y->right = newNode;   // 같은 값일 경우 오른쪽 자식 노드로 추가

  newNode->parent = y;
  newNode->color = RBTREE_RED;

  newNode->left = newNode->right = t->nil;

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
