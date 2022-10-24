#include "BinaryTreeList.h"

// 트리
Node tree = NULL;

// malloc 반환값 체크
// 포인터 역참조 전에 NULL 체크

Node makeRoot(DATA data) {
    tree = (struct _Node *)malloc(sizeof(struct _Node));  // 루트 노드의 메모리 할당
    /*  malloc 함수 사용 시 예외 처리
    if (tree == NULL)
    {
        ....
        return;
    }
    */
    tree->data = data;
    tree->lchild = tree->rchild = NULL;
    return tree;
}

Node makeLeftChild(Node cur, DATA data) {
    struct _Node *newnode = (struct _Node *)malloc(sizeof(struct _Node));
    /*  malloc 함수 사용 시 예외 처리
    if (tree == NULL)
    {
        ....
        return;
    }
    */
    newnode->data = data;
    newnode->lchild = newnode->rchild = NULL;
    cur->lchild = newnode;
    return newnode;
}

Node makeRightChild(Node cur, DATA data) {
    struct _Node *newnode = (struct _Node *)malloc(sizeof(struct _Node));
    /*  malloc 함수 사용 시 예외 처리
    if (tree == NULL)
    {
        ....
        return;
    }
    */
    newnode->data = data;
    newnode->lchild = newnode->rchild = NULL;
    cur->rchild = newnode;
    return newnode;
}
// 포인터를 역참조하여 들어가기 직전에 해당 포인터가 NULL 포인터인지 확인하는 예외 처리 필요
DATA getCurData(Node cur) {
    //cur 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    return cur->data;
}

Node getLeftChild(Node cur) {
    //cur 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    return cur->lchild;
}

DATA getLeftChildData(Node cur) {
    //cur 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    //cur 노드의 lchild 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    return cur->lchild->data;
}

Node getRightChild(Node cur) {
    //cur 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    return cur->rchild;
}

DATA getRightChildData(Node cur) {
    //cur 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    //cur 노드의 rchild 노드가 NULL 노드인 경우에 대한 예외 처리 필요
    return cur->rchild->data;
}

int isTreeEmpty(Node root) {
    if(root == NULL)
        return 1;
    else
        return 0;
}