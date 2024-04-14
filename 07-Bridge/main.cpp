#include <iostream>
#include <string>

/// 接口
// 窗体抽象类
class WindowImp;
class Window {
public:
    Window();
    virtual ~Window();

    // 矩形
    struct Rect {
        Rect() {}
        Rect(double x_, double y_, double width_, double height_)
            : x(x_), y(y_), width(width_), height(height_) {}
        virtual ~Rect() {}

        double x;
        double y;
        double width;
        double height;
    };

    void DrawText(const std::string& text);
    void DrawRect(const Rect& rect);
private:
    WindowImp* _imp = nullptr;
};
// 窗体类型一般由操作系统决定，这里假设参数给定
static std::string sWindowType = "XWindow";

// 窗体实现类
class WindowImp {
public:
    WindowImp() {}
    virtual ~WindowImp() {}

    // 直线
    struct Line {
        Line() {}
        Line(double x1_, double y1_, double x2_, double y2_)
            : x1(x1_), y1(y1_), x2(x2_), y2(y2_) {}
        virtual ~Line() {}

        double x1;
        double y1;
        double x2;
        double y2;
    };

    virtual void DevDrawText(const std::string& text) = 0;
    virtual void DevDrawLine(const Line& line) = 0;
};

// 具体实现类
class XWindowImp : public WindowImp {
public:
    XWindowImp() {}
    virtual ~XWindowImp() {}
    void DevDrawText(const std::string& text) override {
        std::cout << "Text: <" << text << "> in XWindow!" << std::endl;
    }
    void DevDrawLine(const Line& line) override {
        std::cout << "Line: (" 
            << line.x1 << "," << line.y1 << ")-(" 
            << line.x2 << "," << line.y2 << ") in XWindow!" << std::endl;
    }
};
class PMWindowImp : public WindowImp {
public:
    PMWindowImp() {}
    virtual ~PMWindowImp() {}
    void DevDrawText(const std::string& text) override {
        std::cout << "Text: <" << text << "> in PMWindow!" << std::endl;
    }
    void DevDrawLine(const Line& line) override {
        std::cout << "Line: (" 
            << line.x1 << "," << line.y1 << ")-(" 
            << line.x2 << "," << line.y2 << ") in PMWindow!" << std::endl;
    }
};

// 窗体实现函数
Window::Window() {
    if (sWindowType == "XWindow") {
        _imp = new XWindowImp();
    } else {
        _imp = new PMWindowImp();
    }
}
Window::~Window() {
    if (_imp) {
        delete _imp;
        _imp = nullptr;
    }
}

void Window::DrawText(const std::string& text) {
    _imp->DevDrawText(text);
}
void Window::DrawRect(const Rect& rect) {
    WindowImp::Line line;
    // line1
    line.x1 = rect.x; line.y1 = rect.y;
    line.x2 = rect.x + rect.width; line.y2 = rect.y;
    _imp->DevDrawLine(line);
    // line2
    line.x1 = rect.x + rect.width; line.y1 = rect.y;
    line.x2 = rect.x + rect.width; line.y2 = rect.y + rect.height;
    _imp->DevDrawLine(line);
    // line3
    line.x1 = rect.x + rect.width; line.y1 = rect.y + rect.height;
    line.x2 = rect.x; line.y2 = rect.y + rect.height;
    _imp->DevDrawLine(line);
    // line4
    line.x1 = rect.x; line.y1 = rect.y + rect.height;
    line.x2 = rect.x; line.y2 = rect.y;
    _imp->DevDrawLine(line);
}

// 具体窗口类
class IconWindow : public Window {
public:
    IconWindow() {}
    virtual ~IconWindow() {}

    void DrawBorder() {
        std::cout << "=========IconBorder=========" << std::endl;
        Rect rect(0, 0, 128, 128);
        this->DrawRect(rect);
        this->DrawText("icon");
        std::cout << "============================" << std::endl;
    }
};
class TranslentWindow : public Window {
public:
    TranslentWindow() {}
    virtual ~TranslentWindow() {}

    void DrawCloseBox() {
        std::cout << "==========CloseBox==========" << std::endl;
        Rect rect(0, 0, 300, 100);
        this->DrawRect(rect);
        std::cout << "============================" << std::endl;
    }
};

// use it!
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please input window type!" << std::endl;
        return -1;
    }
    sWindowType = argv[1];
    
    IconWindow iconWindow;
    iconWindow.DrawBorder();

    TranslentWindow translentWindow;
    translentWindow.DrawCloseBox();
    return 0;
}