#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, i;
  cin >> n;
  vector<long> d(n + 1), p(n), w(n);
  vector<long> res(n + 1, -1);
  for (i = 1; i <= n; i++) cin >> d[i];
  for (i = 1; i < n; i++) cin >> p[i] >> w[i];

  unordered_map<int, unordered_map<int, long> > graph;
  for (i = 1; i < n; i++) graph[i + 1][p[i]] = graph[p[i]][i + 1] = w[i];
  
  priority_queue<pair<long, int> > pq;
  for (i = 2; i <= n; i++) pq.push(make_pair(d[i], i));
  pq.push(make_pair(LONG_MAX, 1));

  res[1] = 0;
   
  while (!pq.empty())
  {
    pair<long, int> src = pq.top(); pq.pop();
    int srcCity = src.second;
    vector<bool> visited(n + 1, false);
    stack<pair<int, long> > stk;
    stk.push(make_pair(srcCity, 0));
    while (!stk.empty())
    {
      pair<int, long> curr = stk.top(); stk.pop();
      int currCity = curr.first;
      if (visited[currCity]) continue;
      visited[currCity] = true;
      long distSrc = curr.second;
      long cost = res[srcCity] + d[srcCity] * distSrc;
      if (res[currCity] == -1) res[currCity] = cost;
      else res[currCity] = min(res[currCity], cost);
      for (const auto& adj : graph[currCity]) stk.push(make_pair(adj.first, distSrc + adj.second));
    }
  }

  cout << res[n] << endl;

  return 0;
}
