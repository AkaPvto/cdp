// This file will contain the core function of the program
#include "core.hpp"

#include <iostream>
#include <vector>


namespace CDP{

// Constructor of the class
Core::Core( std::string name, double const h, double const w ) : window{sf::VideoMode(w, h), name}, height{h}, width{w} {
    // window(sf::VideoMode(h, w), "Collisions");
}

// Run the main program
void Core::run(){
    sf::Color(26);


    sf::CircleShape shape_1(100.0f);
    shape_1.setFillColor(sf::Color(231,127,23));

    sf::ConvexShape shape_2;
    shape_2.setPointCount(3);
    shape_2.setPoint(0, sf::Vector2f(0, 0));
    shape_2.setPoint(1, sf::Vector2f(0, 100));
    shape_2.setPoint(2, sf::Vector2f(250, 50));
    shape_2.setOutlineColor(sf::Color::Red);
    shape_2.setOutlineThickness(5);
    shape_2.setPosition(200, 200);

    sf::ConvexShape shape_3;
    shape_3.setPointCount(3);
    shape_3.setPoint(0, sf::Vector2f(250, 50));
    shape_3.setPoint(1, sf::Vector2f(0, 0));
    shape_3.setPoint(2, sf::Vector2f(0, 100));
    shape_3.setOutlineColor(sf::Color::Blue);
    shape_3.setOutlineThickness(5);
    shape_3.setPosition(300, 600);

    shapes.emplace_back(&shape_2);
    shapes.emplace_back(&shape_1);
    shapes.emplace_back(&shape_3);
    
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
    
        window.clear();
        draw();
        window.display();       
    }
}

void Core::draw(){
    int sign = -1;
    for(sf::Shape* const s : shapes){
        int new_X = s->getPosition().x + 1*sign;
        if(new_X > width) new_X = 0;
        else if(new_X < 0) new_X = width;

        int new_Y = s->getPosition().y + 1*sign;
        if(new_Y > height) new_Y = 0;
        else if(new_Y < 0) new_Y = height;

        s->setPosition(new_X, new_Y);
        sign*=sign;
        window.draw(*s);
    }
}

} // namespace CDP