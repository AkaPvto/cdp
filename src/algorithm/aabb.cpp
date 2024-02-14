#include "aabb.hpp"
#include "sys/render.tpp"
#include "render/renderpolygon.hpp"
#include "render/rendersegment.hpp"

#include "types/line.hpp"
#include <iostream>


#define DRAWING_MARGIN 150

namespace CDP{

// Check collisions between 2 boxes using AABB
bool AABB::colide(Polygon const& b1, Polygon const& b2){
    // Colision state default true
    axis_x_col = true;
    axis_y_col = true;

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
    if(xMax_1 < xMin_2 || xMin_1 > xMax_2) axis_x_col = false;
    // Same with Y axis
    if(yMax_1 < yMin_2 || yMin_1 > yMax_2) axis_y_col = false;

    if(!(axis_x_col && axis_y_col)) return false;

    return true;
}

// OLD INIT_DRAW
/*
{
    real y_Segments = 30;
    Vector2r pos_1_x = Vector2r{b1.getPosition().x, y_Segments};
    float length = b1.getVertex(1).x - b1.getVertex(0).x;
    segments.emplace_back(pos_1_x, length, 30, 3, 0, b1.getColor());
    renderSegment.init_buffers(segments.back());
    
    Vector2r pos_2_x = Vector2r{b2.getPosition().x, y_Segments};
    length = b2.getVertex(1).x - b2.getVertex(0).x;
    segments.emplace_back(pos_2_x, length, 30, 3, 0, b2.getColor());
    renderSegment.init_buffers(segments.back());

    real x_Segments = render.getWidth() - 30;
    Vector2r pos_1_y = Vector2r{x_Segments, b1.getPosition().y};
    length = b1.getVertex(3).y - b1.getVertex(0).y;
    segments.emplace_back(pos_1_y, length, 30, 3, 90, b1.getColor());
    renderSegment.init_buffers(segments.back());
    
    Vector2r pos_2_y = Vector2r{x_Segments, b2.getPosition().y};
    length = b2.getVertex(3).y - b2.getVertex(0).y;
    segments.emplace_back(pos_2_y, length, 30, 3, 90, b2.getColor());
    renderSegment.init_buffers(segments.back());

    // 1st Polygon, Axis-X projection
    Color c1{b1.getColor().r, b1.getColor().g, b1.getColor().b, 155};
    real y_limit = DRAWING_MARGIN;
    std::vector<Vector2r> p1_x_vertices{ b1.getVertex(0), 
                                        b1.getVertex(1), 
                                        {b1.getVertex(1).x, y_limit}, 
                                        {b1.getVertex(0).x, y_limit} };
    Polygon p1_x(p1_x_vertices, Vector2r{});
    p1_x.setColor(c1);
    p1_x.setBorder(5);
    p1_x.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    projections.emplace_back(p1_x);
    renderPol.init_buffers(projections.back());

    // Two lines per projections' polygon
    Color line_color(1.0f, 1.0f, 1.0f, 1.0f);
    float line_width{4};
    Line first_l_x1(b1.getVertex(1) + Vector2r{-2, 0}, Vector2r{b1.getVertex(1).x-2, y_limit}, line_color, line_width);
    Line second_l_x1(b1.getVertex(0)+ Vector2r{2,0}, Vector2r{b1.getVertex(0).x+2, y_limit}, line_color, line_width);
    projection_lines.emplace_back(first_l_x1);
    renderLine.init_buffers(projection_lines.back());
    projection_lines.emplace_back(second_l_x1);
    renderLine.init_buffers(projection_lines.back());


    

    // 2nd Polygon, Axis-X projection
    Color c2{b2.getColor().r, b2.getColor().g, b2.getColor().b, 155};
    std::vector<Vector2r> p2_x_vertices{ b2.getVertex(0), 
                                        b2.getVertex(1), 
                                        {b2.getVertex(1).x, y_limit}, 
                                        {b2.getVertex(0).x, y_limit} };
    Polygon p2_x(p2_x_vertices, Vector2r{0,0});
    p2_x.setColor(c2);
    p2_x.setBorder(5);
    p2_x.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    projections.emplace_back(p2_x);
    renderPol.init_buffers(projections.back());

    // Two lines per projections' polygon
    Line first_l_x2(b2.getVertex(1) + Vector2r{-2, 0}, Vector2r{b2.getVertex(1).x-2, y_limit}, line_color, line_width);
    Line second_l_x2(b2.getVertex(0) + Vector2r{2,0}, Vector2r{b2.getVertex(0).x+2, y_limit}, line_color, line_width);
    projection_lines.emplace_back(first_l_x2);
    renderLine.init_buffers(projection_lines.back());
    projection_lines.emplace_back(second_l_x2);
    renderLine.init_buffers(projection_lines.back());



    // 1st Polygon, Axis-Y projection
    real x_limit = render.getWidth() - DRAWING_MARGIN;
    std::vector<Vector2r> p1_y_vertices{ b1.getVertex(1), 
                                        b1.getVertex(2),
                                        {x_limit, b1.getVertex(2).y}, 
                                        {x_limit, b1.getVertex(1).y} };
    Polygon p1_y(p1_y_vertices, Vector2r{});
    p1_y.setColor(c1);
    p1_y.setBorder(5);
    p1_y.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    projections.emplace_back(p1_y);
    renderPol.init_buffers(projections.back());

    // Two lines per projections' polygon
    Line first_l_y1(b1.getVertex(1), Vector2r{x_limit, b1.getVertex(1).y}, line_color, line_width);
    Line second_l_y1(b1.getVertex(2), Vector2r{x_limit, b1.getVertex(2).y}, line_color, line_width);
    projection_lines.emplace_back(first_l_y1);
    renderLine.init_buffers(projection_lines.back());
    projection_lines.emplace_back(second_l_y1);
    renderLine.init_buffers(projection_lines.back());



    // 2nd Polygon, Axis-Y projection
    std::vector<Vector2r> p2_y_vertices{ b2.getVertex(1), 
                                        b2.getVertex(2), 
                                        {x_limit, b2.getVertex(2).y}, 
                                        {x_limit, b2.getVertex(1).y} };
    Polygon p2_y(p2_y_vertices, Vector2r{});
    p2_y.setColor(c2);
    p2_y.setBorder(5);
    p2_y.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    projections.emplace_back(p2_y);
    renderPol.init_buffers(projections.back());


    // Two lines per projections' polygon
    Line first_l_y2(b2.getVertex(1), Vector2r{x_limit, b2.getVertex(1).y}, line_color, line_width);
    Line second_l_y2(b2.getVertex(2), Vector2r{x_limit, b2.getVertex(2).y}, line_color, line_width);
    projection_lines.emplace_back(first_l_y2);
    renderLine.init_buffers(projection_lines.back());
    projection_lines.emplace_back(second_l_y2);
    renderLine.init_buffers(projection_lines.back());
}
*/

void AABB::init_draw(RenderSystem& render, RenderPolygon& renderPol, RenderSegment& renderSegment, RenderLine& renderLine, Polygon& b1, Polygon& b2){
    // Exclude more-or-less vertices polygons
    if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return;

    // Init the segments
    auto init_x_segment = [&](Polygon& polygon){
        real y_Segments = 30;
        Vector2r pos_x = Vector2r{polygon.getPosition().x, y_Segments};
        float length = polygon.getVertex(1).x - polygon.getVertex(0).x;
        segments.emplace_back(pos_x, length, 30, 3, 0, polygon.getColor());
        renderSegment.init_buffers(segments.back());
    };

    auto init_y_segment = [&](Polygon& polygon){
        real x_Segments = render.getWidth() - 30;
        Vector2r pos_y = Vector2r{x_Segments, polygon.getPosition().y};
        float length = polygon.getVertex(3).y - polygon.getVertex(0).y;
        segments.emplace_back(pos_y, length, 30, 3, 90, polygon.getColor());
        renderSegment.init_buffers(segments.back());
    };

    init_x_segment(b1);
    init_x_segment(b2);
    init_y_segment(b1);
    init_y_segment(b2);


    Color line_color(1.0f, 1.0f, 1.0f, 1.0f);
    float line_width{4};

    // Init the projections and lines
    auto init_x_projection = [&](Polygon& polygon){
        // Axis-X projection
        Color color{polygon.getColor().r, polygon.getColor().g, polygon.getColor().b, 155};
        real y_limit = DRAWING_MARGIN;
        std::vector<Vector2r> pol_x_verts{ polygon.getVertex(0), 
                                            polygon.getVertex(1), 
                                            {polygon.getVertex(1).x, y_limit}, 
                                            {polygon.getVertex(0).x, y_limit} };
        Polygon p1_x(pol_x_verts, Vector2r{});
        p1_x.setColor(color);
        p1_x.setBorder(5);
        p1_x.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        projections.emplace_back(p1_x);
        renderPol.init_buffers(projections.back());

        // Two lines per projections' polygon
        Color line_color(1.0f, 1.0f, 1.0f, 1.0f);
        float line_width{4};
        Line first_l_x1(polygon.getVertex(1) + Vector2r{-2, 0}, Vector2r{polygon.getVertex(1).x-2, y_limit}, line_color, line_width);
        Line second_l_x1(polygon.getVertex(0)+ Vector2r{2,0}, Vector2r{polygon.getVertex(0).x+2, y_limit}, line_color, line_width);
        projection_lines.emplace_back(first_l_x1);
        renderLine.init_buffers(projection_lines.back());
        projection_lines.emplace_back(second_l_x1);
        renderLine.init_buffers(projection_lines.back());
    };

    auto init_y_projection = [&](Polygon& polygon){
        // Axis-Y projection
        Color color{polygon.getColor().r, polygon.getColor().g, polygon.getColor().b, 155};
        real x_limit = render.getWidth() - DRAWING_MARGIN;
        std::vector<Vector2r> pos_y_verts{ b1.getVertex(1), 
                                            b1.getVertex(2),
                                            {x_limit, b1.getVertex(2).y}, 
                                            {x_limit, b1.getVertex(1).y} };
        Polygon p1_y(pos_y_verts, Vector2r{});
        p1_y.setColor(color);
        p1_y.setBorder(5);
        p1_y.setBorderColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        projections.emplace_back(p1_y);
        renderPol.init_buffers(projections.back());

        // Two lines per projections' polygon
        Line first_l_y1(b1.getVertex(1), Vector2r{x_limit, b1.getVertex(1).y}, line_color, line_width);
        Line second_l_y1(b1.getVertex(2), Vector2r{x_limit, b1.getVertex(2).y}, line_color, line_width);
        projection_lines.emplace_back(first_l_y1);
        renderLine.init_buffers(projection_lines.back());
        projection_lines.emplace_back(second_l_y1);
        renderLine.init_buffers(projection_lines.back());
    };

    init_x_projection(b1);
    init_x_projection(b2);
    init_y_projection(b1);
    init_y_projection(b2);
    
}

void AABB::update(RenderSystem& render, RenderPolygon& renderPol, RenderSegment& renderSegment, RenderLine& renderLine, Polygon& b1, Polygon& b2){
    // Exclude more-or-less vertices polygons
    if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return;

    // Check the changes flag to update the buffers of the graphic helpers
    if(change_F < 0) return;

    // Select the polygon to update
    Polygon* polygon = &b1;
    if(change_F == 1) polygon = &b2; 
    else if(change_F >=2){
        std::cout << "ERROR: More than 2 polygons in the program\n";
        return;
    }

    
    // Update axis color
    auto update_segment_color = [&](size_t index, bool& axis_col){
        Color intersec_color(1.0f,1.0f,1.0f,1.0f);

        Segment& segment_1 = segments.at(index);
        Segment& segment_2 = segments.at(index+1);

        if(axis_col){
            segment_1.setColor(intersec_color);
            segment_2.setColor(intersec_color);
        }
        else{
            segment_1.setColor(b1.getColor());
            segment_2.setColor(b2.getColor());
        }
    };

    auto update_segment_pos = [&](size_t index, Polygon& polygon){
        // Update the segments
        Segment& segment_x = segments.at(index);
        segment_x.setPos(Vector2r{polygon.getPosition().x, segment_x.getPos().y});
        renderSegment.update_buffers(segment_x);

        Segment& segment_y = segments.at(index+2);
        segment_y.setPos(Vector2r{segment_y.getPos().x, polygon.getPosition().y});
        renderSegment.update_buffers(segment_y);
    };

    update_segment_color(0, axis_x_col);
    update_segment_color(2, axis_y_col);
    update_segment_pos(0, b1);
    update_segment_pos(1, b2);

    // Color of the polygon (red if colliding)
    Color color = polygon->getColor();
    // Update the projections

    // Reduce the alpha chanel for projections
    color.a *= 0.6f; 
    color.a_f *= 0.6f; 



    // Update the projections and lines
    auto update_projection_color = [&](size_t index, bool& axis_col){
        Color intersec_color(1.0f,1.0f,1.0f,0.6f);

        Polygon& projection_1 = projections.at(index);
        Polygon& projection_2 = projections.at(index+1);

        if(axis_col){
            projection_1.setColor(intersec_color);
            projection_2.setColor(intersec_color);
        }
        else{
            Color c1(b1.getColor());
            c1.a *= 0.6f;
            c1.a_f *= 0.6f;
            projection_1.setColor(c1);

            Color c2(b2.getColor());
            c2.a *= 0.6f;
            c2.a_f *= 0.6f;
            projection_2.setColor(c2);
        }
    };

    auto update_data = [&](size_t index, std::vector<Vector2r> vertices, std::vector<Vector2r> lines){
        // Axis-X projection
        projections.at(index).setVertices(vertices);
        renderPol.update_buffers(projections.at(index));

        // Two lines per projections' polygon
        Line& line_1 = projection_lines.at(2*index);
        line_1.setStart(lines.at(0));
        line_1.setEnd(lines.at(1));
        renderLine.update_buffers(line_1);

        Line& line_2 = projection_lines.at(2*index+1); 
        line_2.setStart(lines.at(2));
        line_2.setEnd(lines.at(3));
        renderLine.update_buffers(line_2);
    };

    auto update_x_projection = [&](Polygon& polygon, size_t index){
        real y_limit = DRAWING_MARGIN;
        std::vector<Vector2r> px_vertices{  polygon.getVertex(0), 
                                            polygon.getVertex(1), 
                                            {polygon.getVertex(1).x, y_limit}, 
                                            {polygon.getVertex(0).x, y_limit} };

        std::vector<Vector2r> px_lines{ polygon.getVertex(1) + Vector2r{-2, 0},
                                       {polygon.getVertex(1).x-2, y_limit},
                                        polygon.getVertex(0)+ Vector2r{2,0},
                                       {polygon.getVertex(0).x+2, y_limit}};

        update_data(index, px_vertices, px_lines);
    };

    auto update_y_projection = [&](Polygon& polygon, size_t index){
        real x_limit = render.getWidth() - DRAWING_MARGIN;
        std::vector<Vector2r> py_vertices{  polygon.getVertex(1), 
                                            polygon.getVertex(2),
                                            {x_limit, polygon.getVertex(2).y}, 
                                            {x_limit, polygon.getVertex(1).y} };

        std::vector<Vector2r> py_lines{ polygon.getVertex(1) + Vector2r{0, 2},
                                       {x_limit, polygon.getVertex(1).y +2},
                                        polygon.getVertex(2) + Vector2r{0,-2},
                                       {x_limit, polygon.getVertex(2).y -2} };

        update_data(index+2, py_vertices, py_lines);
    };

    update_projection_color(0, axis_x_col);
    update_projection_color(2, axis_y_col);
    update_x_projection(b1, 0);
    update_x_projection(b2, 1);
    update_y_projection(b1, 0);
    update_y_projection(b2, 1);

    // Update the lines
     
}

void AABB::draw(RenderSystem& renderSys){
    if(projection_F) renderSys.draw<Polygon>(projections.data(), projections.size());
    if(projection_F) renderSys.draw<Line>(projection_lines.data(), projection_lines.size());
    if(intersection_F) renderSys.draw<Segment>(segments.data(), segments.size());
}

} // namespace CDP