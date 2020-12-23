//
// Created by jian.yeung on 2020/12/7.
//

#ifndef HANDLERTHREAD_HANDLER_H
#define HANDLERTHREAD_HANDLER_H

#include <vector>
#include <chrono>

#include "Looper.h"

using namespace std;

class Handler {
protected:
    Looper *my_looper_{};

public:
    Handler();

    explicit Handler(Looper *looper);

    virtual ~Handler();

    void setLooper(Looper *looper);

    bool post(std::function<void()> &&f, bool flush = false);

    bool postDelayed(std::function<void()> &&f, long delayMillis);

    bool postAtTime(std::function<void()> &&f, std::chrono::system_clock::time_point);

    bool sendMessage(Message &msg, bool flush = false);

    bool sendMessageDelayed(Message &msg,  long delayMillis);

    bool sendMessageAtTime(Message &msg, std::chrono::system_clock::time_point);

    bool sendEmptyMessage(int what, bool flush = false);

    bool sendEmptyMessageDelayed(int what, long delayMillis);

    bool sendEmptyMessageAtTime(int what, std::chrono::system_clock::time_point);

    void removeMessage(int what);

    void removeCallbacksAndMessages();

    void dispatchMessage(Message &msg);

    virtual void handleMessage(Message &msg);

    void quit();

    void quitSafety();
};


#endif //HANDLERTHREAD_HANDLER_H
