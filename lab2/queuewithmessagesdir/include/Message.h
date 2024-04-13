
#ifndef FINALLAB2_MESSAGE_H
#define FINALLAB2_MESSAGE_H

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <cstring>


/**
 * @namespace Mes
 * */
namespace Mes {

    /**
     * @brief class describe the text message
     * @detailed each instance of this class contains the text of the message,
     * the chat in which it was sent and the time it was sent, starting from
     * 00:00 January 3, 1970
     * */
    class Message {
    private:
        std::string textMessage;
        std::string chatNameMessage;

        long long timeMessage;

        static const long long timeUnix = 170208000LL;

        static char *getCharPointer(const std::string &str);

    public:

        /**
         * @brief operator << : output instance of Message
         * @detailed output time in the format hh:mm:ss day, month, year
         * @param message instance of Message to be printed(&Message)
         * @param c standard output(&ostream)
         * @return stream passed to the operator(&ostream)
         * */
        friend std::ostream &operator<<(std::ostream &c, const Message &message);

        /**
         * @brief operator >> : input instance of Message
         * @detailed enter instance fields, if a negative time was entered or
         * an input error occurred, change the stream state
         * @param message instance of Message to be entered(&Message)
         * @param s standard input(&istream)
         * @return stream passed to the operator(&istream)
         * */
        friend std::istream &operator>>(std::istream &s, Message &message);

        /**
         * @brief operator +
         * @detailed in the returned message the message text with the earlier
         * sending time will be first, the result time will be the later time
         * @param message instance of Message(&Message), which you want to
         * merge with caller
         * @return new instance of Message, result of merge two messages(Message)
         * @throw invalid_argument if the messages from different chats
         * */
        Message operator + (const Message &message) const;

        /**
         * @brief operator == : compares message
         * @param message instance of Message, which we want
         * to compare with caller(&Message)
         * @return true/false, compare is made by name of the chat and
         * in case of equality by time(bool)
         * */
        bool operator == (const Message &message) const;

        /**
         * @brief operator < : compares message
         * @param message instance of Message, which we want
         * to compare with the caller(&Message)
         * @return true/false, compare is made by name of the chat and
         * in case of equality by time(bool)
         * */
        bool operator < (const Message &message) const;



        /**
         * @brief constructor
         * @param text text of the message(&string)
         * @param chatName name of the chat in which the message sent(&string)
         * @param timeMes time the message was sent(long long), by default
         * this is the current time
         * @return instance of Message(Message)
         * @throw invalid_argument if time is less than zero
         * */
        Message(const std::string &text, const std::string &chatName, long long timeMes = time(nullptr));

        /**
         * @brief default constructor
         * @param time time the message was sent(long long), by default
         * this is the 00:00 January 3, 1970
         * @return instance of Message(Message)
         * @throw invalid_argument if time is less than zero
         * */
        explicit Message(long long time = 0LL);



        /**
         * @brief time setter
         * @param time time the message was sent(long long)
         * @return reference to the current instance(&Message)
         * @throw invalid_argument if time is less than zero
         * */
        Message &setTime(long long time);

        /**
         * @brief text setter
         * @param text text of the message(&string)
         * @return reference to the current instance(&Message)
         * */
        Message &setText(const std::string &text);

        /**
         * @brief name of the chat setter
         * @param chatName name of the chat(&string)
         * @return refernce to the current instance(&Message)
         * */
        Message &setChatName(const std::string& chatName);


        /**
         * @brief time getter
         * @return message time(long long)
         * */
        [[nodiscard]] long long getTime() const;

        /**
         * @brief text getter
         * @return text of the message(string)
         * */
        [[nodiscard]] std::string getText() const;

        /**
         * @brief name of the chat getter
         * @return name of the chat(string)
         * */
        [[nodiscard]] std::string getChatName() const;



        /**
         * @detailed the message text broken into words until it meets
         * the one you were looking for
         * @param word the word you are looking for(&string)
         * @return returns true if the word in the message is found
         * and false if not(bool)
         * */
        [[nodiscard]] bool find(const std::string &word) const;
    };

} // Mes

#endif //FINALLAB2_MESSAGE_H
