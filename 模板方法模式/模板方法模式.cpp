#include <iostream>
using namespace std;

// 抽象类：饮料
class Beverage {
public:
    // 模板方法
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    // 具体方法：通用步骤
    void boilWater() {
        cout << "Boiling water" << endl;
    }

    void pourInCup() {
        cout << "Pouring into cup" << endl;
    }

    // 抽象方法：由子类实现
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // 虚析构函数
    virtual ~Beverage() {}
};

// 具体类：茶
class Tea : public Beverage {
public:
    void brew() override {
        cout << "Steeping the tea" << endl;
    }

    void addCondiments() override {
        cout << "Adding lemon" << endl;
    }
};

// 具体类：咖啡
class Coffee : public Beverage {
public:
    void brew() override {
        cout << "Dripping coffee through filter" << endl;
    }

    void addCondiments() override {
        cout << "Adding sugar and milk" << endl;
    }
};

// 客户端代码
int main() {
    Beverage* tea = new Tea();
    cout << "Making tea:" << endl;
    tea->prepareBeverage();
    delete tea;

    cout << endl;

    Beverage* coffee = new Coffee();
    cout << "Making coffee:" << endl;
    coffee->prepareBeverage();
    delete coffee;

    return 0;
}
