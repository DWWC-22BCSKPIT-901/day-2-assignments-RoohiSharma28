#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional> 
#include <string>     
using namespace std;

int maxHappyGroups(int batchSize, vector<int>& groups) {
    vector<int> count(batchSize, 0);

    for (int group : groups) {
        count[group % batchSize]++;
    }

    int result = count[0]; 
    count[0] = 0;

    unordered_map<string, int> memo;

    function<int(vector<int>&, int)> dfs = [&](vector<int>& count, int remainder) -> int {
        string stateKey = to_string(remainder) + "#";
        for (int i = 1; i < batchSize; ++i) {
            stateKey += to_string(count[i]) + ",";
        }

        if (memo.count(stateKey)) return memo[stateKey];

        int maxHappy = 0;
        for (int i = 1; i < batchSize; ++i) {
            if (count[i] > 0) {
                count[i]--;
                int nextRemainder = (remainder + i) % batchSize;
                int currentHappy = (remainder == 0 ? 1 : 0);
                maxHappy = max(maxHappy, currentHappy + dfs(count, nextRemainder));
                count[i]++;
            }
        }

        memo[stateKey] = maxHappy;
        return maxHappy;
    };

    result += dfs(count, 0);
    return result;
}

int main() {
    int batchSize, n;
    cout << "Enter batch size: ";
    cin >> batchSize;

    cout << "Enter number of groups: ";
    cin >> n;

    vector<int> groups(n);
    cout << "Enter group sizes: ";
    for (int i = 0; i < n; ++i) {
        cin >> groups[i];
    }

    int result = maxHappyGroups(batchSize, groups);
    cout << "Maximum number of happy groups: " << result << endl;

    return 0;
}
