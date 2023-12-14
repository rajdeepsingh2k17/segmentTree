#include <bits/stdc++.h>
using namespace std;

struct segmnentTree
{
 vector<pair<int, int>> tree;
 int N;
 void build(vector<int> &v, int n)
 {
  N = n;
  tree.resize(2 * n);
  for (int i = 0; i < n; i++)
  {
   tree[n + i] = {v[i], 1};
  }
  for (int i = n - 1; i >= 1; i--)
  {
   tree[i].first = min(tree[2 * i].first, tree[2 * i + 1].first);
   if (tree[2 * i].first < tree[2 * i + 1].first)
    tree[i].second = tree[2 * i].second;
   else if (tree[2 * i].first > tree[2 * i + 1].first)
    tree[i].second = tree[2 * i + 1].second;
   else
    tree[i].second = tree[2 * i + 1].second + tree[2 * i].second;
  }
 }

 void update(int node, int node_left, int node_right, int l, int r, int u)
 {
  if (l <= node_left && node_right <= r)
  {
   tree[node].first = u;
   return;
  }
  if (r < node_left || node_right < l)
  {
   return;
  }
  int mid = (node_left + node_right) / 2;
  update(2 * node, node_left, mid, l, r, u);
  update(2 * node + 1, mid + 1, node_right, l, r, u);
  tree[node].first = min(tree[2 * node].first, tree[2 * node + 1].first);
  if (tree[2 * node].first < tree[2 * node + 1].first)
   tree[node].second = tree[2 * node].second;
  else if (tree[2 * node].first > tree[2 * node + 1].first)
   tree[node].second = tree[2 * node + 1].second;
  else
   tree[node].second = tree[2 * node + 1].second + tree[2 * node].second;
  return;
 }

 pair<int, int> query(int node, int node_left, int node_right, int l, int r)
 {
  if (l <= node_left && node_right <= r)
  {
   return tree[node];
  }

  if (r < node_left || node_right < l)
  {
   return {INT_MAX, 0};
  }

  int mid = (node_left + node_right) / 2;
  auto left = query(2 * node, node_left, mid, l, r);
  auto right = query(2 * node + 1, mid + 1, node_right, l, r);
  int left_i = min(left.first, right.first);
  int left_j;
  if (left.first < right.first)
   left_j = left.second;
  else if (left.first > right.first)
   left_j = right.second;
  else
   left_j = left.second + right.second;

  return {left_i, left_j};
 }

} s;

int main()
{
 int n, m;
 cin >> n >> m;
 vector<int> v(n);
 for (int i = 0; i < n; i++)
  cin >> v[i];
 while (__builtin_popcount(n) != 1)
 {
  n++;
  v.push_back(0);
 }
 // for (int i = 0; i < n; i++)
 //  cout << v[i] << " ";
 cout << endl;
 s.build(v, n);
 // s.printTree();
 while (m--)
 {
  int a;
  cin >> a;
  if (a == 2)
  {
   int l, r;
   cin >> l >> r;
   auto it = s.query(1, 0, n - 1, l, r - 1);
   cout << it.first << " " << it.second << endl;
  }
  else if (a == 1)
  {
   int k, v;
   cin >> k >> v;
   s.update(1, 0, n - 1, k, k, v);
  }
 }
 return 0;
}