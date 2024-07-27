/* Includes */
#include "readRoomFile.hpp"
#include <iostream>

#define test

int main() {
    // Read Rooms from .txt file
    std::vector<Room> rooms = readRoomsFile("rooms.txt", false);

    // Verify text file contents were read correctly
    #ifdef test
    for (const Room& room : rooms) {
        std::cout << room.getArea() << " " << room.getNumber() << " " << room.getName() << "\n";
    }
    #endif /* test */

    // Write Rooms to a new .txt file and a .dat file
    writeRoomsToFile(rooms, "updated_rooms.txt", false);
    writeRoomsToFile(rooms, "updated_rooms.dat");
    
    // Read Rooms from binary file
    rooms = readRoomsFile("updated_rooms.dat");

     
    // Verify serialization & deserialization results
    for (const Room& room : rooms) {
        std::cout << room.getArea() << " " << room.getNumber() << " " << room.getName() << "\n";
    }

    return 0;
}

