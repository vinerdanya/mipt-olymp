#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
public:
    vector<long long> tree, lazy;
    int n;
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }
    // создаем дерево
    void build(const vector<int>& arr, int node, int start, int end) {
        // если мы в листе, то просто сохраняем его значение
        if (start == end) {
            tree[node] = arr[start];
        } // если нет, то рекурсивно создаем два поддерева
        else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    // для прибавления элемента на участке
    void apply(int node, int start, int end, long long value) {
        tree[node] += value;
        if (start != end) {
            lazy[2 * node] += value;
            lazy[2 * node + 1] += value;
        }
    }
    // передаем в lazy для всех дочерних узлов
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
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    long long query(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (start > r || end < l) return 0;
        if (start >= l && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

    void update(int l, int r, long long value) {
        update(1, 0, n - 1, l, r, value);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    int n, m;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree segTree(n);
    segTree.build(arr, 1, 0, n - 1);
    
    for (int i = 0; i < segTree.tree.size(); i++){
        cout << segTree.tree[i] << ' ';
    }
    cout << '\n';

    cin >> m;
    vector<long long> results;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        if (type == 'a') {
            int l, r, add;
            cin >> l >> r >> add;
            segTree.update(l - 1, r - 1, add);
        } else if (type == 'm') {
            int l, r;
            cin >> l >> r;
            results.push_back(segTree.query(l - 1, r - 1));
        }
    }

    for (long long res : results) {
        cout << res << " ";
    }
    cout << endl;

    return 0;
}