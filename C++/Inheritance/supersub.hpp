#ifndef SUPERSUB_HPP
#define SUPERSUB_HPP

#include <iostream>

using string = std::string;

/* General syntax */
// class derived-class: access-specifier base-classA, access-specifier base-classB, ...

// Access specifiers: public, protected, private; public inheritance is most common

// What can a derived class access? -> All non-private members of its base class (public and protected)
	// Public inheritance - public/protected members of base class become public/protected members of derived class
		// Private members can only be accessed through public/protected function calls that access/modify private members
	// Protected inheritance - public/protected members of base class BOTH become protected members of derived class
	// Private inheritance - public/protected members of base class BOTH become private members of derived class
// Private members can only be accessed within that class.

// What does a derived class inherit? Everything except:
	// Copy constructors, constructors, destructors
	// Overloaded operators
	// Friend functions of base classes

class Animal {
public:
	void eat() { std::cout << "I'm eating a generic food.\n"; }
	virtual void sleep() { std::cout << "I am taking a generic snooze.\n"; }
};

/*
 * Public Inheritance
 */
// All of Animal's public/protected things are public/protected here.
class Cat : public Animal {
public:
	void eat() { std::cout << "I'm eating a rat.\n"; }
	void sleep() { std::cout << "I'm taking a cat nap.\n"; }
};

/*
 * Protected Inheritance
 */
// All of Animal's public/protected things are protected here.
class Dog : protected Animal {
public:
	void bark() { std::cout << "Woof!\n"; }
	// Dog can call the Animal class's methods inside its own methods
	void eat() { 
		Animal::eat();
	}
	
	void sleep() {
		Animal::sleep();
	}

	void eat_and_sleep() {
		this->eat();
		this->sleep();
	}
};

/*
 * Private Inheritance
 */
// All of Animal's public/protected things are private here.
class Squirrel : private Animal {
public:
	void squeak() { std::cout << "Squeak!\n"; }
	// Squirrel can call the Animal class's methods inside its own methods
	void eat_and_sleep() {
		this->eat();
		this->sleep();
	}
};


/*
* Multi-level inheritance
*/
// All of Animal's public/protected things are protected in Dog, and thus accessible from Puppy's own methods, but not outside of the class.
class Puppy : public Dog {
public:
	void whine() { std::cout << "Whine!\n"; }
	// Puppy can call the Animal class's methods via Dog
	void eat_and_sleep() {
		this->eat();
		this->sleep();
	}
};

/*
* Multiple inheritance: Diamond Problem
*/
// This class has 2 (it could have more) base classes that share *another* base class. This creates ambiguity about which base class's method to use.
// To remove ths ambiguity, we specify a class as a virtual base class; derive classes always get the parts of the virtual base class directly from that class, and not from any other class.
class CatDog : public Cat, public Dog {
public:
	// This function will call the base classes' eat() functions
	void eat() {
		Cat::eat();
		Dog::eat();
	}

	void sleep() {
		Cat::sleep();
		Dog::sleep();
	}
};

/*
* Multiple inheritance: No Diamond Problem
*/
class Playful {
public:
	virtual void play() = 0; // pure virtual function
};

//Notice the use of the keyword override
class Kitten : public Cat, public Playful {
public:
	void play() override {
		std::cout << "I'm playing with a ball of yarn.\n";
	}

	// Kitten can also override Cat's methods
	void eat() {
		std::cout << "I'm eating kitten food.\n";
	}
};


#endif /* SUPERSUB_HPP */