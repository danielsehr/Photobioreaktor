#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class RingBuffer
{
public:
    void push(const T &value)
    {
        buffer_[head_] = value;

        head_ = (head_ + 1) % Capacity;

        if (size_ < Capacity)
        {
            ++size_;
        }
    }

    [[nodiscard]]
    std::size_t size() const
    {
        return size_;
    }

    [[nodiscard]]
    constexpr std::size_t capacity() const
    {
        return Capacity;
    }

    [[nodiscard]]
    bool empty() const
    {
        return size_ == 0;
    }

    [[nodiscard]]
    const T &at(std::size_t index) const
    {
        assert(index < size_);

        if (size_ < Capacity)
        {
            return buffer_[index];
        }

        return buffer_[(head_ + index) % Capacity];
    }

private:
    std::array<T, Capacity> buffer_{};

    std::size_t head_ = 0;

    std::size_t size_ = 0;
};