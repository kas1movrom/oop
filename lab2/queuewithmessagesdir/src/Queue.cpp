//
// Created by romka on 18.09.2023.
//

#include "../include/Queue.h"

namespace kas {
    Message *Queue::myRealloc(Message *array, int size, int start, int end) {
        auto *result = new Message[size];
        std::copy(array + start, array + end, result);
        delete[] array;
        return result;
    }

    Queue::Queue(int size, const Message *arr) : head(0), tail(size),
                    capacity(size), queue(new Message[capacity]) {
        std::copy(arr, arr + size, queue);
    }

    Queue::Queue(const Queue &queue1) : head(0), tail(queue1.tail - queue1.head),
                    capacity(queue1.tail - queue1.head), queue(new Message[capacity]) {
        std::copy(queue1.queue + queue1.head, queue1.queue + queue1.tail, this->queue);
    }

    Queue::Queue(Queue &&queue1) noexcept: head(queue1.head), tail(queue1.tail),
                    capacity(queue1.capacity), queue(queue1.queue) {
        queue1.queue = nullptr;
    }

    Queue &Queue::operator=(const Queue &queue1) {
        if (this == &queue1)
            return *this;

        capacity = queue1.tail - queue1.head;
        tail = capacity;
        head = 0;

        auto *array = new Message[capacity];
        delete[] queue;
        queue = array;

        std::copy(queue1.queue + queue1.head, queue1.queue + queue1.tail, queue);
        return *this;
    }

    Queue &Queue::operator=(Queue &&queue1) noexcept {
        std::swap(capacity, queue1.capacity);
        std::swap(head, queue1.head);
        std::swap(tail, queue1.tail);

        std::swap(queue, queue1.queue);
        return *this;
    }

    Message &Queue::operator--() {
        if (tail - head == 0)
            throw std::runtime_error("Queue is empty\n");

        if (tail - head < capacity / 2) {
            capacity /= 2;
            queue = myRealloc(queue, capacity, head, tail);
            tail -= head;
            head = 0;
        }
        return queue[head++];
    }

    Queue &Queue::operator+=(const Message &message) {
        if (tail == capacity) {
            capacity *= QUOTA;
            queue = myRealloc(queue, capacity, 0, tail);
        }
        queue[tail++] = message;
        return *this;
    }

    Queue Queue::operator[](const std::string &chatName) {
        Queue queueCopy(*this);
        head = 0;
        tail = 0;
        Queue result;

        for (int i = queueCopy.head; i < queueCopy.tail; ++i)
            if (queueCopy.queue[i].getChatName() == chatName)
                result += queueCopy.queue[i];
            else
                *this += queueCopy.queue[i];

        return result;
    }

    std::ostream &operator<<(std::ostream &c, const Queue &queue) {
        if (queue.tail - queue.head == 0) {
            c << "Queue is empty" << std::endl;
            return c;
        }
        for (int i = queue.head; i < queue.tail; ++i)
            c << queue.queue[i];
        return c;
    }

    std::istream &operator>>(std::istream &s, Queue &queue) {
        int size;
        s >> size;

        if (s.good()) {
            if (size >= 0 && size <= queue.capacity) {
                for (int i = 0; i < size; ++i) {
                    Message message;
                    s >> message;
                    if (s.good()) {
                        queue += message;
                    } else {
                        s.setstate(std::ios::failbit);
                        return s;
                    }
                }
            } else {
                s.setstate(std::ios::failbit);
            }
        }
        return s;
    }

    Queue &Queue::orderByChat() {
        std::sort(queue + head, queue + tail);
        return *this;
    }

    Message &Queue::searchMessage(const std::string &word) const {
        if (tail - head == 0)
            throw std::runtime_error("Queue is empty\n");

        for (int i = head; i < tail; ++i)
            if (queue[i].find(word))
                return queue[i];

        throw std::runtime_error("There is no messages with that word\n");
    }

    state Queue::checkState() const {
        if (tail - head == 0)
            return state::EMPTY;
        else
            return state::PART_FULL;
    }

    std::ostream &Queue::outputState(std::ostream &c, state st) {
        if (st == state::EMPTY)
            c << "Queue is empty" << std::endl;
        else
            c << "Queue is partially full" << std::endl;
        return c;
    }

    Queue &Queue::reorganizationQueue() {
        Queue queueCopy(*this);
        head = 0;
        tail = 0;

        for (int i = queueCopy.head; i < queueCopy.tail; ++i) {
            int k = i + 1;
            Message tmpMessage = queueCopy.queue[i];
            while (k != queueCopy.tail && queueCopy.queue[k].getChatName() == queueCopy.queue[k - 1].getChatName()) {
                tmpMessage = tmpMessage + queueCopy.queue[k++];
            }
            *this += tmpMessage;
            i += (k - i - 1);
        }
        return *this;
    }

} // kas