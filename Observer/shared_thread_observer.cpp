#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <algorithm>

// 抽象观察者
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 被观察者（线程安全）
class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::mutex mtx;

public:
    void attach(std::shared_ptr<Observer> obs) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.push_back(obs);
    }

    void detach(std::shared_ptr<Observer> obs) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notify(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& obs : observers) {
            if (obs) obs->update(message);
        }
    }
};

// 具体观察者
class ConcreteObserver : public Observer {
private:
    std::string name;
public:
    ConcreteObserver(std::string name_) : name(std::move(name_)) {}
    void update(const std::string& message) override {
        std::cout << "[" << name << "] got: " << message << std::endl;
    }
};

int main() {
    auto subject = std::make_shared<Subject>();

    auto obs1 = std::make_shared<ConcreteObserver>("Thread1");
    auto obs2 = std::make_shared<ConcreteObserver>("Thread2");

    subject->attach(obs1);
    subject->attach(obs2);

    std::thread t1([&]() { subject->notify("From t1"); });
    std::thread t2([&]() { subject->notify("From t2"); });

    t1.join();
    t2.join();

    return 0;
}
