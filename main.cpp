#include <iostream>
#include "SPSC.h" // Replace with actual file if needed

int main() {
    constexpr int size = 8;
    SPSC<int, size> queue;

    // Push some elements
    for (int i = 0; i < size - 1; ++i) {
        auto result = queue.push(i);
        if (result) {
            std::cout << "Pushed: " << *result << std::endl;
        } else {
            std::cout << "Queue full. Could not push: " << i << std::endl;
        }
    }

    std::cout << "---- Now popping ----" << std::endl;

    // Pop all elements
    for (int i = 0; i < size - 1; ++i) {
        auto result = queue.pop();
        if (result) {
            std::cout << "Popped: " << *result << std::endl;
        } else {
            std::cout << "Queue empty at pop attempt #" << i << std::endl;
        }
    }

    return 0;
}
