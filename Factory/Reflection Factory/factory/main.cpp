int main() {
    // 动态创建产品
    std::unique_ptr<Product> p1 = Factory<Product>::create("A");
    std::unique_ptr<Product> p2 = Factory<Product>::create("B");

    p1->use();
    p2->use();

    return 0;
}
