// Export our module
export module cpp20_module;

// Includes
#include <iostream>

// Export all functions we want available to files that import this module
export void moduleDemo();

// Function declarations
void hiddenModuleDemo();

// Function definitions
void moduleDemo() {
    hiddenModuleDemo();
}

// This function is not exported, but it is still accessible outside the module because
// our exported function, moduleDemo(), calls it.
void hiddenModuleDemo() {
    std::cout << "\nThis function is defined in cpp20_module.cppm" << std::endl;
}


/************************************************************************************************/
// Why modules instead of header files?                                                         //
//                                                                                              //
// -> Improved compilation performance                                                          //
//  -> With header files, the compiler must process the entire content of the header            //
//     *every time* they are included, which leads to redundant compilation.                    //
//  -> Modules allow for more efficient and faster compilation by enabling separate             //
//     compilation units, where module interfaces are compiled once and used by multiple        //
//     translation units                                                                        //
//                                                                                              //
// -> Better encapsulation and information hiding mechanisms                                    //
//  -> With header files, all implementation details are exposed to anyone including            //
//     that header, which can lead to unnecessary dependencies, potential clashes               //
//  -> Modules let you selectively export *only* the necessary interfaces, providing            //
//     a cleaner separation between the interface and implementation                            //
//                                                                                              //
// -> Name conflict resolution                                                                  //
//  -> Headers can lead to name conflicts when different headers define entities with the       //
//     same name, which means extra effort to manage include guards & naming conventions        //
//  -> Modules introduce a module scope, where entities in a module are effectively isolated    //
//     from other modules, reducing the chances of name clashes                                 //
//                                                                                              //
// -> Improved dependency management                                                            //
//  -> With header files, their inclusion can lead to transitive dependencies and unnecessary   //
//     compilation dependencies.                                                                //
//  -> Modules allow a more fine-grained control over dependencies by explicitly importing      //
//     and exporting, reducing the coupling between components                                  //
//                                                                                              //
// -> Better tooling support (TBD)                                                              //
//  -> faster parsing, more accurate code completion, better static analysis                    //
//                                                                                              //
/************************************************************************************************/