//
// Created by romka on 22.09.2023.
//
#define CATCH_CONFIG_MAIN

#include "catch2.hpp"

#include "../queuewithmessagesdir/include/Message.h"
#include "../queuewithmessagesdir/include/Queue.h"

using namespace kas;

TEST_CASE("Message Constructors") {
    SECTION("Default Constructor") {
        Message message;
        REQUIRE(message.getTime() == 0LL);
        Message message1{99999LL};
        REQUIRE(message1.getTime() == 99999LL);
    }

    SECTION("Initializing Constructor") {
        Message message{"kasimov", "oop", 9999LL};
        REQUIRE(message.getTime() == 9999LL);
        REQUIRE(message.getChatName() == "oop");
        REQUIRE(message.getText() == "kasimov");
        Message message1{"kezin", "aisd"};
        REQUIRE(message1.getTime() == time(nullptr));
    }

    SECTION("Test exception") {
        REQUIRE_THROWS(Message{-100LL});
//        REQUIRE_THROWS(Message{std::numeric_limits<long long>::max() - 170208002LL});
        REQUIRE_THROWS(Message{"roman", "vk", -100LL});
    }
}

TEST_CASE("Message setters") {
    SECTION("Set time") {
        Message message;
        message.setTime(9999L);
        REQUIRE(message.getTime() == 9999L);
        srand(time(nullptr));
        int a = rand();
        a = (a < 0) ? -a : a;
        REQUIRE_NOTHROW(message.setTime(a));
    }

    SECTION("Set text of message") {
        Message message;
        message.setText("kasimov");
        REQUIRE(message.getText() == "kasimov");
    }

    SECTION("Set chat name") {
        Message message;
        message.setChatName("oop");
        REQUIRE(message.getChatName() == "oop");
    }

    SECTION("Test exception") {
        Message message;
        REQUIRE_THROWS(message.setTime(-100LL));
    }
}

TEST_CASE("Message methods and operators") {
    SECTION("Find test") {
        Message message("kasimov roman elmirovich the best football player", "champions league");
        REQUIRE(message.find("best"));
        REQUIRE_FALSE(message.find("romik"));
    }

    SECTION("Operator <") {
        Message message("kasimov", "oop");
        Message message1("kasimov", "aisd");
        Message message2("kasimov", "oop", 7LL);
        REQUIRE(message1 < message);
        REQUIRE(message2 < message);
    }

    SECTION("Operator ==") {
        Message message("kasimov", "oop");
        Message message1("kezin", "oop");
        Message messgae2("kezin", "oop", 8LL);
        REQUIRE(message1 == message);
        REQUIRE_FALSE(messgae2 == message1);
    }

    SECTION("Operator +") {
        Message message("kasimov ", "oop");
        Message message1("roman", "oop", 9LL);
        Message message2("kezin", "oop", 8LL);
        Message mergedMessage = message + message1;
        REQUIRE(mergedMessage.getText() == "romankasimov ");
        REQUIRE(mergedMessage.getTime() == time(nullptr));
        REQUIRE((message2 + message1).getText() == "kezinroman");
    }

    SECTION("Test exception") {
        Message message("kasimov", "oop");
        Message message1("roman", "aisd");
        REQUIRE_THROWS(message + message1);
    }
}

TEST_CASE("Queue operators") {
    SECTION("Operator []") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL), Message("solonenko", "aisd"),
                           Message("zaivyi", "oop", 991991111LL)};
        Queue queue {5, array};
        Queue queueResult = queue["aisd"];
        REQUIRE(queueResult.checkState() == state::PART_FULL);
        REQUIRE((--queueResult).getText() == "kezin");
        REQUIRE((--queue).getText() == "kasimov");
        REQUIRE((--(queueResult.reorganizationQueue())).getText() == "kurkosolonenko");
    }

    SECTION("Operator +=") {
        Queue queue;
        REQUIRE(queue.checkState() == state::EMPTY);
        queue += Message("Kasimov", "oop");
        REQUIRE((--queue).getText() == "Kasimov");
        REQUIRE(queue.checkState() == state::EMPTY);
    }

    SECTION("Operator --") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        Queue queue {3, array};
        queue.orderByChat();
        REQUIRE((--queue).getText() == "kurko");
        REQUIRE((--queue).getText() == "kezin");
        REQUIRE((--queue).getTime() == 21LL);
        REQUIRE_THROWS(--queue);
        REQUIRE_THROWS(queue.searchMessage("kasimov"));
    }

    SECTION("Operator = copy") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        Queue queue {3, array};
        Queue queueCopy = queue;
        REQUIRE((--queueCopy).getText() == (--queue).getText());
    }

    SECTION("Operator = copy2") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        Queue queue {3, array};
        Queue queueSwap {2, array};
        queue = queueSwap;
        REQUIRE((--queue).getText() == "kasimov");
        REQUIRE((--queue).getChatName() == "aisd");
        REQUIRE_THROWS(--queue);
    }

    SECTION("Operator = move") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        Queue queue {3, array};
        Queue queueSwap {2, array};
        queue = std::move(queueSwap);
        REQUIRE((--queue).getText() == "kasimov");
        REQUIRE((--queue).getChatName() == "aisd");
        REQUIRE((--((queueSwap.reorganizationQueue())["aisd"])).getText() == "kurkokezin");
        REQUIRE_THROWS(--queue);
    }

    SECTION("Queue move constructor") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        Queue queue {1, array};
        Queue queue1 {std::move(queue)};
        REQUIRE((--queue1).getTime() == 21LL);
        std::stringstream out;
        out << queue1;
        REQUIRE(out.str() == "Queue is empty\n");
    }
}

TEST_CASE("Queue methods") {
    SECTION("Method find and reorganization") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL), Message("solonenko", "aisd"),
                           Message("zaivyi", "aisd", 991991111LL), Message("krotov", "aisd"),
                           Message("klimo", "inf", 6LL)};
        Queue queue {7, array};
        queue += Message("Subbot", "inf");
        REQUIRE(queue.searchMessage("kurko").getChatName() == "aisd");
        REQUIRE((--queue).getText() == "kasimov");
        REQUIRE_THROWS(queue.searchMessage("kostin"));
        queue.reorganizationQueue();
        REQUIRE((--queue).getChatName() == "aisd");
    }

    SECTION("Output state partially full") {
        Message array[] = {Message("kasimov", "oop", 21LL), Message("kezin", "aisd"),
                           Message("kurko", "aisd", 93939328LL)};
        std::stringstream out;
        Queue queue {1, array};
        Queue::outputState(out, queue.checkState());
        REQUIRE(out.str() == "Queue is partially full\n");
        REQUIRE((--queue).getTime() == 21LL);
    }

    SECTION("Output state empty") {
        Queue queue;
        std::stringstream out;
        Queue::outputState(out, queue.checkState());
        REQUIRE(out.str() == "Queue is empty\n");
    }
}