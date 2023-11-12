#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, x, y, i, j;
    cin >> n >> x >> y;
    vector<int> a(n), b(n);
    for (i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<pair<int, int> > combined; 
    for (i = 0; i < n; i++) combined.push_back(make_pair(a[i] - b[i], i));
    sort(combined.begin(), combined.end());
    // The best x runners
    priority_queue<pair<int, int> > runnerMaxHeap;
    // The best y swimmers
    priority_queue<pair<int, int> > swimmerMaxHeap;
    vector<int> runnerTotalTimes = {0};
    for (i = 0; i < x; i++)
    {
        pair<int, int> athlete = combined[i];
        int athleteId = athlete.second;
        int runTime = a[athleteId];
        runnerMaxHeap.push(make_pair(runTime, athleteId));
        runnerTotalTimes[0] += runTime;
    }
    vector<int> swimmerTotalTimes = {0};
    for (i = n - 1; i >= n - y; i--)
    {
        pair<int, int> athlete = combined[i];
        int athleteId = athlete.second;
        int swimTime = b[athleteId];
        swimmerMaxHeap.push(make_pair(swimTime, athleteId));
        swimmerTotalTimes[0] += swimTime;
    }
    // Boundary is from 1st to n - yth athlete
    for (i = x; i < n - y; i++)
    {
        pair<int, int> currRunner = combined[i];
        int currRunnerId = currRunner.second;
        int currRunnerTime = a[currRunnerId];
        pair<int, int> worstSelectedRunner = runnerMaxHeap.top();
        int worstSelectedRunnerTime = worstSelectedRunner.first;
        if (currRunnerTime >= worstSelectedRunnerTime) 
        {
            runnerTotalTimes.push_back(runnerTotalTimes.back());
            continue;
        }
        runnerMaxHeap.pop();
        runnerMaxHeap.push(make_pair(currRunnerTime, currRunnerId));
        runnerTotalTimes.push_back(runnerTotalTimes.back() - worstSelectedRunnerTime + currRunnerTime);
    }
    // Boundary is from nth athlete to x + 1th athlete
    for (i = n - y - 1; i >= x; i--)
    {
        pair<int, int> currSwimmer = combined[i];
        int currSwimmerId = currSwimmer.second;
        int currSwimmerTime = b[currSwimmerId];
        pair<int, int> worstSelectedSwimmer = swimmerMaxHeap.top();
        int worstSelectedSwimmerTime = worstSelectedSwimmer.first;
        if (currSwimmerTime >= worstSelectedSwimmerTime)
        {
            swimmerTotalTimes.push_back(swimmerTotalTimes.back());
            continue;
        }
        swimmerMaxHeap.pop();
        swimmerMaxHeap.push(make_pair(currSwimmerTime, currSwimmerId));
        swimmerTotalTimes.push_back(swimmerTotalTimes.back() - worstSelectedSwimmerTime + currSwimmerTime);
    }
    
    int res = INT_MAX;
    for (i = 0; i < runnerTotalTimes.size(); i++)
    {
        int lBoundary = x + i - 1;
        // 1st to x + ith runner, minimum top x runner times
        int runnerTime = runnerTotalTimes[i];
        for (j = 0; j < swimmerTotalTimes.size(); j++)
        {
            // nth to n - y - jth swimmer, minimum top y swimmer times
            int rBoundary = n - y - j;
            if (lBoundary >= rBoundary) break;
            int swimmerTime = swimmerTotalTimes[j];
            res = min(res, runnerTime + swimmerTime);
        }
    }

    cout << res << endl;
    return 0;
}
