//
// Created by jian.yeung on 2020/12/7.
//

#include "Message.h"

Message::Message() : Message(0, 0, 0, 0, nullptr) {

}

Message::Message(int what) : Message(what, 0, 0, 0, nullptr) {
}

Message::Message(int what, int arg1) : Message(what, arg1, 0, 0, nullptr) {

}

Message::Message(int what, int arg1, int arg2) : Message(what, arg1, arg2, 0, nullptr) {

}

Message::Message(int what, int arg1, int arg2, long uptimeMillis) : Message(what, arg1, arg2, uptimeMillis, nullptr) {

}

Message::Message(int what, int arg1, int arg2, long uptimeMillis, Handler *target) : what(what), arg1(arg1),
                                                                                     arg2(arg2) {
    this->when = std::chrono::system_clock::now() + std::chrono::milliseconds(uptimeMillis);
    this->task = nullptr;
    this->target = target;
}

void Message::setWhen(std::chrono::system_clock::time_point &when) {
    this->when = when;
}

void Message::setTask(std::function<void()> &&f) {
    this->task = f;
}

void Message::setTarget(Handler *handler) {
    this->target = handler;
}

Message::~Message() {

}

Message &Message::operator=(const Message &msg) {
    this->what = msg.what;
    this->arg1 = msg.arg1;
    this->arg2 = msg.arg2;
    this->when = msg.when;
    this->task = msg.task;
    this->target = msg.target;

    return *this;
}


