#include "header.h"

class NumberContainers {
    unordered_map<int, int> index_map;
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> smallest_map;

public:  
    void change(int index, int number) {
        index_map[index] = number;
        smallest_map[number].emplace(index);
    }
    
    int find(int number) {
        auto& queue = smallest_map[number];
        while (!queue.empty())
        {
            if (number == index_map[queue.top()])
                return queue.top();
            queue.pop();
        }

        return -1;
    }
};

int main() {
    NumberContainers nc;
    vector<string> commands = {"NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"};
    vector<vector<int>> inputs = {{}, {10}, {2, 10}, {1, 10}, {3, 10}, {5, 10}, {10}, {1, 20}, {10}};
    
    vector<string> results;
    results.push_back("null");
    
    for (size_t i = 1; i < commands.size(); ++i) {
        if (commands[i] == "find") {
            int res = nc.find(inputs[i][0]);
            results.push_back(to_string(res));
        } else if (commands[i] == "change") {
            nc.change(inputs[i][0], inputs[i][1]);
            results.push_back("null");
        }
    }
    
    cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << results[i];
        if (i != results.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}

    /**
     * Your NumberContainers object will be instantiated and called as such:
     * NumberContainers* obj = new NumberContainers();
     * obj->change(index,number);
     * int param_2 = obj->find(number);
     */

// Design a number container system that can do the following:

// Insert or Replace a number at the given index in the system.
// Return the smallest index for the given number in the system.
// Implement the NumberContainers class:

// NumberContainers() Initializes the number container system.
// void change(int index, int number) Fills the container at index with the number. If there is already a number at that index, replace it.
// int find(int number) Returns the smallest index for the given number, or -1 if there is no index that is filled by number in the system.
 

// Example 1:

// Input
// ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
// [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
// Output
// [null, -1, null, null, null, null, 1, null, 2]

// Explanation
// NumberContainers nc = new NumberContainers();
// nc.find(10); // There is no index that is filled with number 10. Therefore, we return -1.
// nc.change(2, 10); // Your container at index 2 will be filled with number 10.
// nc.change(1, 10); // Your container at index 1 will be filled with number 10.
// nc.change(3, 10); // Your container at index 3 will be filled with number 10.
// nc.change(5, 10); // Your container at index 5 will be filled with number 10.
// nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the smallest index that is filled with 10 is 1, we return 1.
// nc.change(1, 20); // Your container at index 1 will be filled with number 20. Note that index 1 was filled with 10 and then replaced with 20. 
// nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest index that is filled with 10 is 2. Therefore, we return 2.

// Constraints:

// 1 <= index, number <= 109
// At most 105 calls will be made in total to change and find.
