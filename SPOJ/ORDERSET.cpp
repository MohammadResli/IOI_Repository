#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct node {
  int p, key, cnt;
  node *left, *right;

  node(int _p, int _key, node* _left = NULL, node* _right = NULL) {
    p = _p;
    key = _key;
    left = _left;
    right = _right;

    upd();
  }

  void upd() {
    cnt = 1;
    if(left != NULL) cnt += left->cnt;
    if(right != NULL) cnt += right->cnt;
  }
};

inline int cnt(node* root) {
  return (root == NULL ? 0 : root->cnt);
}

void rotate_right(node*& root) {
  root->left->right = new node(root->p, root->key, root->left->right, root->right);
  root = root->left;
}

void rotate_left(node*& root) {
  root->right->left = new node(root->p, root->key, root->left, root->right->left);
  root = root->right;
}

void insert(node*& root, int X, int p) {
  if(root == NULL) {
    root = new node(p, X);
    return;
  }

  if(X < root->key) {
    insert(root->left, X, p);
    if(root->left->p < root->p) rotate_right(root);
  }
  else if(X > root->key){
    insert(root->right, X, p);
    if(root->right->p < root->p) rotate_left(root);
  }

  root->upd();
}

void merge(node*& root, node* L, node* R) {
  if(L == NULL) {
    root = R;
    return;
  }
  if(R == NULL) {
    root = L;
    return;
  }

  if(L->p <= R->p) {
    merge(L->right, L->right, R);
    root = L;
  }
  else {
    merge(R->left, L, R->left);
    root = R;
  }

  root->upd();
}

void delete_node(node*& root, int X) {
  if(root == NULL) return;

  if(X < root->key) {
    delete_node(root->left, X);
  }
  else if(X > root->key) {
    delete_node(root->right, X);
  }
  else {
    merge(root, root->left, root->right);
  }

  if(root != NULL) root->upd();
}

node* kth_min(node* root, int K) {
  if(root == NULL) return NULL;

  if(K <= cnt(root->left)) {
    return kth_min(root->left, K);
  }
  else if(K == cnt(root->left) + 1){
    return root;
  }
  else {
    return kth_min(root->right, K - cnt(root->left) - 1);
  }
}

int count_less(node* root, int X) {
  if(root == NULL) return 0;

  if(X > root->key) {
    return cnt(root->left) + 1 + count_less(root->right, X);
  }
  else {
    return count_less(root->left, X);
  }
}

int main() {
  srand(0);

  node* root = NULL;

  int Q; scanf("%d", &Q);
  while(Q--) {
    char t; int x; scanf(" %c %d", &t, &x);

    if(t == 'I') {
      int p = rand();
      if(root == NULL) {
        root = new node(p, x);
      }
      else insert(root, x, p);
    }
    else if(t == 'D') {
      delete_node(root, x);
    }
    else if(t == 'K') {
      node* req = kth_min(root, x);

      if(req == NULL) printf("invalid\n");
      else printf("%d\n", req->key);
    }
    else {
      printf("%d\n", count_less(root, x));
    }
  }
}

