#include <iostream>
#include <memory>
#include <string>

class Cpu {
public:
    Cpu() {}
    virtual ~Cpu() {}

    void Start() {
        std::cout << "Cpu start!" << std::endl;
    }
    void Stop() {
        std::cout << "Cpu stop!" << std::endl;
    }
};
class Memory {
public:
    Memory() {}
    virtual ~Memory() {}
    
    void Start() {
        std::cout << "Memory start!" << std::endl;
    }
    void Stop() {
        std::cout << "Memory stop!" << std::endl;
    }
};
class Screen {
public:
    Screen() {}
    virtual ~Screen() {}
    
    void Start() {
        std::cout << "Screen start!" << std::endl;
    }
    void Stop() {
        std::cout << "Screen stop!" << std::endl;
    }
};
class ComputerFacade {
public:
    ComputerFacade() {}
    virtual ~ComputerFacade() {}

    void Start() {
        std::cout << "Computer is starting!" << std::endl;
        _cpu.Start();
        _memory.Start();
        _screen.Start();
    }

    void Stop() {
        _cpu.Stop();
        _memory.Stop();
        _screen.Stop();
        std::cout << "Computer is stopped!" << std::endl;
    }
private:
    Cpu _cpu;
    Memory _memory;
    Screen _screen;
};

// use it!
int main(int argc, char* argv[]) {
    ComputerFacade computer;
    // 开机
    computer.Start();
    // 关机
    computer.Stop();
    return 0;
}