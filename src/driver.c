#include "rbtree.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    delete_rbtree(t);
}