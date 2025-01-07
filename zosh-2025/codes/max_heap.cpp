#include <iostream>
#include <vector>

class MaxHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            heapifyUp(parent); 
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]); 
            heapifyDown(largest);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value); // Добавляем в конец
        heapifyUp(heap.size() - 1); // Просеиваем вверх
    }

    int removeMax() {
        int maxElem = heap[0]; // Максимальный элемент (корень)
        heap[0] = heap.back(); // Перемещаем последний элемент на корень
        heap.pop_back(); // Удаляем последний элемент
        heapifyDown(0); // Просеиваем вниз, начиная с корня

        return maxElem;
    }

    int peek() const {
        return heap[0];
    }

    void display() const {
        for (int val : heap) {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
};
