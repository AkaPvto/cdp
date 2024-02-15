#include "aabb.hpp"
#include "sys/render.tpp"
#include "render/renderpolygon.hpp"
#include "render/rendersegment.hpp"

#include "types/line.hpp"
#include <iostream>


#define DRAWING_MARGIN 150
#define SEGMENT_MARGIN 30
#define SEGMENT_WIDTH  3
#define SEGMENT_HEIGHT 30
#define INTERSEC_COLOR 205_u8, 70_u8 , 56_u8 , 255_u8
#define LINE_COLOR 0.0f, 0.0f, 0.0f, 0.3f
#define LINE_WIDTH 4


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


void AABB::init_projection(RenderPolygon& renderPol, RenderLine& renderLine, ProjectionData const& data, Color const& color){
        // Axis projection
        Polygon p(data.pol_vertices, Vector2r{});
        p.setColor(color);
        projections.emplace_back(p);
        renderPol.init_buffers(projections.back());

        // Two lines per projections' polygon
        Line line_1(data.line1.start, data.line1.end, Color(LINE_COLOR), LINE_WIDTH);
        projection_lines.emplace_back(line_1);
        renderLine.init_buffers(projection_lines.back());
    
        Line line_2(data.line2.start, data.line2.end, Color(LINE_COLOR), LINE_WIDTH); 
        projection_lines.emplace_back(line_2);
        renderLine.init_buffers(projection_lines.back());
}

void AABB::init_draw(RenderSystem& render, RenderPolygon& renderPol, RenderSegment& renderSegment, RenderLine& renderLine, Polygon& b1, Polygon& b2){
    // Exclude more-or-less vertices polygons
    if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return;


    // Set default polygons colors
    color1 = b1.getColor();
    color2 = b2.getColor();

    // Init the segments
    auto init_x_segment = [&](Polygon& polygon){
        real y_Segments = SEGMENT_MARGIN;
        Vector2r pos_x = Vector2r{polygon.getPosition().x, y_Segments};
        float length = polygon.getVertex(1).x - polygon.getVertex(0).x;
        segments.emplace_back(pos_x, length, SEGMENT_HEIGHT, SEGMENT_WIDTH, 0, polygon.getColor());
        renderSegment.init_buffers(segments.back());
    };

    auto init_y_segment = [&](Polygon& polygon){
        real x_Segments = render.getWidth() - SEGMENT_MARGIN;
        Vector2r pos_y = Vector2r{x_Segments, polygon.getPosition().y};
        float length = polygon.getVertex(3).y - polygon.getVertex(0).y;
        segments.emplace_back(pos_y, length, SEGMENT_HEIGHT, SEGMENT_WIDTH, 90, polygon.getColor());
        renderSegment.init_buffers(segments.back());
    };

    init_x_segment(b1);
    init_x_segment(b2);
    init_y_segment(b1);
    init_y_segment(b2);


    real y_limit = DRAWING_MARGIN;
    real x_limit = render.getWidth() - DRAWING_MARGIN;
    
    ProjectionData data_x_1(getX_projection(b1, y_limit));
    ProjectionData data_x_2(getX_projection(b2, y_limit));
    ProjectionData data_y_1(getY_projection(b1, x_limit));
    ProjectionData data_y_2(getY_projection(b2, x_limit));

    init_projection(renderPol, renderLine, data_x_1, color1);
    init_projection(renderPol, renderLine, data_x_2, color2);
    init_projection(renderPol, renderLine, data_y_1, color1);
    init_projection(renderPol, renderLine, data_y_2, color2);
    
}

// Update segments color per axis
void AABB::update_segment_color(RenderSegment& renderSegment, size_t index, bool axis_col){
    Color intersec_color(INTERSEC_COLOR);

    Segment& segment_1 = segments.at(index);
    Segment& segment_2 = segments.at(index+1);

    if(axis_col){
        segment_1.setColor(intersec_color);
        segment_2.setColor(intersec_color);
    }
    else{
        segment_1.setColor(color1);
        segment_2.setColor(color2);
    }

    renderSegment.update_color(segment_1);
    renderSegment.update_color(segment_2);
}

// Update the segments position
void AABB::update_segment_pos(RenderSegment& renderSegment, size_t index, Polygon& polygon){
    Segment& segment_x = segments.at(index);
    segment_x.setPos(Vector2r{polygon.getPosition().x, segment_x.getPos().y});
    renderSegment.update_buffers(segment_x);

    Segment& segment_y = segments.at(index+2);
    segment_y.setPos(Vector2r{segment_y.getPos().x, polygon.getPosition().y});
    renderSegment.update_buffers(segment_y);
}

// Update the projections' color
void AABB::update_projection_color(RenderPolygon& renderPol, size_t index, bool axis_col){
    Color intersec_color(INTERSEC_COLOR);
    intersec_color.setAlpha(0.6f);

    Polygon& projection_1 = projections.at(index);
    Polygon& projection_2 = projections.at(index+1);

    if(axis_col){
        projection_1.setColor(intersec_color);
        projection_2.setColor(intersec_color);
    }
    else{
        Color c1(color1);
        c1.setAlpha(0.6f);
        projection_1.setColor(c1);

        Color c2(color2);
        c2.setAlpha(0.6f);
        projection_2.setColor(c2);
    }

    renderPol.update_buffers(projection_1);
    renderPol.update_buffers(projection_2);
}

// Update projections' position
void AABB::update_projection_pos(RenderPolygon& renderPol, RenderLine& renderLine, size_t index, ProjectionData const& data){
    projections.at(index).setVertices(data.pol_vertices);
    renderPol.update_buffers(projections.at(index));

    // Two lines per projections' polygon
    Line& line_1 = projection_lines.at(2*index);
    line_1.setStart(data.line1.start);
    line_1.setEnd(data.line1.end);
    renderLine.update_buffers(line_1);

    Line& line_2 = projection_lines.at(2*index+1); 
    line_2.setStart(data.line2.start);
    line_2.setEnd(data.line2.end);
    renderLine.update_buffers(line_2);
}

// Calculate the corresponding vertices for an axis given a polygon
AABB::ProjectionData AABB::getX_projection(Polygon& polygon, float margin) const{
    std::vector<Vector2r> px_vertices{  polygon.getVertex(0), 
                                        polygon.getVertex(1), 
                                        {polygon.getVertex(1).x, margin}, 
                                        {polygon.getVertex(0).x, margin} };

    ProjectionData data{ px_vertices,
                    { polygon.getVertex(1) + Vector2r{-2, 0}, {polygon.getVertex(1).x-2, margin} },
                    { polygon.getVertex(0) + Vector2r{ 2, 0}, {polygon.getVertex(0).x+2, margin} }
                };

    return data;
}

AABB::ProjectionData AABB::getY_projection(Polygon& polygon, float margin) const{
    std::vector<Vector2r> py_vertices{  polygon.getVertex(1), 
                                        polygon.getVertex(2),
                                        {margin, polygon.getVertex(2).y}, 
                                        {margin, polygon.getVertex(1).y} };

    ProjectionData data{ py_vertices,
                    { polygon.getVertex(1) + Vector2r{0, 2}, {margin, polygon.getVertex(1).y +2} },
                    { polygon.getVertex(2) + Vector2r{0,-2}, {margin, polygon.getVertex(2).y -2} }
                    };

    return data;
}

void AABB::update_color(RenderPolygon& renderPol, RenderSegment& renderSegment){
    update_segment_color(renderSegment, 0, axis_x_col);
    update_segment_color(renderSegment, 2, axis_y_col);
    
    update_projection_color(renderPol, 0, axis_x_col);
    update_projection_color(renderPol, 2, axis_y_col);
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


    update_color(renderPol, renderSegment);
    update_segment_pos(renderSegment, change_F, *polygon);

    real y_limit = DRAWING_MARGIN;
    real x_limit = render.getWidth() - DRAWING_MARGIN;

    ProjectionData data_x_1(getX_projection(*polygon, y_limit));
    ProjectionData data_y_1(getY_projection(*polygon, x_limit));

    update_projection_pos(renderPol, renderLine, change_F, data_x_1);
    update_projection_pos(renderPol, renderLine, change_F+2, data_y_1);
}

void AABB::update_all(RenderSystem& render, RenderPolygon& renderPol, RenderSegment& renderSegment, RenderLine& renderLine, Polygon& b1, Polygon& b2){
    // Exclude more-or-less vertices polygons
    if(b1.getVertexCount() != 4 || b2.getVertexCount() != 4) return;

    // Update both the polygons
    update_color(renderPol, renderSegment);

    update_segment_pos(renderSegment, 0, b1);
    update_segment_pos(renderSegment, 1, b2);

    real y_limit = DRAWING_MARGIN;
    real x_limit = render.getWidth() - DRAWING_MARGIN;


    ProjectionData data_x_1(getX_projection(b1, y_limit));
    ProjectionData data_x_2(getX_projection(b2, y_limit));
    ProjectionData data_y_1(getY_projection(b1, x_limit));
    ProjectionData data_y_2(getY_projection(b2, x_limit));

    update_projection_pos(renderPol, renderLine, 0, data_x_1);
    update_projection_pos(renderPol, renderLine, 1, data_x_2);
    update_projection_pos(renderPol, renderLine, 2, data_y_1);
    update_projection_pos(renderPol, renderLine, 3, data_y_2);
}

void AABB::draw(RenderSystem& renderSys){
    if(projection_F) renderSys.draw<Polygon>(projections.data(), projections.size());
    if(projection_F) renderSys.draw<Line>(projection_lines.data(), projection_lines.size());
    if(intersection_F) renderSys.draw<Segment>(segments.data(), segments.size());
}


} // namespace CDP