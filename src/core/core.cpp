// This file will contain the core function of the program
#include "core.hpp"

#include <iostream>
#include <vector>
#include <array>

#include "algorithm/aabb.hpp"
#include "algorithm/gjk.hpp"
#include "algorithm/sat.hpp"

// #include "algorithm"
// #include "algorithm"


namespace CDP{

// Constructor of the class
Core::Core( std::string name, double const h, double const w ) : window{sf::VideoMode(w, h), name}, height{h}, width{w}, initialize_types{&Core::AABB_init, &Core::SAT_init, &Core::GJK_init} {
    // window(sf::VideoMode(h, w), "Collisions");
}
void Core::mouse_movement(){
    if(dynamic_cast<AABB*>(algth) == nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        delete_shapes();
        initialize(0);
    }

    if(dynamic_cast<SAT*>(algth) == nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        delete_shapes();
        initialize(1);
    }

    if(dynamic_cast<GJK*>(algth) == nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
        delete_shapes();
        initialize(2);
    }

    sf::Vector2i localPos = sf::Mouse::getPosition(window);
    auto point = shapes[0]->getPoint(2);
    shapes[0]->setPosition(sf::Vector2f(localPos.x - point.x/2, localPos.y - point.y/2));
}

// Run the main program
void Core::run(){
    sf::Color(26);

    initialize(0);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
        mouse_movement();
        check_collision();
        window.clear();
        draw();
        window.display();       
    }
    delete_shapes();
}

void Core::check_collision(){
    Polygon box1{};
    Polygon box2{};
    box1.fill(shapes[0]);
    box2.fill(shapes[1]);
    
    if(algth != nullptr){
        if(algth->colide(box1, box2)){
            shapes[0]->setFillColor(sf::Color::Red);
            shapes[1]->setFillColor(sf::Color::Red);
        }
        else{
            shapes[0]->setFillColor(sf::Color::Green);
            shapes[1]->setFillColor(sf::Color::Blue);
        }
    }
}

void Core::draw(){
    // int sign = -1;
    for(sf::Shape* const s : shapes){
        // int new_X = s->getPosition().x + 1*sign;
        // if(new_X > width) new_X = 0;
        // else if(new_X < 0) new_X = width;

        // int new_Y = s->getPosition().y + 1*sign;
        // if(new_Y > height) new_Y = 0;
        // else if(new_Y < 0) new_Y = height;

        // s->setPosition(new_X, new_Y);
        // sign*=sign;

        window.draw(*s);
    }
}

void Core::delete_shapes(){
    for(sf::Shape* const s : shapes){
       delete(s);
    }
    shapes.clear();

    if(algth != nullptr){ delete(algth); algth = nullptr;}
}

// Uses the initialization function indicated by param from the static array
void Core::initialize(uint32_t const type){
    // (this->*initialize_types[type])();
    switch(type){
        case 0:
            AABB_init();
            break;
        case 1:
            SAT_init();
            break;
        case 2:
            GJK_init();
            break;
        default:
            break;
    }
}

// ### Initialization functions ###

// Default initialization of AABB case scenario
void Core::AABB_init(){
    sf::ConvexShape* shape_1 = new sf::ConvexShape();
    shape_1->setPointCount(4);
    shape_1->setPoint(0, sf::Vector2f(0,   0));
    shape_1->setPoint(1, sf::Vector2f(200, 0));
    shape_1->setPoint(2, sf::Vector2f(200, 330));
    shape_1->setPoint(3, sf::Vector2f(0,   330));
    shape_1->setFillColor(sf::Color::Green);
    shape_1->setOutlineColor(sf::Color::White);
    shape_1->setOutlineThickness(5);
    shape_1->setPosition(300, 300);

    sf::ConvexShape* shape_2 = new sf::ConvexShape();
    shape_2->setPointCount(4);
    shape_2->setPoint(0, sf::Vector2f(0,   0));
    shape_2->setPoint(1, sf::Vector2f(300, 0));
    shape_2->setPoint(2, sf::Vector2f(300, 200));
    shape_2->setPoint(3, sf::Vector2f(0,   200));
    shape_2->setFillColor(sf::Color::Blue);
    shape_2->setOutlineColor(sf::Color::White);
    shape_2->setOutlineThickness(5);
    shape_2->setPosition(350, 200);

    shapes.emplace_back(shape_1);
    shapes.emplace_back(shape_2);

    algth = new AABB();
}

// Default initialization of SAT case scenario
void Core::SAT_init(){
    sf::ConvexShape* shape_1 = new sf::ConvexShape();
    shape_1->setPointCount(5);
    shape_1->setPoint(0, sf::Vector2f(200, 50));
    shape_1->setPoint(1, sf::Vector2f(340, 155));
    shape_1->setPoint(2, sf::Vector2f(300, 350));
    shape_1->setPoint(3, sf::Vector2f(100,   350));
    shape_1->setPoint(4, sf::Vector2f(50,  150));
    shape_1->setFillColor(sf::Color::Green);
    shape_1->setOutlineColor(sf::Color::White);
    shape_1->setOutlineThickness(5);
    shape_1->setPosition(300, 300);

    sf::ConvexShape* shape_2 = new sf::ConvexShape();
    shape_2->setPointCount(6);
    shape_2->setPoint(0, sf::Vector2f(150, 50));
    shape_2->setPoint(1, sf::Vector2f(300, 50));
    shape_2->setPoint(2, sf::Vector2f(400, 200));
    shape_2->setPoint(3, sf::Vector2f(300, 350));
    shape_2->setPoint(4, sf::Vector2f(150, 350));
    shape_2->setPoint(5, sf::Vector2f(50,  200));
    shape_2->setFillColor(sf::Color::Blue);
    shape_2->setOutlineColor(sf::Color::White);
    shape_2->setOutlineThickness(5);
    shape_2->setPosition(350, 200);

    shapes.emplace_back(shape_1);
    shapes.emplace_back(shape_2);

    algth = new SAT();
}

// Default initialization of GJK case scenario
void Core::GJK_init(){
    sf::ConvexShape* shape_1 = new sf::ConvexShape();
    shape_1->setPointCount(5);
    shape_1->setPoint(0, sf::Vector2f(50,   0));
    shape_1->setPoint(1, sf::Vector2f(300, 0));
    shape_1->setPoint(2, sf::Vector2f(300, 200));
    shape_1->setPoint(3, sf::Vector2f(50,   200));
    shape_1->setPoint(4, sf::Vector2f(0,   100));
    
    shape_1->setFillColor(sf::Color::Green);
    shape_1->setOutlineColor(sf::Color::White);
    shape_1->setOutlineThickness(5);
    shape_1->setPosition(300, 300);

    sf::ConvexShape* shape_2 = new sf::ConvexShape();
    shape_2->setPointCount(4);
    shape_2->setPoint(0, sf::Vector2f(0,   0));
    shape_2->setPoint(1, sf::Vector2f(200, 0));
    shape_2->setPoint(2, sf::Vector2f(200, 330));
    shape_2->setPoint(3, sf::Vector2f(0,   330));
    shape_2->setFillColor(sf::Color::Blue);
    shape_2->setOutlineColor(sf::Color::White);
    shape_2->setOutlineThickness(5);
    shape_2->setPosition(350, 200);

    shapes.emplace_back(shape_1);
    shapes.emplace_back(shape_2);

    algth = new GJK();
}


} // namespace CDP