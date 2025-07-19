#include<array>
#include<optional>
template<typename T>
class SPSC{
    std::array<T , 8> arr;
    int head;
    int tail;
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
template<typename T>
SPSC<T>::SPSC()
{
    head = 0;
    tail = 0;
}
template<typename T>
inline std::optional<T> SPSC<T> :: push(T element)
{
    if(wrap_around(head+1)) == tail)
    {
        return std::nullopt;
    }
    arr[head] = element;
    head++;
    head = wrap_around(head);
    return element;
}
template<typename T>
inline std::optional<T> SPSC<T>::pop()
{
    if(head == tail)
    {
        return std::nullopt;
    }
    T popped_element = arr[tail];
    tail++;
    tail = wrap_around(tail);
    return popped_element;  
}