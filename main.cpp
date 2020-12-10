#include <iostream>
#include "Handler.h"

#define TEST01 0x01
#define TEST02 0x02

class MyHandler : public Handler {
public:
    MyHandler(Looper *looper) : Handler(looper) {

    }

    void handleMessage(Message &msg) override {
        int what = msg.what;
        switch (what) {
            case TEST01:
                std::cout << "Test 01" << endl;
                break;
            case TEST02:
                std::cout << "Test 02" << endl;
                break;
            default:
                std::cout << "Test default" << endl;
                break;
        }
    }
};

void fun1() {
    std::cout << "Test fun1" << endl;
}

int main() {
    Looper::prepare();
    Looper::loop();
    auto handler = MyHandler(Looper::myLooper());
    handler.postDelayed(fun1, 2000);
    handler.sendEmptyMessage(3);
    handler.sendEmptyMessageDelayed(TEST02, 3000);
    handler.removeMessage(3);
    std::cout << "Hello, World!" << endl;
    cin.get();
    return 0;
}
