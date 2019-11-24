#include <fstream>
#include "Network.h"
#include "definitions/addressbook.pb.h"

Network::Network() {

    tutorial::AddressBook address_book;
    auto person = address_book.add_people();
    person->set_name("Lol");

    const char* path = "/home/mel/Projects/VulkanLab/Engine/src/Network/store/person";
    std::fstream output(path, std::ios::out | std::ios::trunc | std::ios::binary);

    if (!address_book.SerializeToOstream(&output)) {
        std::cout << "Failed to write address book." << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();
}

Network::~Network() {

}
