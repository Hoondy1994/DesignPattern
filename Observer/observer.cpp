#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 抽象观察者
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() {}
};

// 抽象主题（被观察者）
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

// 具体主题
class ConcreteSubject : public Subject {
private:
    std::vector<Observer*> observers;
    std::string state;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notify() override {
        for (auto* observer : observers) {
            observer->update(state);
        }
    }

    void setState(const std::string& newState) {
        state = newState;
        notify();
    }

    std::string getState() const {
        return state;
    }
};

// 具体观察者 A
class ConcreteObserverA : public Observer {
private:
    std::string name;
public:
    ConcreteObserverA(const std::string& n) : name(n) {}

    void update(const std::string& message) override {
        std::cout << "Observer A (" << name << ") received update: " << message << std::endl;
    }
};

// 具体观察者 B
class ConcreteObserverB : public Observer {
private:
    std::string name;
public:
    ConcreteObserverB(const std::string& n) : name(n) {}

    void update(const std::string& message) override {
        std::cout << "Observer B (" << name << ") received update: " << message << std::endl;
    }
};

// 测试代码
int main() {
    ConcreteSubject subject;

    ConcreteObserverA observer1("Alice");
    ConcreteObserverB observer2("Bob");

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setState("State #1");

    subject.detach(&observer1);

    subject.setState("State #2");

    return 0;
}
