#include <iostream>
#include <memory>

// 产品接口
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() {}
};

// 具体产品
class ProductA : public Product {
public:
    void use() override {
        std::cout << "使用产品A" << std::endl;
    }
};

class ProductB : public Product {
public:
    void use() override {
        std::cout << "使用产品B" << std::endl;
    }
};

// 工厂接口
class Factory {
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
    virtual ~Factory() {}
};

// 具体工厂
class FactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductA>();
    }
};

class FactoryB : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductB>();
    }
};

// 客户端
int main() {
    std::unique_ptr<Factory> factory = std::make_unique<FactoryA>();
    auto product = factory->createProduct();
    product->use();
    return 0;
}
