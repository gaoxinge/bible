#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct tree {
    struct tree *left;
    struct tree *right;
    char *key;
    char *value;
};

void  tree_insert(struct tree **, char *k, char *v);
char *tree_find(struct tree *, char *k);
void  tree_visit(struct tree *, void (*f)(char *, char *));
void  tree_destroy(struct tree *);
void  printer(char *k, char *v);
void  print_tree(struct tree *);

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
    print_tree(tree);
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

void tree_visit(struct tree *t, void (*f)(char *, char *)) {
    if (t) {
        f(t->key, t->value);
        tree_visit(t->left, f);
        tree_visit(t->right, f);
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

void printer(char *k, char *v) {
    printf("%s = %s\n", k, v);
}

void print_tree(struct tree *tree) {
    tree_visit(tree, printer);
}