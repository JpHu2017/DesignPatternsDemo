#include <iostream>
#include <memory>
#include <string>

/// 接口
// 可见组建
class VisualComponent {
public:
    using Ptr = std::shared_ptr<VisualComponent>;
    VisualComponent() {}
    virtual ~VisualComponent() {}
    virtual void Draw() = 0;
};

// 文本视口
class TextView : public VisualComponent {
public:
    TextView() : VisualComponent() {}
    virtual ~TextView() {}
    void Draw() override {
        std::cout << "Draw TextView!" << std::endl;
    }
};

// 装饰器
class Decorator : public VisualComponent {
public:
    Decorator(VisualComponent* vc) : VisualComponent(), _vc(vc) {}
    virtual ~Decorator() {}
    void Draw() override {
        if (_vc) {_vc->Draw();}
    };
private:
    VisualComponent* _vc = nullptr;
};

// 滚动条装饰器
class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(VisualComponent* vc) : Decorator(vc) {}
    virtual ~ScrollDecorator() {}
    void Draw() override {
        std::cout << ">>>" << std::endl;
        Decorator::Draw();
        ScrollTo();
        std::cout << "<<<" << std::endl;
    }
protected:
    void ScrollTo() {
        std::cout << "Draw Scroll!" << std::endl;
    }
};
// 边框装饰器
class BorderDecorator : public Decorator {
public:
    BorderDecorator(VisualComponent* vc) : Decorator(vc) {}
    virtual ~BorderDecorator() {}
    void Draw() override {
        std::cout << ">>>" << std::endl;
        Decorator::Draw();
        DrawBorder();
        std::cout << "<<<" << std::endl;
    }
protected:
    void DrawBorder() {
        std::cout << "Draw Border!" << std::endl;
    }
};

// use it!
int main(int argc, char* argv[]) {
    VisualComponent::Ptr textView(new TextView());
    
    // 滚动条装饰
    Decorator::Ptr scrollDecorator(new ScrollDecorator(textView.get()));
    scrollDecorator->Draw();
    
    // 边框装饰
    Decorator::Ptr borderDecorator(new BorderDecorator(textView.get()));
    borderDecorator->Draw();
    return 0;
}