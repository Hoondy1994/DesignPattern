#include <iostream>
#include <memory>

// 产品族接口
class Phone {
public:
    virtual void call() = 0;
    virtual ~Phone() {}
};

class Computer {
public:
    virtual void run() = 0;
    virtual ~Computer() {}
};

// 具体产品：Apple
class ApplePhone : public Phone {
public:
    void call() override {
        std::cout << "Apple手机打电话" << std::endl;
    }
};

class AppleComputer : public Computer {
public:
    void run() override {
        std::cout << "Apple电脑运行" << std::endl;
    }
};

// 具体产品：Huawei
class HuaweiPhone : public Phone {
public:
    void call() override {
        std::cout << "Huawei手机打电话" << std::endl;
    }
};

class HuaweiComputer : public Computer {
public:
    void run() override {
        std::cout << "Huawei电脑运行" << std::endl;
    }
};

// 抽象工厂接口
class AbstractFactory {
public:
    virtual std::unique_ptr<Phone> createPhone() = 0;
    virtual std::unique_ptr<Computer> createComputer() = 0;
    virtual ~AbstractFactory() {}
};

// Apple工厂
class AppleFactory : public AbstractFactory {
public:
    std::unique_ptr<Phone> createPhone() override {
        return std::make_unique<ApplePhone>();
    }
    std::unique_ptr<Computer> createComputer() override {
        return std::make_unique<AppleComputer>();
    }
};

// Huawei工厂
class HuaweiFactory : public AbstractFactory {
public:
    std::unique_ptr<Phone> createPhone() override {
        return std::make_unique<HuaweiPhone>();
    }
    std::unique_ptr<Computer> createComputer() override {
        return std::make_unique<HuaweiComputer>();
    }
};

// 客户端
int main() {
    std::unique_ptr<AbstractFactory> factory = std::make_unique<HuaweiFactory>();
    auto phone = factory->createPhone();
    auto computer = factory->createComputer();

    phone->call();
    computer->run();
    return 0;
}
