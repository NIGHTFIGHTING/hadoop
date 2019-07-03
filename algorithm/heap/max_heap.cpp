#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

template<typename T>
class MaxHeap {
public:
    vector<T> data;
    MaxHeap(int capacity) {
        data.resize(capacity);
    }
    MaxHeap(const vector<T> vec) {
        copy(vec.begin(), vec.end(), data.begin());
        for (int i = parent(data,size()-1); i >= 0; i--) {
            sift_down(i);
        }
    }
    // 返回堆中的元素个数
    int size() {
        return data.size();
    }
    // 返回一个布尔值,表示堆中是否为空
    bool is_empty() {
        return data.empty();
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的父亲节点的索引
    int parent(int index) {
        if (index == 0) {
            std::cout << "";
        }
        return (index - 1) / 2;
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的左孩子节点的索引
    int left_child(int index) {
        return index * 2 + 1;
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的右孩子节点的索引
    int right_child(int index) {
        return index * 2 + 2;
    }
    void add(T e) {
        cout << "e:" << e << endl;
        data.push_back(e);
        sift_up(data.size() - 1);
    }
    T find_max() {
        if (data.size() == 0) {
            std::cout << "";
            return -1;
        }
        cout << data[0] << endl;
        return data[0];
    }
    T extract_max() {
        T ret = find_max();
#if 0
        swap(data[0], data[data.size() - 1]);
        cout << *(data.begin() + (data.size() -2)) << " ";
        data.erase(data.begin() + (data.size() -2));
        sift_down(0);
#endif
        return ret;
    }
    T replace(T e) {
        T ret = find_max();
        data[0] = e;
        sift_down(0);
        return ret;
    }
 private:
    void sift_up(int index) {
        while (index > 0 && data[parent(index)] < data[index]) {
            cout << "data[parent(index)]" << data[parent(index)] << " data[index]:" << data[index] << endl;
            swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }
    void sift_down(int index) {
        while (left_child(index) < data.size()) {
            int max_index = left_child(index);
            if (right_child(index) < data.size() && data[left_child(index)] < data[right_child(index)]) {
                max_index = right_child(index);
            }
            if (data[max_index] < data[index]) {
                break;
            }
            swap(data[max_index], data[index]);
            index = max_index;
        }
    }
};

template<typename T>
class PriorityQueue {
public:
    PriorityQueue() {
    }
    int get_size() {
        return max_heap.size();
    }
    bool is_empty() {
        return max_heap.empty();
    }
    T get_front() {
        return max_heap.find_max();
    }
    void enqueue(T e) {
        max_heap.add(e);
    }
    void dequeue() {
        return max_heap.extract_max();
    }

private:
    MaxHeap<T> max_heap;
};

int main() {
    srand((unsigned)time(NULL));
    MaxHeap<int> heap(10);
    for (int i = 0; i < 10; ++i) {
        //int num = rand()%10;
        heap.add(i);
    }
    for (int i = 0; i < 10; ++i) {
        cout << heap.data[i] << " ";
    }
    cout << "------------" << endl;
    vector<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr[i] = heap.extract_max();
        std::cout << arr[i] << " ";
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
}
