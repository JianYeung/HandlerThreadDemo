#include <iostream>
#include "Handler.h"

#define TEST01 0x01
#define TEST02 0x02

class MyHandler : public Handler {
public:
    explicit MyHandler(Looper *looper) : Handler(looper) {

    }

    void handleMessage(Message &msg) override {
        int what = msg.what;
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto when = std::chrono::time_point_cast<std::chrono::milliseconds>(msg.when);
        auto delay = when.time_since_epoch().count() - now.time_since_epoch().count();
        switch (what) {
            case TEST01:
                std::cout <<"预期执行时间："<< when.time_since_epoch().count() << ",Test 01" << endl;
                std::cout <<"实际执行时间："<< now.time_since_epoch().count() << ",Test 01" << endl;
                std::cout <<"延迟了："<< delay << ",Test 01" << endl;
                break;
            case TEST02:
                std::cout <<"预期执行时间："<< when.time_since_epoch().count() << ",Test 02" << endl;
                std::cout <<"实际执行时间："<< now.time_since_epoch().count() << ",Test 02" << endl;
                std::cout <<"延迟了："<< delay << ",Test 02" << endl;
                break;
            default:
                std::cout <<"预期执行时间："<< when.time_since_epoch().count() << ",Test default" << endl;
                std::cout <<"实际执行时间："<< now.time_since_epoch().count() << ",Test default" << endl;
                std::cout <<"延迟了："<< delay << ",Test default" << endl;
                break;
        }
    }
};

void fun1() {
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    std::cout <<"实际执行时间："<< now.time_since_epoch().count() << ",Test fun1" << endl;
    std::cout << "Test fun1" << endl;
}

int main() {
    auto handler = MyHandler(new Looper());
    handler.postDelayed(fun1, 10000);
    handler.sendEmptyMessage(TEST01);
    handler.sendEmptyMessageDelayed(TEST02, 5000);
    std::cout << "Hello, World!" << endl;
    cin.get();
    return 0;
}
