#include <iostream>
#include "core/core.hpp"
#include "gjk/gjk.hpp"

int main(){
    CDP::Core core;
    
    core.run();
    std::cout << "Hello world" << std::endl;
    CDP::GJK new_gjk(2, 3);
    std::cout << "GJK values: " << new_gjk.a << " | " << new_gjk.b << "\n";
}