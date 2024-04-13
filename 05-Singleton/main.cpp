#include <iostream>

class Singleton {
public:
    virtual ~Singleton() = default;
    static Singleton* Instance() {
        static Singleton s_instance;
        return &s_instance;
    }
    void print() {
        std::cout << "I'm a singleton" << std::endl;
    }
private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

///use it!
int main(int argc, char* argv[]) {
    Singleton::Instance()->print();
    return 0;
}