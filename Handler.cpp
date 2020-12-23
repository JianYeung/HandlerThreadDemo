//
// Created by jian.yeung on 2020/12/7.
//

#include <iostream>
#include "Handler.h"

#include "Looper.h"
#include "Message.h"


Handler::Handler() = default;

Handler::Handler(Looper *looper) {
    my_looper_ = looper;
}

Handler::~Handler() {
    delete my_looper_;
}

void Handler::setLooper(Looper *looper) {
    my_looper_ = looper;
}

bool Handler::post(std::function<void()> &&f, bool flush) {
    if (flush) {
        my_looper_->dequeueAllMessage();
    }
    return postDelayed(std::forward<std::function<void()>>(f), 0);
}

bool Handler::postDelayed(std::function<void()> &&f, long delayMillis) {
    if (delayMillis < 0) {
        return false;
    }
    Message msg {};
    msg.setWhen(delayMillis);
    msg.setTask(std::forward<std::function<void()>>(f));
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

bool Handler::postAtTime(std::function<void()> &&f, std::chrono::system_clock::time_point when) {
    if (my_looper_ == nullptr) {
        return false;
    }
    Message msg {};
    msg.setWhen(when);
    msg.setTask(std::forward<std::function<void()>>(f));
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

bool Handler::sendMessage(Message &msg, bool flush) {
    if (flush) {
        my_looper_->dequeueAllMessage();
    }
    return sendMessageDelayed(msg, 0);
}

bool Handler::sendMessageDelayed(Message &msg, long delayMillis) {
    if (delayMillis < 0) {
        return false;
    }
    msg.setWhen(delayMillis);
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

bool Handler::sendMessageAtTime(Message &msg, std::chrono::system_clock::time_point when) {
    if (my_looper_ == nullptr) {
        return false;
    }
    msg.setWhen(when);
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

bool Handler::sendEmptyMessage(int what, bool flush) {
    if (flush) {
        my_looper_->dequeueAllMessage();
    }
    return sendEmptyMessageDelayed(what, 0);
}

bool Handler::sendEmptyMessageDelayed(int what, long delayMillis) {
    if (what < 0 || delayMillis < 0) {
        return false;
    }

    Message msg(what);
    msg.setWhen(delayMillis);
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

bool Handler::sendEmptyMessageAtTime(int what, std::chrono::system_clock::time_point when) {
    if (my_looper_ == nullptr) {
        return false;
    }

    if (what < 0) {
        return false;
    }

    Message msg(what);
    msg.setWhen(when);
    msg.setTarget(this);
    return my_looper_->enqueueMessage(msg);
}

void Handler::removeMessage(int what) {
    if (my_looper_ == nullptr) {
        return;
    }
    my_looper_->dequeueMessage(what);
}

void Handler::removeCallbacksAndMessages() {
    if (my_looper_ == nullptr) {
        return;
    }
    my_looper_->dequeueAllMessage();
}

void Handler::dispatchMessage(Message &msg) {
    if (msg.task != nullptr) {
        msg.task();
    } else {
        if (msg.what < 0) {
            return;
        }

        handleMessage(msg);
    }
}

void Handler::handleMessage(Message &msg) {
}

void Handler::quit() {
    if (my_looper_ == nullptr) {
        return;
    }
    my_looper_->quit();
}

void Handler::quitSafety() {
    if (my_looper_ == nullptr) {
        return;
    }
    my_looper_->quitSafety();
}
