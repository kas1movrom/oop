//
// Created by romka on 18.09.2023.
//

#ifndef FINALLAB2_DIALOG_H
#define FINALLAB2_DIALOG_H

#include "../../../queuewithmessagesdir/include/Queue.h"

using namespace kas;
using namespace Mes;

namespace Dialog {

    /**
     * @detailed standard number input function
     * @param min minimum number value(int)
     * @param max maximum number value(int)
     * @returns entered number(int)
     * @throw runtime_error if there was input error
     * */
    int getNum(int min = 1, int max = 9);

    /**
     * @detailed send array of messages, print in
     * @param arrayOfMsgs array of messages(string *)
     * @param size size of messages array(int)
     * */
    void printMenu(std::string arrayOfMsgs[], int size);

    /**
     * @detailed message is entered from the standard stream
     * if no errors occurred, the message is pushed into queue
     * @param queue passed queue(&Queue)
     * @throw runtime_error if there was input error
     * */
    void push(Queue &queue);

    /**
     * @detailed remove the message from the queue, if no errors
     * occurred we print a message, otherwise we print a message
     * about caught exception
     * @param queue passed queue(&Queue)
     * */
    void pop(Queue &queue);

    /**
     * @detailed check the queue status and print it
     * @param queue passed queue(&Queue)
     * */
    void check(Queue &queue);

    /**
     * @detailed reorganize the queue, group message in it
     * @param queue passed queue(&Queue)
     * */
    void reorganization(Queue &queue);

    /**
     * @detailed get a new queue contains messages from the
     * entered chat and print it
     * @param queue passed queue(&Queue)
     * @throw runtime_error if there was input error
     * */
    void getMessagesFromChat(Queue &queue);

    /**
     * @detailed enter a word and print the first message in the
     * queue containing this word. if there is no such word or
     * the queue is empty, catch an exception
     * @param queue passed queue(&Queue)
     * @throw runtime_error if there was input error
     * */
    void findMessage(Queue &queue);

    /**
     * @detailed sorts the queue by chat name and time
     * @param queue passed queue(&Queue)
     * */
    void sort(Queue &queue);

    /**
     * @detailed print queue
     * @param queue passed queue(&Queue)
     * */
    void output(Queue &queue);

    /**
     * @detailed print menu with input selection, you
     * can select several options either create an empty queue,
     * or queue from an array of messages with specified number
     * of elements, or enter the queue into standard input stream
     * @param size size of messages array(int)
     * @param array array of messages(Message*)
     * @returns queue
     * @throw runtime_error if there was input error
     * */
    Queue create(int size, Message array[]);
}

#endif //FINALLAB2_DIALOG_H
