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
    void *obj;
    std::chrono::system_clock::time_point when;
    Function task;
    Handler *target;

public:
    Message();

    explicit Message(int what);

    explicit Message(int what, int arg1);

    explicit Message(int what, int arg1, int arg2);

    explicit Message(int what, int arg1, int arg2, void *obj);

    explicit Message(int what, int arg1, int arg2, void *obj, long uptimeMillis);

    explicit Message(int what, int arg1, int arg2, void *obj, long uptimeMillis, Handler *target);

    virtual ~Message();

    void setObj(void *obj);

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
