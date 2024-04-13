#include "Dialog/include/Dialog/dialog.h"

using namespace kas;

typedef void (*dialogFunctions) (Queue &queue);

std::string msgsMenu[9] = {"1. push", "2. pop", "3. check",
                           "4. reorganization", "5. get messages from chat",
                           "6. find", "7. sort", "8. output", "9.exit"};

int main() {
    Message array[] = {Message("kasimov", "oop"),
                       Message("kezin", "aisd"),
                       Message("kurko", "oop", 92838LL)};

    dialogFunctions function[] =
            {
                    Dialog::push,
                    Dialog::pop,
                    Dialog::check,
                    Dialog::reorganization,
                    Dialog::getMessagesFromChat,
                    Dialog::findMessage,
                    Dialog::sort,
                    Dialog::output,
                    nullptr
            };

    Queue queue = Dialog::create(3, array);

    while (true) {
        Dialog::printMenu(msgsMenu, 9);

        try {
            int option = Dialog::getNum();
            if (option == 9)
                break;
            function[option - 1](queue);
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}


