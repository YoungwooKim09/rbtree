#include <stdio.h>
#include <stdlib.h>

typedef char data;

typedef struct _Node {
    char key;
    struct _Node *left;
    struct _Node *right;
} Node;     // 형 재선언

// 노드 탐색
Node *searchBST(Node *root, char x) {

    Node *p = root;

    while(p != NULL) {
        if(p->key == x)
            return p;

        else if(p->key < x)
            p = p->right;

        else
            p = p->left;
    }

    return NULL;
}

// 노드 삽입
Node *insertBST(Node *root, char x) {

    Node *p = root;
    Node *parent = NULL;    // 루트가 비어 있는 경우를 대비하여 NULL로 초기화

    while(p != NULL) {

        parent = p;

        if(p->key == x) {
            printf("같은 키가 있습니다.\n");
            return p;
        }

        else if(p->key < x)
            p = p->right;

        else
            p = p->left;
    }

    // 새 노드 할당
    Node *newNode = (Node *)malloc(sizeof(Node));

    /*  malloc 함수 사용 시 예외 처리
    if (newNode == NULL)
    {
        ....
        return;
    }
    */

   newNode->key = x;
   newNode->left = newNode->right = NULL; // 단말노드

    // parent의 자식으로 새 노드 연결 - 루트가 비어 있는 경우 제외
    if(parent != NULL) {
        if(parent->key < newNode->key)
            parent->right = newNode;

        else
            parent->left = newNode;
    }

    return newNode;
}

// 노드 삭제
Node *deleteBST(Node *root, char x) {

    Node *p = root;
    Node *parent = NULL;    // 루트가 비어 있는 경우를 대비하여 NULL로 초기화

    while((p != NULL) && (p->key != x)) {   // 삭제를 위해 찾는 노드가 없거나 찾을 때까지

        parent = p;

        if(p->key < x)
            p = p->right;

        else
            p = p->left;
    }

    // 못 찾았을 때
    if (p == NULL) {
        printf("찾는 노드가 없습니다.\n");
        return root;    // 새로운 루트 노드의 주소를 반환하고 이를 가리키게 하기 위함 - 이 경우 찾는 노드가 없으므로 그대로 반환
    }

    // 찾았을 때
    if (p->left == NULL && p->right == NULL) {      // 차수 = 0

        // 루트 노드인데 차수가 0인 경우
        if(parent == NULL)
            root = NULL;

        // 루트 노드가 아닌데 차수가 0인 경우
        else {
            if(parent->left == p)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }

    // 위 if문에서 차수가 0인 것은 필터링
    else if (p->left == NULL || p->right == NULL) {      // 차수 = 1
        Node *child = (p->left != NULL) ? p->left : p->right;
        // 루트 노드가 삭제되는 경우
        if(parent == NULL)
            root = child;
        // 루트 이외의 노드가 삭제되는 경우
        else {
            if(parent->left == p)
                parent->left = child;
            else
                parent->right = child;
        }

    }

    else {                                               // 차수 = 2
        // 후계자 노드 찾기 - 오른쪽 서브트리 (오른쪽, 왼쪽 상관없음)
        Node *succ_parent = p;  // 예를 들어 루트 노드가 아닌 p 노드가 있으면,
        Node *succ = p->right;  // p의 오른쪽 서브트리에서 가장 작은 값을 찾겠다.

        while(succ->left != NULL) { // 오른쪽 서브트리에서 가장 작은 값은 왼쪽 자식이 반드시 없음
            succ_parent = succ;
            succ = succ->left;
        }

        // p 노드에는 후계자 노드의 데이터 복사, 후계자 노드를 제거
        p->key = succ->key;

        if(succ_parent->left == succ)
            succ_parent->left = succ->right;

        else
            succ_parent->right = succ->right;

        p = succ;
    }

    free(p);

    return root;        // 삭제 시 루트 값이 바뀔 수 있으므로
}

void Inorder(Node* root) {

    if(root == NULL)
        return;
    
    Inorder(root->left);
    printf("%c ", root->key);
    Inorder(root->right);
}

int main(void)
{
    Node *root = insertBST(NULL, 'D');
    insertBST(root, 'I');
    insertBST(root, 'F');
    insertBST(root, 'A');
    insertBST(root, 'G');
    insertBST(root, 'C');
    Inorder(root);      // BST를 중위 순회 하면 오름차순 정렬

    root = deleteBST(root, 'C');
    Inorder(root);

    return 0;
}