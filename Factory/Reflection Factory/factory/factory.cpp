// --- 工厂模板基类 ---
template <typename BaseType>
class Factory {
public:
    using Creator = std::function<std::unique_ptr<BaseType>()>;

    // 注册产品
    static bool registerProduct(const std::string& name, Creator creator) {
        auto& map = getMap();
        return map.emplace(name, std::move(creator)).second;
    }

    // 创建产品
    static std::unique_ptr<BaseType> create(const std::string& name) {
        auto& map = getMap();
        auto it = map.find(name);
        if (it != map.end()) {
            return (it->second)();
        }
        throw std::runtime_error("未知产品类型: " + name);
    }

private:
    static std::unordered_map<std::string, Creator>& getMap() {
        static std::unordered_map<std::string, Creator> instance;
        return instance;
    }
};
