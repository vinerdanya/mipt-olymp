#include <iostream>
#include <vector>
#include <queue>

class MinHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[index] < heap[parent]) {
            std::swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        int minElem = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return minElem;
    }

    int getMin() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }
};

int main() {
    int q;
    std::cin >> q;

    MinHeap heap;

    for (int i = 0; i < q; ++i) {
        std::string query;
        std::cin >> query;

        if (query == "insert") {
            int x;
            std::cin >> x;
            heap.insert(x);
        } else if (query == "extractMin") {
            std::cout << heap.extractMin() << std::endl;
        } else if (query == "getMin") {
            std::cout << heap.getMin() << std::endl;
        }
    }

    return 0;
}
