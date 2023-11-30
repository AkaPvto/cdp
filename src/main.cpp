#include <iostream>
#include "core/core.hpp"
#include "sys/render.hpp"
int main(){
    CDP::Core core;
    // CDP::RenderSystem renderSys;
    // renderSys.init();
    // while(renderSys.isOpen()){
    //     renderSys.update();
    // }
    // renderSys.end();
    core.run();
    std::cout << "Hello world" << std::endl;
}