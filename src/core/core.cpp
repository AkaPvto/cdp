// This file will contain the core function of the program
#include "core.hpp"

#include <iostream>
#include <vector>
#include <array>

#include "algorithm/aabb.hpp"
#include "algorithm/gjk.hpp"
#include "algorithm/sat.hpp"

#include "sys/render.tpp"

// #include "algorithm"
// #include "algorithm"


#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define SOFT_GREEN          33_u8 , 184_u8, 49_u8 , 255_u8
#define LIGHT_BLUE          72_u8 , 191_u8, 191_u8, 255_u8
#define CREAM_RED           205_u8, 70_u8 , 56_u8 , 255_u8
#define WHITE               255_u8, 255_u8, 255_u8, 255_u8


namespace CDP{

// Constructor of the class
Core::Core( std::string name, double const w, double const h ) : 
 renderPol{uint32_t(w), uint32_t(h)}, width{w}, height{h}, initialize_types{&Core::AABB_init, &Core::SAT_init, &Core::GJK_init} {
    // window(sf::VideoMode(h, w), "Collisions");
    render.init(w, h, name.c_str());
    render.setBackgroundColor(Color(BACKGROUND_COLOR));
}
void Core::mouse_movement(){
    if(dynamic_cast<AABB*>(algth) == nullptr && render.isKeyPressed(GLFW_KEY_A)){
        delete_shapes();
        initialize(0);
    }

    if(dynamic_cast<SAT*>(algth) == nullptr && render.isKeyPressed(GLFW_KEY_S)){
        delete_shapes();
        initialize(1);
    }

    if(dynamic_cast<GJK*>(algth) == nullptr && render.isKeyPressed(GLFW_KEY_G)){
        delete_shapes();
        initialize(2);
    }

    Vector2r localPos;
    render.getMousePos(localPos);
    localPos.y = height - localPos.y;
    Vector2r center_diff = polygons.at(0).getCenter();
    polygons[0].setPosition(localPos - center_diff);
    renderPol.update_position(polygons[0]);
}

// Run the main program
void Core::run(){
    // Initialize the program with the base state: AABB Collisions
    initialize(0);

    while(render.isOpen()){
        mouse_movement();
        check_collision();
        // draw_collision();
        draw();
    }
    delete_shapes();
    render.end();
}

void Core::check_collision(){    
    if(algth != nullptr){
        if(algth->colide(polygons[0], polygons[1])){
            polygons[0].setColor(Color(CREAM_RED));
            renderPol.update_color(polygons[0]);
            polygons[1].setColor(Color(CREAM_RED));
            renderPol.update_color(polygons[1]);
        }
        else{
            polygons[0].setColor(Color(SOFT_GREEN));
            renderPol.update_color(polygons[0]);
            polygons[1].setColor(Color(LIGHT_BLUE));
            renderPol.update_color(polygons[1]);
        }
    }
}

void Core::draw_collision(){
    // auto size = window.getSize();
    // DrawList draw_l{};
    // algth->draw(draw_l, polygons[0], polygons[1], size.x, size.y);
    // for(auto drawable : draw_l){
    //     if(drawable == nullptr) continue;
    //     window.draw(*drawable);
    // }
}

void Core::draw(){
    // for(auto& p : polygons){
    //     renderPol.update_buffers(p);
    // }
    render.update<Polygon>(polygons.data(), polygons.size());
}

void Core::delete_shapes(){
    for(auto& p : polygons){
        renderPol.delete_buffers(p);
    }
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
    p1.setColor(Color(SOFT_GREEN));
    p1.setBorder(5);
    p1.setBorderColor(Color(WHITE));

    std::vector<Vector2r> p2_vertices{{0,0}, {300,0}, {300,200}, {0,200}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(Color(LIGHT_BLUE));
    p2.setBorder(5);
    p2.setBorderColor(Color(WHITE));


    polygons.emplace_back(p1);
    renderPol.init_buffers(polygons.back());
    polygons.emplace_back(p2);
    renderPol.init_buffers(polygons.back());

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
    p1.setColor(Color(SOFT_GREEN));
    p1.setBorder(5);
    p1.setBorderColor(Color(WHITE));

    std::vector<Vector2r> p2_vertices{{150, 50}, {300,50}, {400,200}, {300,350}, {150,350}, {50,200}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(Color(LIGHT_BLUE));
    p2.setBorder(5);
    p2.setBorderColor(Color(WHITE));


    polygons.emplace_back(p1);
    renderPol.init_buffers(polygons.back());
    polygons.emplace_back(p2);
    renderPol.init_buffers(polygons.back());

    algth = new SAT();
}

// Default initialization of GJK case scenario
void Core::GJK_init(){
    std::vector<Vector2r> p1_vertices{{50,0}, {300,0}, {300,200}, {50,200}, {0,100}};
    Polygon p1{p1_vertices, {300,300}};
    p1.setColor(Color(SOFT_GREEN));
    // p1.setBorder(5);
    // p1.setBorderColor(Color(WHITE));

    std::vector<Vector2r> p2_vertices{{0,0}, {200,0}, {200,330}, {0,330}};
    Polygon p2(p2_vertices, {350,200});
    p2.setColor(Color(LIGHT_BLUE));
    // p2.setBorder(5);
    // p2.setBorderColor(Color(WHITE));


    polygons.emplace_back(p1);
    renderPol.init_buffers(polygons.back());
    polygons.emplace_back(p2);
    renderPol.init_buffers(polygons.back());
    
    algth = new GJK();
}


} // namespace CDP