#ifndef FINALLAB2_QUEUE_H
#define FINALLAB2_QUEUE_H

#include "Message.h"
#include <algorithm>

using namespace Mes;

/**
 * @namespace kas
 * */
namespace kas {

    /**
     * @brief enum class for queue state
     * @detailed queue can be empty and partially full
     * */
    enum class state
    {
        EMPTY,
        PART_FULL
    };

    /**
     * @brief class describe data struct - messages queue
     * @detailed each instance of this class contains a pointer to
     * a dynamic array of messages, index of the beginning and end
     * of the queue, also contains max array size
     * */
    class Queue {
    private:
        static const int QUOTA = 2;
        int head, tail, capacity;

        Message *queue;

        static Message *myRealloc(Message *array, int size, int start, int end);

    public:

        /**
         * @brief default constructor without parameters
         * @details default
         * @returns new Queue with default fields: head = 0, tail = 0
         * capacity = 8, we also allocated memory for queue here(Queue)
         * */
        Queue() : head(0), tail(0), capacity(8), queue(new Message[capacity]) {}

        /**
         * @brief constructor with queue size and array of messages
         * @param size array length(int)
         * @param arr array of messages(Message*)
         * @returns new queue with passed size and messages(Queue)
         * */
        Queue(int size, const Message arr[]);

        /**
         * @brief destructor, frees memory allocated for the queue
         * */
        ~Queue() { delete[] queue; }

        /**
         * @brief copy constructor
         * @param queue1 passed queue(&Queue)
         * @returns new queue, copy of the passed queue(Queue)
         * */
        Queue(const Queue &queue1);

        /**
         * @brief moving constructor
         * @param queue1 passed queue(&Queue)
         * @return new queue, contains all fields in passed queue
         * */
        Queue(Queue &&queue1) noexcept;



        /**
         * @brief copy assignment operator
         * @detailed copies all parameters from one queue to another
         * @param queue1 passed queue(&Queue)
         * @returns reference to the caller queue
         * */
        Queue &operator=(const Queue &queue1);

        /**
         * @brief operator = : moving assignment operator
         * @detailed swaps the fields of the calling queue and
         * the passed one
         * @param queue1 : passed queue(&&queue1)
         * @return reference to the caller queue(&queue)
         * */
        Queue &operator=(Queue &&queue1) noexcept;

        /**
         * @brief operator -- : gets the first message from the queue
         * @detailed if the number of messages in the queue is less
         * than the memory allocated for it in half, then the memory is
         * distributed, after which the first element is taken
         * @return received message (&message)
         * @throw runtime_error if queue is empty
         * */
        Message &operator--();

        /**
         * @brief operator += : puts a new message into queue
         * @detailed if the queue is full, then redistribute the memory
         * allocated for the queue and put a new message in it
         * @param message new message(&message)
         * @return calling queue with new message(&Queue)
         * */
        Queue &operator+=(const Message &message);

        /**
         * @brief operator [] : receive all messages from the chat in the queue
         * @detailed go through each message in the queue from its beginning
         * and check message chat, if it matches, push to a new queue
         * @param chatName chat name(&string)
         * @return new queue, where each message from given chat(Queue)
         * */
        Queue operator[](const std::string &chatName);

        /**
         * @brief operator << : output instance of Message
         * @detailed output each message of the queue, if queue is empty
         * print "queue is empty"
         * @param queue instance of Queue to be printed(&Queue)
         * @param c standard output(&ostream)
         * @return stream passed to the operator(&ostream)
         * */
        friend std::ostream &operator<<(std::ostream &c, const Queue &queue);

        /**
         * @brief operator >> : input instance of queue
         * @detailed enter queue size, then enter each message of queue
         * if an input error occurred, change the stream status
         * @param queue instance of Queue to be entered(&Queue)
         * @param s standard input (&istream)
         * @return stream passed to the operator(&istream)
         * */
        friend std::istream &operator>>(std::istream &s, Queue &queue);



        /**
         * @brief all adjacent messages from the same chat are merged
         * @details create a copy of queue, go through it and if we encounter
         * messages from the same chat, we merged them and add push result
         * to the calling queue
         * @return caller queue(&Queue)
         * */
        Queue &reorganizationQueue();

        /**
         * @brief ordering the queue by chat name and sending time
         * @detailed use sort from standard library
         * @return caller queue(&Queue)
         * */
        Queue &orderByChat();

        /**
         * @brief searches for a message that contains the word
         * @detailed go through each message in the queue from its
         * beginning and check whether next message contains the word
         * @param word the word you are looking for(&string)
         * @return found message(&Message)
         * @throw runtime_error if queue is empty and if there is
         * no messages with that word
         * */
        [[nodiscard]] Message &searchMessage(const std::string &word) const;

        /**
         * @brief check queue status, it can be empty or partially full
         * @return queue state(enum state)
         * */
        [[nodiscard]] state checkState() const;



        /**
         * @brief static method, print the queue status to the user
         * @param st queue status : empty/partially full(enum state)
         * @param c standard output(&ostream)
         * @return stream passed to the method(&ostream)
         * */
        static std::ostream &outputState(std::ostream &c, state st);
    };

} // kas

#endif //FINALLAB2_QUEUE_H
