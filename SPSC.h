#include<array>
#include<optional>
#include<atomic>
template<typename T , int SIZE>
class SPSC{
    std::array<std::aligned_storage_t<sizeof(T),alignof(T)>,SIZE> arr;
    alignas(64) std::atomic<int> head;
    alignas(64) std::atomic<int> tail;
    public:
        SPSC();
        std::optional<T> push(T element);
        std::optional<T> pop();
        constexpr int get_mask() const
        {
            return arr.size() - 1;
        }
        constexpr int wrap_around(int index) const 
        {
            return index & get_mask();
        }
};
template<typename T, int SIZE>
SPSC<T , SIZE>::SPSC()
{
    head = 0;
    tail = 0;
}
template<typename T , int SIZE>
inline std::optional<T> SPSC<T,SIZE>:: push(T element)
{
    int current_head = head.load(std::memory_order_relaxed);
    int next_head = wrap_around(current_head+1);
    int current_tail = tail.load(std::memory_order_acquire);
    if(next_head == current_tail)
    {
        return std::nullopt;
    }
    new (static_cast<void*>(&arr[current_head])) T(element);
    head.store(next_head , std::memory_order_release);
    return element;
}
template<typename T, int SIZE>
inline std::optional<T> SPSC<T, SIZE>::pop()
{
    int current_tail = tail.load(std::memory_order_relaxed);
    int current_head = head.load(std::memory_order_acquire);
    if (current_head == current_tail) {
        return std::nullopt; 
    }
    T* obj_ptr = reinterpret_cast<T*>(&arr[current_tail]);
    T popped_element = *obj_ptr;
    obj_ptr->~T(); 
    int next_tail = wrap_around(current_tail + 1);
    tail.store(next_tail, std::memory_order_release);
    return popped_element;
}