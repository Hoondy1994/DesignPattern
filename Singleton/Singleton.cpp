#include <iostream>
using namespace std;

class Singleton {
private:
    // 1. 私有构造函数，防止外部创建对象
    Singleton() {
        cout << "Singleton Constructor Called" << endl;
    }

    // 2. 禁止复制和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 3. 静态成员指针，指向唯一实例
    static Singleton* instance;

public:
    // 4. 提供一个静态方法获取唯一实例
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();  // 延迟初始化（lazy initialization）
        }
        return instance;
    }

    // 示例方法
    void sayHello() {
        cout << "Hello from Singleton" << endl;
    }
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;

int main() {
    // 获取唯一实例
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    s1->sayHello();

    // 验证两个指针是否相同（是同一个实例）
    if (s1 == s2) {
        cout << "Same instance!" << endl;
    }
    else {
        cout << "Different instances!" << endl;
    }

    return 0;
}
