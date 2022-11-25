#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct tree {
    struct tree *left;
    struct tree *right;
    char *key;
    char *value;
};

struct tree_it {
    struct tree *stack[32];
    unsigned long long state;
    int nstack;
};

void  tree_insert(struct tree **, char *k, char *v);
char *tree_find(struct tree *, char *k);
void  tree_destroy(struct tree *);

struct tree_it *tree_iterator(struct tree *);
int             tree_next(struct tree_it *, char **k, char **v);

char *teams[] = {
    "Pittsburgh",   "Penguins",
    "Washington",   "Capitals",
    "Philadelphia", "Flyers",
    "New York",     "Rangers",
    "Tampa Bay",    "Lightning",
    "Boston",       "Bruins",
    "Columbus",     "Blue Jackets",
};

const int nteams = sizeof(teams) / sizeof(*teams) / 2;

int main() {
    struct tree *tree = NULL;
    for (int i = 0; i < nteams; i++)
        tree_insert(&tree, teams[i * 2], teams[i * 2 + 1]);
    
    char *k, *v;
    struct tree_it *it = tree_iterator(tree);
    while (tree_next(it, &k, &v))
        printf("%s = %s\n", k, v);
    
    tree_destroy(tree);
    return 0;
}

void tree_insert(struct tree **t, char *k, char *v) {
    if (*t) {
        int cmp = strcmp((*t)->key, k);
        if (cmp < 0)      tree_insert(&(*t)->left, k, v);
        else if (cmp > 0) tree_insert(&(*t)->right, k, v);
        else              (*t)->value = v;
    } else {
        *t = malloc(sizeof(struct tree));
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->key = k;
        (*t)->value = v;
    }
}

char *tree_find(struct tree *t, char *k) {
    if (t) {
        int cmp = strcmp(t->key, k);
        if (cmp < 0) return tree_find(t->left, k);
        if (cmp > 0) return tree_find(t->right, k);
        return t->value;
    }
    return NULL;
}

void tree_destroy(struct tree *t) {
    if (t) {
        tree_destroy(t->left);
        tree_destroy(t->right);
        free(t);
    }
}

struct tree_it *tree_iterator(struct tree *t) {
    struct tree_it *it = malloc(sizeof(*it));
    it->stack[0] = t;
    it->state = 0;
    it->nstack = 1;
    return it;
}

int tree_next(struct tree_it *it, char **k, char **v) {
    while (it->nstack) {
        int shift = (it->nstack - 1) * 2;
        int state = 3u & (it->state >> shift);
        struct tree *t = it->stack[it->nstack - 1];
        it->state += 1ull << shift;
        switch (state) {
            case 0:
                *k = t->key;
                *v = t->value;
                if (t->left) {
                    it->stack[it->nstack++] = t->left;
                    it->state &= ~(3ull << (shift + 2));
                }
                return 1;
            case 1:
                if (t->right) {
                    it->stack[it->nstack++] = t->right;
                    it->state &= ~(3ull << (shift + 2));
                }
                break;
            case 2:
                it->nstack--;
                break;
        }
    }
    free(it);
    return 0;
}