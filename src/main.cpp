#include <iostream>
#include "core/core.hpp"
#include "gjk/gjk.hpp"
#include <SFML/Graphics.hpp>

int main(){
    sf::Color(26);
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WORK!");


    // while(window.isOpen()){
    //     sf::Event event;

    //     while(window.pollEvent(event)){
    //         if(event.type == sf::Event::Closed) window.close();
    //     }

    //     window.clear();

    //     window.display();       
    // }
    // CDP::run();
    // std::cout << "Hello world" << std::endl;
    // CDP::GJK new_gjk(2, 3);
    // std::cout << "GJK values: " << new_gjk.a << " | " << new_gjk.b << "\n";
}