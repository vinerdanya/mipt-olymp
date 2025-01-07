#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
    vector<pair<long long, int>> tree;
    vector<long long> lazy;
    int n;

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, {0, -1});
        lazy.assign(4 * n, 0);
    }

    void build(const vector<long long>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = {arr[start], start};  // Дерево хранит пару: (максимум, индекс)
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    // Слияние двух поддеревьев
    pair<long long, int> merge(const pair<long long, int>& left, const pair<long long, int>& right) {
        if (left.first > right.first) {
            return left;
        } else if (left.first < right.first) {
            return right;
        } else {
            return left.second < right.second ? left : right;  // В случае равенства максимума выбираем минимальный индекс
        }
    }

    void apply(int node, int start, int end, long long value) {
        tree[node].first += value;
        if (start != end) {
            lazy[2 * node] += value;
            lazy[2 * node + 1] += value;
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            apply(node, start, end, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long long value) {
        propagate(node, start, end);
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            apply(node, start, end, value);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, value);
        update(2 * node + 1, mid + 1, end, l, r, value);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    pair<long long, int> query(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (start > r || end < l) return {-1, -1};  // Возвращаем минимальное возможное значение и некорректный индекс
        if (start >= l && end <= r) return tree[node];
        int mid = (start + end) / 2;
        pair<long long, int> left_result = query(2 * node, start, mid, l, r);
        pair<long long, int> right_result = query(2 * node + 1, mid + 1, end, l, r);
        return merge(left_result, right_result);
    }

    void update(int l, int r, long long value) {
        update(1, 0, n - 1, l, r, value);
    }

    pair<long long, int> query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    int N;
    cin >> N;

    vector<long long> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(N);
    segTree.build(arr, 1, 0, N - 1);

    int K;
    cin >> K;

    for (int i = 0; i < K; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        pair<long long, int> result = segTree.query(l, r);
        cout << result.first << " " << result.second + 1 << endl;
    }

    return 0;
}
