#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
using namespace std;

bool canAssign(vector<int>& jobs, vector<int>& workers, int k, int limit, int index) {
    if (index == jobs.size()) return true;

    int job = jobs[index];
    for (int i = 0; i < k; ++i) {
        if (workers[i] + job <= limit) {
            workers[i] += job;
            if (canAssign(jobs, workers, k, limit, index + 1)) return true;
            workers[i] -= job;
        }

        if (workers[i] == 0) break;
    }
    return false;
}

int minimumWorkingTime(vector<int>& jobs, int k) {
    int n = jobs.size();
    int left = *max_element(jobs.begin(), jobs.end()); 
    int right = accumulate(jobs.begin(), jobs.end(), 0); 


    while (left < right) {
        int mid = left + (right - left) / 2;
        vector<int> workers(k, 0); 

        if (canAssign(jobs, workers, k, mid, 0)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int n, k;
    cout << "Enter the number of jobs: ";
    cin >> n;

    vector<int> jobs(n);
    cout << "Enter the job durations: ";
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i];
    }

    cout << "Enter the number of workers: ";
    cin >> k;

    int result = minimumWorkingTime(jobs, k);
    cout << "The minimum possible maximum working time is: " << result << endl;

    return 0;
}
