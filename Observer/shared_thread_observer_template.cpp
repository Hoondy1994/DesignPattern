#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>
#include <string>
#include <thread>

// 模板观察者接口
template<typename T>
class IObserver {
public:
    virtual void update(const T& data) = 0;
    virtual ~IObserver() = default;
};

// 模板线程安全主题
template<typename T>
class Subject {
private:
    std::vector<std::shared_ptr<IObserver<T>>> observers;
    std::mutex mtx;

public:
    void attach(std::shared_ptr<IObserver<T>> obs) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.push_back(obs);
    }

    void detach(std::shared_ptr<IObserver<T>> obs) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify(const T& data) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& obs : observers) {
            if (obs) obs->update(data);
        }
    }
};

// 整型观察者
class IntObserver : public IObserver<int> {
private:
    std::string name;
public:
    explicit IntObserver(std::string name_) : name(std::move(name_)) {}

    void update(const int& value) override {
        std::cout << "[" << name << "] got int: " << value << std::endl;
    }
};

// 字符串观察者
class StringObserver : public IObserver<std::string> {
private:
    std::string name;
public:
    explicit StringObserver(std::string name_) : name(std::move(name_)) {}

    void update(const std::string& msg) override {
        std::cout << "[" << name << "] got string: " << msg << std::endl;
    }
};

int main() {
    // 整数主题
    Subject<int> intSubject;
    auto intObs = std::make_shared<IntObserver>("IntReceiver");

    // 字符串主题
    Subject<std::string> strSubject;
    auto strObs = std::make_shared<StringObserver>("StrReceiver");

    intSubject.attach(intObs);
    strSubject.attach(strObs);

    std::thread t1([&]() { intSubject.notify(99); });
    std::thread t2([&]() { strSubject.notify("Hello Template"); });

    t1.join();
    t2.join();

    return 0;
}
