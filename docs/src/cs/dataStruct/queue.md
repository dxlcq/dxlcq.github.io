## 参考



<br>

---


## 安全队列

```cpp
#pragma once
#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class queue_safe {
   public:
    queue_safe() = default;
    ~queue_safe() = default;
    queue_safe(const queue_safe&) = delete;
    queue_safe& operator=(const queue_safe&) = delete;
    queue_safe(queue_safe&&) = delete;
    queue_safe& operator=(queue_safe&&) = delete;

    void push(T&& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(std::move(value));
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return std::nullopt;
        }
        T result = std::move(_queue.front());
        _queue.pop();
        return result;
    }

   private:
    std::queue<T> _queue;
    std::mutex _mutex;
};
```