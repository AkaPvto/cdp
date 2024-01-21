#include "aabb.hpp"
#include <iostream>

#define DRAWING_X_MARGIN 20
#define DRAWING_Y_MARGIN 20

namespace CDP{

// Check collisions between 2 boxes using AABB
bool AABB::colide(Polygon const& b1, Polygon const& b2){
    // Exclude more-or-less vertices polygons
    if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return false;

    // We'll check each axis separately
    // The box's vertices are asumed to be setted clockwise, starting in the top-left:
    //          0--------1
    //          |        |
    //          3--------2

    real xMax_1{b1.getVertex(1).x}, xMin_1{b1.getVertex(0).x}, 
         xMax_2{b2.getVertex(1).x}, xMin_2{b2.getVertex(0).x};
    real yMax_1{b1.getVertex(3).y}, yMin_1{b1.getVertex(0).y}, 
         yMax_2{b2.getVertex(3).y}, yMin_2{b2.getVertex(0).y};

    // Check 1-dimensionaly if the boxes are colliding
    if(xMax_1 < xMin_2 || xMin_1 > xMax_2) return false;
    // Same with Y axis
    if(yMax_1 < yMin_2 || yMin_1 > yMax_2) return false;

    return true;
}

void AABB::draw(DrawList& draw_l, Polygon const& b1, Polygon const& b2, int window_w, int window_h){
     // // Exclude more-or-less vertices polygons
     // if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return;

     // real xMax_1{b1.getVertex(1).x}, xMin_1{b1.getVertex(0).x}, 
     //      xMax_2{b2.getVertex(1).x}, xMin_2{b2.getVertex(0).x};
     // real yMax_1{b1.getVertex(3).y}, yMin_1{b1.getVertex(0).y}, 
     //      yMax_2{b2.getVertex(3).y}, yMin_2{b2.getVertex(0).y};

     // if(proyection_F){
     //      sf::Color aux_color{};
     //      // Y proyection
     //           // p1
     //           sf::RectangleShape rect1_y{};
     //           rect1_y.setPosition({xMax_1, yMin_1});
     //           rect1_y.setSize({ window_w-xMax_1-DRAWING_X_MARGIN, yMax_1-yMin_1 });
     //           aux_color = b1.getColor();
     //           aux_color.a = uint8_t(120);
     //           rect1_y.setFillColor(aux_color);
     //           drawables.rectangles[0] = rect1_y;
     //           draw_l.push_back(dynamic_cast<sf::Drawable*>(&drawables.rectangles[0]));

     //           // p2
     //           sf::RectangleShape rect2_y{};
     //           rect2_y.setPosition({xMax_2, yMin_2});
     //           rect2_y.setSize({ window_w-xMax_2-DRAWING_X_MARGIN, yMax_2-yMin_2 });
     //           aux_color = b2.getColor();
     //           aux_color.a = uint8_t(120);
     //           rect2_y.setFillColor(aux_color);
     //           drawables.rectangles[1] = rect2_y;
     //           draw_l.push_back(dynamic_cast<sf::Drawable*>(&drawables.rectangles[1]));


     //      // X proyection
     //           // p1
     //           sf::RectangleShape rect1_x{};
     //           rect1_x.setPosition({xMin_1, yMax_1});
     //           rect1_x.setSize({ xMax_1-xMin_1, window_h - yMax_1-DRAWING_Y_MARGIN});
     //           aux_color = b1.getColor();
     //           aux_color.a = uint8_t(120);
     //           rect1_x.setFillColor(aux_color);
     //           drawables.rectangles[2] = rect1_x;
     //           draw_l.push_back(dynamic_cast<sf::Drawable*>(&drawables.rectangles[2]));

     //           // p2
     //           sf::RectangleShape rect2_x{};
     //           rect2_x.setPosition({xMin_2, yMax_2});
     //           rect2_x.setSize({ xMax_2-xMin_2, window_h - yMax_2-DRAWING_Y_MARGIN});
     //           aux_color = b2.getColor();
     //           aux_color.a = uint8_t(120);
     //           rect2_x.setFillColor(aux_color);
     //           drawables.rectangles[3] = rect2_x;
     //           draw_l.push_back(dynamic_cast<sf::Drawable*>(&drawables.rectangles[3]));

     // }

     // if(intersection_F){

     // }
}

} // namespace CDP