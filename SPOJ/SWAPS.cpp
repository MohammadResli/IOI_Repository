#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 250000;
const int MAX = 50000;
const int BLOCK_SIZE = 500;
int A[MAX_N + 1];
int bit[MAX_N/BLOCK_SIZE + 1][MAX + 1];
int temp_bit[MAX + 1];
int N;

void update(int *bit, int i, int v) {
  if(i == 0) return;
  while(i <= MAX) {
    bit[i] += v;
    i += i & -i;
  }
}

int query(int *bit, int i) {
  int ans = 0;
  while(i > 0) {
    ans += bit[i];
    i -= i & -i;
  }
  return ans;
}

int find_inversions(int X) {
  int ans = 0;

  for(int i = 0; i < X/BLOCK_SIZE; i++) {
    ans += BLOCK_SIZE - query(bit[i], A[X]);
  }
  for(int i = X/BLOCK_SIZE * BLOCK_SIZE; i < X; i++) {
    if(A[i] > A[X]) ans++;
  }
  for(int i = X + 1; i < (X/BLOCK_SIZE + 1) * BLOCK_SIZE; i++) {
    if(A[i] < A[X]) ans++;
  }
  for(int i = X/BLOCK_SIZE + 1; i < N/BLOCK_SIZE + 1; i++) {
    ans += query(bit[i], A[X] - 1);
  }

  return ans;
}

int main() {
  scanf("%d", &N);

  for(int i = 0; i < N; i++) scanf("%d", &A[i]);

  long long ans = 0;
  for(int i = 0; i < N; i++) {
    ans += i - query(temp_bit, A[i]);
    update(temp_bit, A[i], 1);
    update(bit[i/BLOCK_SIZE], A[i], 1);
  }

  int M; scanf("%d", &M);

  while(M--) {
    int X, Y; scanf("%d %d", &X, &Y); X--;

    ans -= find_inversions(X);
    update(bit[X/BLOCK_SIZE], A[X], -1);
    A[X] = Y;
    update(bit[X/BLOCK_SIZE], A[X], 1);
    ans += find_inversions(X);

    printf("%lld\n", ans);
  }
}
