#include <iostream>
#include <memory>


using namespace std;


class Product
{
public:
	virtual void use() = 0;
	virtual ~Product() {}
};


class ProductA : public Product
{

public:

	void use()override
	{
		cout << "use product A" << endl;
	}

};

class ProductB : public Product {
public:
	void use() override {
		std::cout << "use product B" << std::endl;
	}
};


class SimpleFactory {
public:
	static std::unique_ptr<Product> create(const std::string& type) {
		if (type == "A") return std::make_unique<ProductA>();
		if (type == "B") return std::make_unique<ProductB>();
		return nullptr;
	}
};



int main()
{
	auto product = SimpleFactory::create("A");
	product->use();
	return 0;
}