// 自动注册辅助模板
template <typename BaseType, typename DerivedType>
class Register {
public:
    Register(const std::string& name) {
        Factory<BaseType>::registerProduct(name, []() {
            return std::make_unique<DerivedType>();
        });
    }
};

// 注册宏（简化用户调用）
#define REGISTER_PRODUCT(BaseType, DerivedType, name) \
    static Register<BaseType, DerivedType> reg_##DerivedType(name)
