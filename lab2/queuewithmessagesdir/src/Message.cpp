//
// Created by romka on 18.09.2023.
//

#include "../include/Message.h"

namespace Mes {

    char *Message::getCharPointer(const std::string &str) {
        char *charArr = new char[str.length() + 1];
        strcpy_s(charArr, str.length() + 1, str.c_str());
        return charArr;
    }

    Message::Message(long long time) {
        if (time < 0LL || time > (std::numeric_limits<long long>::max() - Message::timeUnix))
            throw std::invalid_argument("Inavlid time\n");

        timeMessage = time;
    }

    Message::Message(const std::string& text, const std::string& chatName, long long timeMes) {
        textMessage = {text};
        chatNameMessage = {chatName};

        if (timeMes < 0 || timeMes > (std::numeric_limits<long long>::max() - Message::timeUnix))
            throw std::invalid_argument("Invalid time\n");

        timeMessage = timeMes;
    }

    Message &Message::setChatName(const std::string& chatName) {
        chatNameMessage = {chatName};
        return *this;
    }

    Message &Message::setText(const std::string& text) {
        textMessage = {text};
        return *this;
    }

    Message &Message::setTime(long long time) {
        if (time < 0 || time > (std::numeric_limits<long long>::max() - Message::timeUnix))
            throw std::invalid_argument("Invalid time!\n");

        timeMessage = time;
        return *this;
    }

    std::string Message::getChatName() const {
        return chatNameMessage;
    }

    std::string Message::getText() const {
        return textMessage;
    }

    long long Message::getTime() const {
        return timeMessage;
    }

    Message Message::operator+(const Message &message) const {
        if (chatNameMessage != message.chatNameMessage)
            throw std::invalid_argument("Messages from different chats!\n");

        std::string tmp;
        long long maxTime;

        if (timeMessage > message.timeMessage) {
            tmp = message.textMessage;
            tmp.append(textMessage);

            maxTime = timeMessage;
        }
        else {
            tmp = textMessage;
            tmp.append(message.textMessage);

            maxTime = message.timeMessage;
        }
        return {tmp, chatNameMessage, maxTime};
    }

    bool Message::operator==(const Message &message) const {
        return (chatNameMessage == message.chatNameMessage) &&
            (timeMessage == message.timeMessage);
    }

    bool Message::operator<(const Message &message) const {
        int chatComp = chatNameMessage.compare(message.chatNameMessage);
        return (chatComp < 0 || (chatComp == 0 && timeMessage - message.timeMessage < 0));
    }

    bool Message::find(const std::string &word) const {
        char *message = getCharPointer(textMessage), *src = getCharPointer(word), *next_token;
        char *token = strtok_s(message, " ", &next_token);

        while (token != nullptr) {
            if (strcmp(token, src) == 0) {
                delete[] message;
                delete[] src;

                return true;
            }
            token = strtok_s(nullptr, " ", &next_token);
        }
        delete[] message;
        delete[] src;

        return false;
    }

    std::ostream &operator<<(std::ostream &c, const Message &message) {
        char buffer[32];
        time_t tot = message.getTime();
        asctime_s(buffer, 32, localtime(&tot));
        std::string str_time = buffer;

        c << message.textMessage << std::endl << message.chatNameMessage << std::endl
            << str_time << std::endl;
        return c;
    }

    std::istream &operator>>(std::istream &s, Message &message) {
        s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(s, message.textMessage);
        std::getline(s, message.chatNameMessage);

        s >> message.timeMessage;
        if (s.good()) {
            if (message.timeMessage < 0 || message.timeMessage >
                    (std::numeric_limits<long long>::max() - Message::timeUnix)) {
                s.setstate(std::ios::failbit);
            }
        }
        return s;
    }
} // Mes