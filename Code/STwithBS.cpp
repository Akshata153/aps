#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Define a type for the accumulator
using Acc = int;

// Sample predicate function for demonstration
template<typename T>
int pred(T val) {
    return val;
}

// Segment Tree class
class SegmentTree {
private:
    vector<int> T;
    int n; // size of the array

    // Build the segment tree
    void build(vector<int>& arr, int node, int b, int e) {
        if (b == e) {
            T[node] = arr[b];
        } else {
            int m = (b + e) / 2;
            build(arr, node * 2, b, m);
            build(arr, node * 2 + 1, m + 1, e);
            T[node] = T[node * 2] + T[node * 2 + 1]; // change as per need
        }
    }

    // Search function with accumulator and predicate
    int search(int node, int b, int e, int l, int r, Acc& acc, function<int(Acc)> pred) {
        if (e <= l) return -1;
        if (b >= r) return b;
        if (b >= l && e <= r && pred(acc + T[node]) == 0) {
            acc = acc + T[node];
            return -1;
        }
        if (b + 1 == e) return b;

        int m = (b + e) / 2;
        int res = search(node * 2, b, m, l, r, acc, pred);
        if (res != -1) return res;
        return search(node * 2 + 1, m, e, l, r, acc, pred);
    }

public:
    // Constructor to initialize the segment tree
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        T.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    // Public method to perform search
    int search(int l, int r, Acc& acc, function<int(Acc)> pred) {
        return search(1, 0, n - 1, l, r, acc, pred);
    }
};

int main() {
    // Example usage
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    Acc accumulator = 0;
    int result = st.search(0, 4, accumulator, pred<Acc>);

    if (result != -1) {
        cout << "Found element at index: " << result << endl;
    } else {
        cout << "No element found within the range." << endl;
    }

    return 0;
}
