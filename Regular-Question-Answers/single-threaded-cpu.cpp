// Author: Rojen Arda Şeşen
// Question Link: https://leetcode.com/problems/single-threaded-cpu/
// Reviewer: Denis Davidoglu

// Time Complexity: T(n) <= O(nlogn)

// Overloading parentheses operator of structs to obtain custom comparators.

// Helps to sort tasks by their running times.
struct CompareRunningTimes {
    bool operator()(const vector<int>& a, const vector<int>& b) {
        if (a[1] == b[1]) {
            return a[2] > b[2];  // If running times are the same, compare indexes.
        }
        return a[1] > b[1];
    }
};

// Helps to sort tasks by their availability times.
struct CompareAvailabilityTimes {
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
};

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        for (int i = 0; i < tasks.size(); i++) {
            // Adding each task's initial index to itself as a new element.
            // Now, each task's 2nd index shows the task's initial index in the "tasks" array.
            tasks[i].push_back(i);
        }

        sort(tasks.begin(), tasks.end(), CompareAvailabilityTimes());

        long long cpuTime = 1;
        int index = 0;      // Index to keep track of tasks's order. Corresponds to task's order in array "tasks"
        vector<int> order;  // Order of the executed tasks

        // A pq that stores the available tasks in ascending order, depending on their running times.
        priority_queue<vector<int>, vector<vector<int>>, CompareRunningTimes> availableTasks;

        while (!availableTasks.empty() || index < tasks.size()) {
            if (availableTasks.empty() && cpuTime < tasks[index][0]) {
                // If there are no available tasks, CPU remains idle
                // -> CPU time keeps getting incremented until a task becomes available.
                cpuTime = tasks[index][0];
            }
            // Moving tasks that ready to run to availableTasks
            for (; index < tasks.size(); index++) {
                if (cpuTime < tasks[index][0]) {
                    // All tasks ready to run have been moved to availableTasks
                    break;
                }
                availableTasks.push(tasks[index]);
            }

            if (availableTasks.empty())
                break;

            // Running the task with the lowest running time among availableTasks
            cpuTime += availableTasks.top()[1];        // Increment cpuTime by the tasks time
            order.push_back(availableTasks.top()[2]);  // Add executed task's order to the "order" array.
            availableTasks.pop();                      // Remove the task from availableTasks
        }

        return order;
    }
};
