#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

// --- 产品基类 ---
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

// --- 产品子类A ---
class ProductA : public Product {
public:
    void use() override {
        std::cout << "使用产品A" << std::endl;
    }
};

// --- 产品子类B ---
class ProductB : public Product {
public:
    void use() override {
        std::cout << "使用产品B" << std::endl;
    }
};
