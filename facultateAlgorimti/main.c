#include <stdio.h>
#include <stdlib.h>

typedef enum {RED, BLACK } COLOR;

typedef struct RB_node {
    int key;
    COLOR color;
    struct RB_node *left, *right, *parent;
} t_RB_node;

typedef struct {
    t_RB_node *root;
} t_RB_arbore;

t_RB_node* MAKE_ROOT(t_RB_arbore *A, int key) {
    t_RB_node *root = (t_RB_node *)malloc(sizeof(t_RB_node));
    root->key = key;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    root->color = BLACK;
    A->root = root;
    return root;
}

t_RB_node* CREATE_NODE(int key) {
    t_RB_node *node = (t_RB_node *)malloc(sizeof(t_RB_node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED;
    return node;
}

void INORDER_WALK(t_RB_node *root) {
    if (root != NULL) {
        INORDER_WALK(root->left);
        printf("%d ", root->key);
        if (root->color == BLACK) {
            printf("[b] ");
        } else {
            printf("[r] ");
        }
        INORDER_WALK(root->right);
    }
}

t_RB_node* TREE_SEARCH(t_RB_node *n, int key) {
    if (n == NULL || key == n->key) {
        return n;
    }
    if (key < n->key) {
        return TREE_SEARCH(n->left, key);
    }
    return TREE_SEARCH(n->right, key);
}

void LEFT_ROTATE(t_RB_arbore *A, t_RB_node *x) {
    t_RB_node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        A->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RIGHT_ROTATE(t_RB_arbore *A, t_RB_node *y) {
    t_RB_node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        A->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void RB_INSERT_FIXUP(t_RB_arbore *A, t_RB_node *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            t_RB_node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LEFT_ROTATE(A, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RIGHT_ROTATE(A, z->parent->parent);
            }
        } else {
            t_RB_node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RIGHT_ROTATE(A, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LEFT_ROTATE(A, z->parent->parent);
            }
        }
    }
    A->root->color = BLACK;
}

void RB_INSERT(t_RB_arbore *A, t_RB_node *z) {
    t_RB_node *y = NULL;
    t_RB_node *x = A->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        A->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NULL;
    z->right = NULL;
    z->color = RED;
    RB_INSERT_FIXUP(A, z);
}

int main(int argc, const char * argv[]) {
    t_RB_arbore A;
    A.root = NULL;
    int x;
    printf("Introduceti valoarea radacinii: ");
    scanf("%d", &x);
    t_RB_node *root = MAKE_ROOT(&A, x);
    printf("Introduceti x pana la citirea 0\n");
    while (1) {
        scanf("%d", &x);
        if (x == 0) {
            break;
        }
        t_RB_node *node = CREATE_NODE(x);
        RB_INSERT(&A, node);
    }
    printf("Parcurgerea in-order a arborelui: \n");
    INORDER_WALK(A.root);
    printf("\nCauta nodul cu cheia x = ");
    scanf("%d", &x);
    t_RB_node *n = TREE_SEARCH(A.root, x);
    if (n != NULL) {
        printf("Nodul cu cheia %d a fost gasit.\n", n->key);
    } else {
        printf("Nodul nu a fost gasit\n");
    }
    return 0;
}
