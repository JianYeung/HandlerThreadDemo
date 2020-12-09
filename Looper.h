//
// Created by jian.yeung on 2020/12/7.
//

#ifndef HANDLERTHREAD_LOOPER_H
#define HANDLERTHREAD_LOOPER_H

#include <thread>
#include <vector>
#include "Message.h"

using namespace std;

class Looper {
private:
    static Looper *my_looper_;

    std::thread msg_thread_;
    std::vector<Message> msg_queue_;

    std::mutex queue_mutex_;
    std::condition_variable queue_condition_;

    bool stop = false;
    bool stopSafety = false;

public:
    static Looper* myLooper();

    static void prepare();

    static void loop();

    static void run();

    Looper();

    virtual ~Looper();

    bool enqueueMessage(Message &msg);

    void dequeueMessage(int what);

    void dequeueAllMessage();

    void quit();

    void quitSafety();
};


#endif //HANDLERTHREAD_LOOPER_H
