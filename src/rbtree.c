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

void Postorder(rbtree *t, node_t* root) {

    if(root == t->nil)
        return;
    
    Postorder(t, root->left);
    root->left = NULL;
    Postorder(t, root->right);
    root->left = NULL;
    free(root);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t == NULL) return; 
  Postorder(t, t->root);
  free(t->nil);
  t->root=NULL;
  t->nil = NULL;
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;           // y 설정
  x->right = y->left;             // y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮긴다. (자식으로 연결)
  if (y->left != t->nil)          // 옮긴 서브 트리가 nil이 아니라면,
    y->left->parent = x;          // 옮긴 서브 트리 연결 (부모로 연결)
  y->parent = x->parent;          // x의 부모를 y로 연결한다.
  if (x->parent  == t->nil)       // x의 부모가 nil이라면,
    t->root = y;                  // y는 루트노드
  else if (x == x->parent->left)  // x가 부모노드의 왼쪽자식이었다면,
    x->parent->left = y;          // y는 부모노드의 왼쪽자식
  else
    x->parent->right = y;
  y->left = x;                    // x를 y의 왼쪽으로 놓는다.
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;            // y 설정           
  x->left = y->right;             // x의 오른쪽 서브 트리를 y의 왼쪽 서브 트리로 옮긴다. (자식으로 연결)             
  if (y->right != t->nil)         // 옮긴 서브 트리가 nil이 아니라면,
    y->right->parent = x;         // 옮긴 서브 트리 연결 (부모로 연결)
  y->parent = x->parent;          // y의 부모를 x로 연결한다.
  if (x->parent  == t->nil)       // y의 부모가 nil이라면,
    t->root = y;                  // x는 루트노드
  else if (x == x->parent->right) // y가 부모노드의 왼쪽자식이었다면,
    x->parent->right = y;         // x는 부모노드의 왼쪽자식
  else
    x->parent->left = y;
  y->right = x;                     
  x->parent = y;
}

void rb_insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) {

    if (z->parent == z->parent->parent->left) {
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else  {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }

    else {
         node_t *y = z->parent->parent->left;
        if (y->color == RBTREE_RED){
          z->parent->color = RBTREE_BLACK;
          y->color = RBTREE_BLACK;
          z->parent->parent->color = RBTREE_RED;
          z = z->parent->parent;
        }
        else  {
          if (z == z->parent->left) {
            z = z->parent;
            right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *x = t->root;
  node_t *y = t->nil;
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));  // 메모리 할당 실패 시 예외 처리 필요

  if (newNode == NULL)
    return NULL;
  
  newNode->key = key;

  while(x != t->nil) {

    y = x;

    if(key < x->key)
      x = x->left;

    else
      x = x->right;
  }

  newNode->parent = y;

  if(y == t->nil)
    t->root = newNode;

  else if(y->key > key)
    y->left = newNode;

  else
    y->right = newNode;   // 같은 값일 경우 오른쪽 자식 노드로 추가

  newNode->left = newNode->right = t->nil;
  newNode->color = RBTREE_RED;

  rb_insert_fixup(t, newNode);

  return newNode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *x = t->root;
  while(x != t->nil) {
    if (x->key == key)
      return x;
    else if (x->key > key)
      x = x->left;
    else
      x = x->right;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root;

  while(x->left != t->nil) {
    x = x->left;
  }

  return x;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root;

  while(x->right != t->nil) {
    x = x->right;
  }

  return x;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil)
    t->root = v;

  else if (u == u->parent->left)
    u->parent->left = v;

  else
    u->parent->right = v;

  v->parent = u->parent;
}

node_t *tree_minimum(rbtree *t, node_t *x) {
  while (x->left != t->nil)
      x = x->left;

  return x;
}

void rb_erase_fixup(rbtree *t, node_t *x) {
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      w = x->parent->right;
      // case 1
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      // case 2
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      // case 3
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;   // case 4 형태로 만들어줌
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else {
      w = x->parent->left;
      // case 1
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      // case 2
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      // case 3
      else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;   // case 4 형태로 만들어줌
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;  // p가 하나 이하의 자식을 가질 경우, y는 p를 가리키도록 설정되며 삭제된다.
  color_t y_original_color = y->color;  // 변경 전 y의 색깔 저장
  node_t *x;

  if (z->left == t->nil) {
     x = z->right;
    rb_transplant(t, z, z->right);
  }

  else if (z->right == t->nil) {
    x = z->left;
    rb_transplant(t, z, z->left);
  }

  else {
    y = tree_minimum(t, z->right);
    y_original_color = y->color;
    x = y->right;
    
    if (y->parent == z)
      x->parent = y;

    else {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (y_original_color == RBTREE_BLACK)
    rb_erase_fixup(t, x);

  free(z);

  return 0;
}

int Inorder(const rbtree *t, node_t *p, key_t *arr, const size_t n, int i) {
  if (p == t->nil || i >= n)
    return i;
  i = Inorder(t, p->left, arr, n, i);
  arr[i++] = p->key;
  i = Inorder(t, p->right, arr, n, i);

  return i;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  int i = 0;
  Inorder(t, t->root, arr, n, i);

  return 0;
}