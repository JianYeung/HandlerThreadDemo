//
// Created by jian.yeung on 2020/12/7.
//
#include "Looper.h"

#include <iostream>
#include "Handler.h"

void Looper::run(Looper *looper) {
    auto my_looper_ = looper;
    while (true) {
        Message msg;
        {
            std::unique_lock<std::mutex> lock(my_looper_->queue_mutex_);
            if (my_looper_->msg_queue_.empty()) {
                my_looper_->queue_condition_.wait(lock, [my_looper_] {
                    return my_looper_->stop || my_looper_->stopSafety || !my_looper_->msg_queue_.empty();
                });
            } else {
                my_looper_->queue_condition_.wait_until(lock, my_looper_->msg_queue_.back().when, [my_looper_]  {
                    return my_looper_->stop || my_looper_->stopSafety || my_looper_->msg_queue_.empty();
                });
            }

            if (my_looper_->stopSafety && my_looper_->msg_queue_.empty()) {
                return;
            }

            if (my_looper_->stop) {
                my_looper_->msg_queue_.clear();
                return;
            }

            if (!my_looper_->msg_queue_.empty()) {
                Message temp = my_looper_->msg_queue_.back();
                auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
                auto when = std::chrono::time_point_cast<std::chrono::milliseconds>(temp.when);
                auto delay = now.time_since_epoch().count() - when.time_since_epoch().count();
                if (delay >= 0) {
                    msg = std::move(temp);
                    my_looper_->msg_queue_.pop_back();
                }
            }
        }

        if (msg.target != nullptr) {
            msg.target->dispatchMessage(msg);
        }
    }
}

Looper::Looper() {
    msg_queue_ = std::vector<Message>();
    msg_thread_ = std::thread(&Looper::run, this);
}

Looper::~Looper() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop = true;
    }
    queue_condition_.notify_all();
    msg_thread_.join();
    msg_queue_.clear();
}

bool Looper::enqueueMessage(Message &msg) {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    auto i = std::find(msg_queue_.begin(), msg_queue_.end(), msg);
    if (i != msg_queue_.end()) {
        msg_queue_.erase(i);
    }

    if (msg.target == nullptr && msg.task == nullptr) {
        return false;
    }

    std::cout << "enqueueMessage msg what : " << msg.what << std::endl;
    msg_queue_.push_back(msg);
    std::sort(msg_queue_.begin(), msg_queue_.end(), greater<Message>());
    queue_condition_.notify_one();
    return true;
}

void Looper::dequeueMessage(int what) {
    if (what < 0) {
        return;
    }
    std::unique_lock<std::mutex> lock(queue_mutex_);
    std::cout << "dequeueMessage msg what : " << what << std::endl;
    auto i = std::find(msg_queue_.begin(), msg_queue_.end(), what);
    if (i != msg_queue_.end()) {
        msg_queue_.erase(i);
    }
}

void Looper::dequeueAllMessage() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    msg_queue_.clear();
}

void Looper::quit() {
    stop = true;
}

void Looper::quitSafety() {
    stopSafety = true;
}



