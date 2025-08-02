#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// 抽象观察者
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 被观察者（主题）
class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void attach(std::shared_ptr<Observer> obs) {
        observers.push_back(obs);
    }

    void detach(std::shared_ptr<Observer> obs) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notify(const std::string& message) {
        for (auto& obs : observers) {
            obs->update(message);
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
        std::cout << "[" << name << "] received: " << message << std::endl;
    }
};

int main() {
    auto subject = std::make_shared<Subject>();

    auto obs1 = std::make_shared<ConcreteObserver>("Alice");
    auto obs2 = std::make_shared<ConcreteObserver>("Bob");

    subject->attach(obs1);
    subject->attach(obs2);

    subject->notify("Event A");

    subject->detach(obs1);

    subject->notify("Event B");

    return 0;
}
