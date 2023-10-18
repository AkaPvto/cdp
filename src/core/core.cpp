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

sf::Color const green(33, 184, 49,255);
sf::Color const blue(72, 191, 191, 255);
sf::Color const red(205,70,56,255);

namespace CDP{

// Constructor of the class
Core::Core( std::string name, double const h, double const w ) : 
window{sf::VideoMode(w, h), name}, height{h}, width{w}, initialize_types{&Core::AABB_init, &Core::SAT_init, &Core::GJK_init} {
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
    Vector2r center_diff = polygons.at(0).getCenter();
    polygons[0].setPosition(Vector2r{localPos.x - center_diff.x, localPos.y - center_diff.y});
    for(Polygon& p : polygons){
        p.update();
    }
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
    if(algth != nullptr){
        if(algth->colide(polygons[0], polygons[1])){
            polygons[0].setColor(red);
            polygons[1].setColor(red);
        }
        else{
            polygons[0].setColor(green);
            polygons[1].setColor(blue);
        }
    }
}

void Core::draw(){
    // int sign = -1;
    for(Polygon const& s : polygons){
        // int new_X = s->getPosition().x + 1*sign;
        // if(new_X > width) new_X = 0;
        // else if(new_X < 0) new_X = width;

        // int new_Y = s->getPosition().y + 1*sign;
        // if(new_Y > height) new_Y = 0;
        // else if(new_Y < 0) new_Y = height;

        // s->setPosition(new_X, new_Y);
        // sign*=sign;

        window.draw(s.getShape());
    }
}

void Core::delete_shapes(){
    polygons.clear();

    if(algth != nullptr){ delete(algth); algth = nullptr;}
}

// Uses the initialization function indicated by param from the static array
void Core::initialize(uint32_t const type){
    (this->*initialize_types.at(type))();
}

// ### Initialization functions ###

// Default initialization of AABB case scenario
void Core::AABB_init(){
    std::vector<Vector2r> p1_vertices{{0,0}, {200,0}, {200,330},{0,330}};
    Polygon p1(p1_vertices, {300,300});
    p1.setColor(green);
    p1.setBorder(5);
    p1.setBorderColor(sf::Color::White);

    std::vector<Vector2r> p2_vertices{{0,0}, {300,0}, {300,200}, {0,200}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(blue);
    p2.setBorder(5);
    p2.setBorderColor(sf::Color::White);


    polygons.emplace_back(p1);
    polygons.emplace_back(p2);

    algth = new AABB();

    // for(Polygon const& p : polygons){
    //     std::cout << "Polygon with " << p.getVertexCount() << " vertices:\n";
    //     for(int i{} ; i < p.getVertexCount() ; ++i){
    //         std::cout << "  { " << p.getVertex(i).x << " | " << p.getVertex(i).y  << " }\n";  
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << "\n\n";
}

// Default initialization of SAT case scenario
void Core::SAT_init(){
    std::vector<Vector2r> p1_vertices{{200,50}, {340,155}, {300,350}, {100,350}, {50,150}};
    Polygon p1(p1_vertices, {300,300});
    p1.setColor(green);
    p1.setBorder(5);
    p1.setBorderColor(sf::Color::White);

    std::vector<Vector2r> p2_vertices{{150, 50}, {300,50}, {400,200}, {300,350}, {150,350}, {50,200}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(blue);
    p2.setBorder(5);
    p2.setBorderColor(sf::Color::White);


    polygons.emplace_back(p1);
    polygons.emplace_back(p2);

    algth = new SAT();
}

// Default initialization of GJK case scenario
void Core::GJK_init(){
    std::vector<Vector2r> p1_vertices{{50,0}, {300,0}, {300,200}, {50,200}, {0,100}};
    Polygon p1{p1_vertices, {300,300}};
    p1.setColor(green);
    // p1.setBorder(5);
    // p1.setBorderColor(sf::Color::White);

    std::vector<Vector2r> p2_vertices{{0,0}, {200,0}, {200,330}, {0,330}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(blue);
    // p2.setBorder(5);
    // p2.setBorderColor(sf::Color::White);


    polygons.emplace_back(p1);
    polygons.emplace_back(p2);
    
    algth = new GJK();
}


} // namespace CDP