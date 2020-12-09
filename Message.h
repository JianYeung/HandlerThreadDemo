//
// Created by jian.yeung on 2020/12/7.
//

#ifndef HANDLERTHREAD_MESSAGE_H
#define HANDLERTHREAD_MESSAGE_H

#include <functional>
#include <chrono>

using namespace std;

typedef std::function<void()> Function;

class Handler;
class Message {
public:
    int what;
    int arg1;
    int arg2;
    std::chrono::system_clock::time_point when;
    Function task;
    Handler *target;
    Message *next;

public:
    Message();

    Message(int what);

    Message(int what, int arg1);

    Message(int what, int arg1, int arg2);

    Message(int what, int arg1, int arg2, long uptimeMillis);

    Message(int what, int arg1, int arg2, long uptimeMillis, Handler *target);

    virtual ~Message();

    void setWhen(std::chrono::system_clock::time_point &when);

    void setTask(std::function<void()> &&f);

    void setTarget(Handler *handler);

    Message &operator=(const Message &msg);

    bool operator==(int what) const {
        return (this->what == what);
    }

    bool operator==(const Message &msg) const {
        return (this->what == msg.what) && (this->task != nullptr) && (msg.task != nullptr);
    }

    bool operator>(const Message &msg) const {
        return (this->when > msg.when);
    }

    bool operator<(const Message &msg) const {
        return (this->when < msg.when);
    }
};


#endif //HANDLERTHREAD_MESSAGE_H
