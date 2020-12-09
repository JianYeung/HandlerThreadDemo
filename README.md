# HandlerThreadDemo
 C++模仿Android实现Handler机制
 
 **调用方式：**
 ```c++
    Looper::prepare();
    Looper::loop();
    auto handler = MyHandler(Looper::myLooper());
    handler.postDelayed(fun1, 2000);
    handler.sendEmptyMessage(3);
    handler.sendEmptyMessageDelayed(TEST02, 3000);
    handler.removeMessage(3);
 ```
 
 **Handle处理逻辑：**
 
```c++
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
```
 
 **测试结果如图：**
 
![image](https://jim-1253486552.cos.ap-hongkong.myqcloud.com/WechatIMG53.jpeg)
