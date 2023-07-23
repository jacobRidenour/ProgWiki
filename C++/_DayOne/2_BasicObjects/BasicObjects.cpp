#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

class Room
{          // no () after className
protected: // access specifier
    int width;
    int height;
    std::string roomName;
    std::string areaName;

public:
    // Constructors
    Room(int w, int h, std::string room, std::string area)
    {
        if (w >= 30)
            width = w;
        if (h >= 17)
            height = h;
        roomName = room;
        areaName = area;
    }

    Room(int w, int h)
    {
        if (w >= 30)
            width = w;
        if (h >= 17)
            height = h;
    }
    Room()
    {
        width = 17;
        height = 30;
    }
    // Modifiers
    void setWidth(int w) 
    {
        if (w >= 30)
            width = w;
    }
    void setHeight(int h)
    {
        if (h >= 17)
            height = h;
    }
    void setArea(std::string name)
    {
        areaName = name;
    }
    void setName(std::string name)
    {
        roomName = name;
    }
    // Accessors
    int getWidth() const //can check if a function is const
    {
        return width;
    }
    int getHeight() noexcept //tells you that the function doesn't throw an exception (can check, like const)
    {
        return height;
    }
    std::string getArea()
    {
        return areaName;
    }
    std::string getName()
    {
        return roomName;
    }

}; // end with ; like a struct in C

class Shape
{
protected:
    int sideLength;

public:
   // virtual double area() = 0; // virtual -> can be overridden in derived classes (but not required)
                               // virtual functions cannot be friends of another class
                               // for runtime polymorphism: access with pointer/reference of base class
    virtual int perimeter() = 0;
};
class Triangle : public Shape
{
private:
    int sideLength;

public:
    Triangle()
    {
        sideLength = -1;
    }
    Triangle(int l)
    {
        sideLength = l;
    }
    int perimeter() {
        return 3 * sideLength;
    }
};

int main()
{
    // using namespace std;

    // Example of basic objects & accessing/modifying them
    Room firstRoom(64, 48, "Landing Site", "Crateria");
    Room secondRoom(36, 44, "Parlor", "Crateria");
    std::cout << firstRoom.getName() << " + " << secondRoom.getName() << std::endl;

    // Example of inheritance in action (Shape superclass: subclasses triangle, square, pentagon)
    int size = 4;
    // Shape is abstract type; we cannot instantiate an object of type Shape
    Triangle t1;

    if (true) {
//        throw (exception) {
//            //do something; can call parent exceptions prn
//        }
    }

    return 0;
}