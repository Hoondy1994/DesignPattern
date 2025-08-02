#include <iostream>
#include <vector>
#include <memory>

// 抽象策略类
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

// 具体策略：冒泡排序
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort\n";
        int n = data.size();
        for (int i = 0; i < n - 1; ++i)
            for (int j = 0; j < n - i - 1; ++j)
                if (data[j] > data[j + 1])
                    std::swap(data[j], data[j + 1]);
    }
};

// 具体策略：快速排序
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort\n";
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int>& data, int left, int right) {
        if (left >= right) return;
        int pivot = data[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (data[j] < pivot)
                std::swap(data[++i], data[j]);
        }
        std::swap(data[i + 1], data[right]);
        quickSort(data, left, i);
        quickSort(data, i + 2, right);
    }
};

// 上下文类：使用某个策略
class Context {
private:
    std::unique_ptr<SortStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<SortStrategy> s) {
        strategy = std::move(s);
    }

    void executeStrategy(std::vector<int>& data) {
        if (strategy)
            strategy->sort(data);
        else
            std::cerr << "No strategy set.\n";
    }
};

// 测试代码
int main() {
    std::vector<int> data = { 5, 3, 8, 6, 2 };

    Context context;

    // 使用冒泡排序
    context.setStrategy(std::make_unique<BubbleSort>());
    std::vector<int> data1 = data;
    context.executeStrategy(data1);
    for (int n : data1) std::cout << n << " ";
    std::cout << "\n";

    // 使用快速排序
    context.setStrategy(std::make_unique<QuickSort>());
    std::vector<int> data2 = data;
    context.executeStrategy(data2);
    for (int n : data2) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
