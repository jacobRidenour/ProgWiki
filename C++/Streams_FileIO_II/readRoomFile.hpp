/* Includes */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/* Using & Typedefs */
using string = std::string;
using uint = unsigned int;

class Room {
private:
    string name;
    string area;
    uint number;

public:
    Room()
        : name("NONAME"), area("NONE"), number(1024) {}
    
    Room(const string& area, uint number, const string& name)
        : name(name), area(area), number(number) {}

    inline const string& getName() const { return name; }
    inline const string& getArea() const { return area; }
    inline uint getNumber() const { return number; }
    inline void setName(const string& newName) { name = newName; }
    inline void setArea(const string& newArea) { area = newArea; }
    inline void setNumber(uint newNumber) { number = newNumber; }

    void serialize(std::ofstream& outFile) const {
        outFile.write(reinterpret_cast<const char*>(&number), sizeof(uint));
        size_t areaLength = area.length();
        outFile.write(reinterpret_cast<const char*>(&areaLength), sizeof(size_t));
        outFile.write(area.c_str(), areaLength + 1);
        size_t nameLength = name.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
        outFile.write(name.c_str(), nameLength + 1);
    }

    bool deserialize(std::ifstream& inFile) {
        if (!inFile.read(reinterpret_cast<char*>(&number), sizeof(uint))) {
            return false; // Return false if unable to read number
        }

        size_t areaLength;
        if (!inFile.read(reinterpret_cast<char*>(&areaLength), sizeof(size_t))) {
            return false; 
        }
        area.resize(areaLength + 1); // Include null-terminator
        if (!inFile.read(&area[0], areaLength + 1)) {
            return false;
        }

        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t))) {
            return false;
        }
        name.resize(nameLength + 1);
        if (!inFile.read(&name[0], nameLength + 1)) {
            return false; 
        }
    }
};

// Read room list from .txt file
// Format:
// <AreaName> <RoomNumber> <RoomName>
std::vector<Room> readRoomsFile(const string& filename, bool binary=true) {
    std::vector<Room> rooms;

    if (!binary) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << "\n";
            return std::vector<Room>();
        }

        string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            string area, name;
            uint number;
            if (iss >> area >> number) {
                std::getline(iss, name); // Read the Room Name directly
                rooms.emplace_back(area, number, name);
            }
            else {
                std::cerr << "Error: Invalid format in line: " << line << "\n";
            }
        }
        return rooms;

    }
    else {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << "\n";
            return std::vector<Room>();
        }

        std::vector<Room> rooms;
        Room room;
        while (!file.eof()) {
            room.deserialize(file);
            if (!file.eof()) { // Avoid adding an extra Room if we reach the end of the file
                rooms.push_back(room);
            }
        }
        std::cout << rooms.size();
        return rooms;
    }
}

void addRoom(std::vector<Room>& rooms, const Room& room) {
    rooms.push_back(room);
}

void deleteRoom(std::vector<Room>& rooms, const Room& roomToDelete) {
    rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
        [&roomToDelete](const Room& room) {
            return room.getArea() == roomToDelete.getArea()
                && room.getNumber() == roomToDelete.getNumber();
        }),
        rooms.end());
}

void modifyRoom(std::vector<Room>& rooms, const Room& roomToModify) {
    for (Room& room : rooms) {
        if (room.getArea() == roomToModify.getArea() && room.getNumber() == roomToModify.getNumber()) {
            room = roomToModify; // You can customize this based on how you want to modify the room.
            break;
        }
    }
}

// write contents of Rooms vector back to a file
void writeRoomsToFile(const std::vector<Room>& rooms, const string& filename, bool binary=true) {
    if (!binary) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not create file " << filename << "\n";
            return;
        }

        for (const Room& room : rooms) {
            file << room.getArea() << " " << room.getNumber() << " " << room.getName() << "\n";
        }
    }
    else {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not create file " << filename << "\n";
            return;
        }

        for (const Room& room : rooms) {
            room.serialize(file);
        }
    }
}



