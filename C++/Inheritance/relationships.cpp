// Inheritance showcase

#include <iostream>
#include "supersub.hpp"

/* Function Declarations */
void call_eat(Animal* animal);
void call_sleep(Animal* animal);

int main() {
	std::cout << "     Class relationship diagram \n";
	std::cout << "             *---------*\n";
	std::cout << "             | Animal  |\n";
	std::cout << "             *---------*______________\n";
	std::cout << "                |     |               |\n";
	std::cout << "*---------* *------* *------*      *-----------*\n";
	std::cout << "| Playful | | +Cat | | #Dog |      | -Squirrel |\n";
	std::cout << "*---------* *------* *------*__    *-----------*\n";
	std::cout << "        |    |    |   |        |\n";
	std::cout << "   *----------* *----------* *--------*\n";
	std::cout << "   | +Kitten+ | | +CatDog+ | | +Puppy |\n";
	std::cout << "   *----------* *----------* *--------*\n\n";
	std::cout << "+: public #: protected -: private\n\n\n\n";
	
	std::cout << "Polymorphism in action\n----------------------\nWe are creating an Animal (base class) object and a Cat (public Animal) object.\n";
	
	// See supersub.hpp for implementation details and some notes
	Animal* animal = new Animal;
	Cat* cat = new Cat;

	std::cout << "Calling animal.eat() directly: ";
	animal->eat();

	std::cout << "Calling cat.eat() directly: ";
	cat->eat();

	std::cout << "Calling animal.eat() via non-class function call_eat(Animal* animal): ";
	call_eat(animal);

	// This calls the parent class's eat() function!
	std::cout << "Calling cat.eat() via non-class function call_eat(Animal* animal): ";
	call_eat(cat);
	// Solution 1: overload call_eat for every subclass we might want to call the eat() function with
	// Solution 2: make the parent class's eat function virtual
		// Note: virtual calls are much more expensive than regular function calls

	// Which method will be called? It gets decided at compile time.
	// Not virtual - early binding - function to call is based on the type of the pointer
	//     Virtual - late binding  - function to call is based on the type of the pointed-to object (what it originally was constructed as).

	std::cout << "\nTrying again with a different function where the parent class function is virtual.\n";

	std::cout << "Calling animal.sleep() directly: ";
	animal->sleep();

	std::cout << "Calling cat.sleep() directly: ";
	cat->sleep();

	std::cout << "Calling animal.sleep() via non-class function call_sleep(Animal* animal): ";
	call_sleep(animal);

	std::cout << "Calling cat.sleep() via non-class function call_sleep(Animal* animal): ";
	call_sleep(cat);

	std::cout << "\n\nProtected (Dog) and Private (Squirrel) inheritance in action\n------------------------------------------------------------\n";

	Dog* dog = new Dog;
	Squirrel* squirrel = new Squirrel;

	//dog->eat();
	//dog->sleep();
	std::cout << "Calling dog.eat() or dog.sleep() directly: COMPILER ERROR - function is inaccessible.\n";
	// We can't do this because Dog's eat() and sleep() are protected, they can only be accessed from within Dog or a class derived from Dog
	
	// We can do this though
	std::cout << "Calling dog.eat_and_sleep() directly: ";
	dog->eat_and_sleep();

	//squirrel->eat();
	//squirrel->sleep();
	std::cout << "Calling squirrel.eat() or squirrel.sleep() directly: COMPILER ERROR - function is inaccessible.\n";
	// We can't do this because Squirrel's eat() and sleep() are private, they can only be accessed from within Squirrel, even though eat() and sleep() are public in Animal

	// We can do this though
	std::cout << "Calling squirrel.eat_and_sleep() directly: ";
	squirrel->eat_and_sleep();

	std::cout << "\n\nMulti-level inheritance in action\n---------------------------------\n";

	Puppy* puppy = new Puppy;

	//puppy->eat();
	//puppy->sleep();
	std::cout << "Calling puppy.eat() or puppy.sleep() directly: COMPILER ERROR - function is inaccessible.\n";
	// We can't do this because Puppy's eat() and sleep() are protected via Dog, they can only be accessed from within Puppy

	// We can do this though
	std::cout << "Calling puppy.eat_and_sleep() directly: ";
	puppy->eat_and_sleep();

	std::cout << "\n\nThe Diamond Problem: Multiple Inheritance in action\n---------------------------------------------------\n";

	CatDog* catdog = new CatDog;

	//catdog->Dog::eat();
	//catdog->Dog::sleep();
	std::cout << "Calling catdog.Dog::eat() or catdog.Dog::sleep() directly: COMPILER ERROR - function is inaccessible.\n";
	// We can't do this because CatDog's eat() and sleep() from Dog are protected, they can only be accessed from within CatDog

	// We can do this because CatDog's eat() and sleep() from Cat are public
	std::cout << "Calling catdog.Cat::eat() directly: ";
	catdog->Cat::eat();

	std::cout << "Calling catdog.Cat::sleep() directly: ";
	catdog->Cat::sleep();

	// And of course, we can call CatDog's own methods
	std::cout << "Calling catdog.eat() directly: ";
	catdog->eat();

	std::cout << "Calling catdog.sleep() directly: ";
	catdog->sleep();

	std::cout << "\n\nNo Diamond Problem: Multiple Inheritance in action\n--------------------------------------------------\n";

	Kitten* kitten = new Kitten;

	// We can call Kitten's own methods
	std::cout << "Calling kitten.eat() directly: ";
	kitten->eat();

	std::cout << "Calling kitten.play() directly: ";
	kitten->play();

	// We can also call methods from Cat via Kitten
	std::cout << "Calling kitten.Cat::eat() directly: ";
	kitten->Cat::eat();

	std::cout << "Calling kitten.Cat::sleep() directly: ";
	kitten->Cat::sleep();

	return 0;
}

void call_eat(Animal* animal) {
	animal->eat();
}

void call_sleep(Animal* animal) {
	animal->sleep();
}