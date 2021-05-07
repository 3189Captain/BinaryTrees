#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTreeNode {
    char key;
    struct binaryTreeNode *leftChild;
    struct binaryTreeNode *rightChild;
} NODE;

typedef struct stackNode {
    struct binaryTreeNode *key;
    struct stackNode *next;
} STACKNODE;

void insert(NODE **root, char value);
void preorder(NODE **root);
void inorder(NODE **root);
char find(NODE **root, char value);
void push(STACKNODE **top, NODE *node);
NODE* pop(STACKNODE **top);
int isEmpty(STACKNODE **top);

int main() {
    NODE* root = NULL;
    int exit = 0;
    char controlChar;
    char searchValue;
    while(!exit) {
        printf("Press i to insert, p to preorder, o to inorder, f to find, or q to quit: ");
        controlChar = getc(stdin);
        getc(stdin);
        
        switch(controlChar) {
            case 'i':
                printf("Enter a character to insert: ");
                insert(&root, getc(stdin));
                getc(stdin);
                break;
            case 'p':
                preorder(&root);
                break;
            case 'o':
                inorder(&root);
                break;
            case 'f':
                printf("Enter a value: ");
                searchValue = getc(stdin);
                getc(stdin);
                if(find(&root, searchValue) == '\0') {
                    printf("value is not in the tree\n");
                } else {
                    printf("value %c found\n", find(&root, searchValue));
                }
                break;
            case 'q':
                exit = 1;
        }
    }
    return 0;
}

void insert(NODE **root, char value){
    if(*root == NULL) {
        *root = malloc(sizeof(NODE));
        (*root)->key = value;
    } else {
        NODE* parent = NULL;
        NODE* insertPtr = *root;
        while(insertPtr != NULL) {
            parent = insertPtr;
            if(value == insertPtr->key) {
                printf("VALUE IS ALREADY IN TREE\n");
            } else if(value < insertPtr->key) {
                insertPtr = insertPtr->leftChild;
            } else {
                insertPtr = insertPtr->rightChild;
            }
        }
        if(value < parent->key) {
            parent->leftChild = malloc(sizeof(NODE));
            parent->leftChild->key = value;
        } else if(value > parent->key) {
            parent->rightChild = malloc(sizeof(NODE));
            parent->rightChild->key = value;
        }
    }
}

void preorder(NODE **root) {
    NODE* current = *root;
    STACKNODE* top = NULL;
    int done = 0;
    if(current == NULL) {
        printf("The tree is empty");
    } else {
        printf("PREORDER: ");
    
        while(!done) {
            if(current != NULL) {
                push(&top, current);
                printf("%c ", current->key);
                current = current->leftChild;
            } else {
                if(!isEmpty(&top)) {
                    current = pop(&top);
                    current = current->rightChild;
                } else {
                    done = 1;
                }
            }
        }
        printf("\n");
    }
}
void inorder(NODE** root) {
    NODE* current = *root;
    STACKNODE* top = NULL;
    int done = 0;
if(current == NULL) {
        printf("The tree is empty");
    } else {
        printf("INORDER: ");
    
        while(!done) {
            if(current != NULL) {
                push(&top, current);
                current = current->leftChild;
            } else {
                if(!isEmpty(&top)) {
                    current = pop(&top);
                    printf("%c ", current->key);
                    current = current->rightChild;
                } else {
                    done = 1;
                }
            }
        }
        printf("\n");
    }
}

char find(NODE **root, char value) {
    NODE* current = *root;
    STACKNODE* top = NULL;
    char currentValue;
    int done = 0;
    
    
    while(!done) {
        if(current != NULL) {
            push(&top, current);
            currentValue = current->key;
            if(currentValue == value) {
                return currentValue;
            }
            current = current->leftChild;
        } else {
            if(!isEmpty(&top)) {
                current = pop(&top);
                current = current->rightChild;
            } else {
                done = 1;
                return '\0';
            }
        }
    }
}

void push(STACKNODE **top, NODE *node) {
    STACKNODE* newNode = malloc(sizeof(STACKNODE));
    newNode->key = node;
    newNode->next = *top;
    *top = newNode;
}
NODE* pop(STACKNODE **top) {
    STACKNODE* internalTop = *top;
    NODE* result = internalTop->key;
    *top = internalTop->next;
    free(internalTop);
    return result;
}
int isEmpty(STACKNODE **top) {
    if(*top == NULL) {
        return 1;
    } else {
        return 0;
    }
}