// Chandragupta and the fun with BST

#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

#define MOD 1000000007

int ans[300001];
int A[300001];
bool left[300001];
bool right[300001];
map<int, int> compres;
set<int> vals;

int main() {
  int N; scanf("%d", &N);

  for(int i = 0; i < N; i++) scanf("%d", &A[i]);
  int timer = 0;
  for(int i = 0; i < N; i++) {
    compres[A[i]] = 0;
  }
  for(auto it: compres) compres[it.first] = ++timer;
  for(int i = 0; i < N; i++) A[i] = compres[A[i]];

  ans[A[0]] = 1;
  vals.insert(A[0]);

  for(int i = 1; i < N; i++) {
    auto it = vals.upper_bound(A[i]);
    if(it == vals.end()) {
      int add = *vals.rbegin();
      ans[A[i]] = (2 * ans[add] + 1) % MOD;
      right[add] = true;
    }
    else if(it == vals.begin()) {
      int add = *vals.begin();
      ans[A[i]] = (2 * ans[add]) % MOD;
      left[add] = true;
    }
    else {
      int add = *it;
      if(left[add]) {
        advance(it, -1); add = *it;
        ans[A[i]] = (2 * ans[add] + 1) % MOD;
        right[add] = true;
      }
      else {
        ans[A[i]] = (2 * ans[add]) % MOD;
        left[add] = true;
      }
    }
    vals.insert(A[i]);
  }

  for(int i = 0; i < N; i++) printf("%d ", ans[A[i]]); printf("\n");
}

