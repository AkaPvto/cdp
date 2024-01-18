// g++ -c main.cpp && g++ -o main main.o libglfw.so.3 libglad.a libimgui.a 
// g++ -c main.cpp && g++ -o main main.o shaderprogram.o EBO.o VAO.o VBO.o libglfw.so.3 libglad.a libimgui.a

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"

// #include "render.hpp"

#include "shaderprogram.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include <vector>
#include <array>


#include <iostream>
#include <cmath>

#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define RED_CREAM           205_u8, 70_u8 , 56_u8 , 255_u8
#define BLUE_LIGHT          72_u8 , 191_u8, 191_u8, 255_u8
#define SOFT_GREEN          33_u8 , 184_u8, 49_u8 , 255_u8

#define SCREEN_WIDTH        1280
#define SCREEN_HEIGHT       720

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec4 aColor;"
"out vec4 color;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"   color = aColor;"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 color;"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";


uint8_t operator ""_u8(unsigned long long i){
    return uint8_t(i);
}
struct Color{
    uint8_t r{},g{},b{},a{};
    float   r_f{},g_f{},b_f{},a_f{};
    
    Color() = default;
    
    Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a) :
    r{_r}, g{_g}, b{_b}, a{_a}, r_f{_r/255.0f}, g_f{_g/255.0f}, b_f{_b/255.0f}, a_f{_a/255.0f} {}

    Color(float _r,float _g, float _b,float _a) :
    r{uint8_t(_r*255)}, g{uint8_t(_g*255)}, b{uint8_t(_b*255)}, a{uint8_t(_a*255)}, r_f{_r}, g_f{_g}, b_f{_b}, a_f{_a} {}
};
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(1280, 720, "Collision Detection Learning Program", NULL, NULL);
    if(window == NULL){
        std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    gladLoadGL();

    glViewport(0, 0, 1280, 720);

    Color red(RED_CREAM);
    Color blue(BLUE_LIGHT);

    struct Vector2r{
        float x{}, y{};

        Vector2r& operator=(std::initializer_list<float> list){
            x = *(list.begin());
            y = *(list.begin()+1);

            return *this;
        }
    };
    
    struct Polygon{
        Polygon(std::vector<Vector2r> v, Color c) : vertices{v}, color{c}{}
        std::vector<Vector2r> vertices;
        GLfloat* buffer_data;
        GLuint* index_data;
        Vector2r position{};
        Color color;
        VAO vao;
        VBO vbo;
        EBO ebo;

        void normalize_vertices(uint32_t width, uint32_t height){
            uint32_t norm_width = width/2;
            uint32_t norm_height = height/2;
            for(auto& v : vertices){
                v.x = (v.x-norm_width)/norm_width;
                v.y = (v.y-norm_height)/norm_height;
            }
        }

        void update_color(){
            for(size_t i{};i<vertices.size();++i){
                vbo.modify(reinterpret_cast<GLfloat*>(&color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*i*4);
            }
        }
        
        void update_color(Color c){
            color = c;
            update_color();
        }
        
        void update_position(float x, float y){
            position = {x,y};

            // Obtain the normalized value of the polygon's position
            uint32_t norm_width = SCREEN_WIDTH/2;
            uint32_t norm_height = SCREEN_HEIGHT/2;

            int count = 0;
            for(auto v : vertices){
                buffer_data[count++] = ((v.x+position.x)-norm_width)/norm_width;
                buffer_data[count++] = ((v.y+position.y)-norm_height)/norm_height;
                vbo.modify((buffer_data + (count-2)), sizeof(GLfloat)*2, sizeof(GLfloat)*(count-2));
                
                count +=4;
            }
        }

        void update_buffers(){
            // (x + y + color data (4 values))
            int vertex_size = 6;
            // Vertices size * vertex size
            int buffer_size = vertices.size()*(vertex_size);
            //(Ammount of triangles after teselating a polygon)*(number of vertices of a triangle) => (n_vertices-2)*(3)
            int index_size = (vertices.size()-2)*3;

            buffer_data = new GLfloat[buffer_size];
            index_data = new GLuint[index_size];

            // Obtain the normalized value of the polygon's position
            uint32_t norm_width = SCREEN_WIDTH/2;
            uint32_t norm_height = SCREEN_HEIGHT/2;

            // Insert the data of each vertex into the buffer_data
            int count = 0;
            for(auto v : vertices){
                buffer_data[count++] = ((v.x+position.x)-norm_width)/norm_width;
                buffer_data[count++] = ((v.y+position.y)-norm_height)/norm_height;
                buffer_data[count++] = color.r_f;
                buffer_data[count++] = color.g_f;
                buffer_data[count++] = color.b_f;
                buffer_data[count++] = color.a_f;
            }
            count = 0;
            
            // Insert the index of each vertex into the index_data
            for(size_t i = 1; i<vertices.size()-1; ++i){
                index_data[count++] = 0;
                index_data[count++] = i;
                index_data[count++] = i+1;
            }
    
            vao.bind();
            vbo.insert(buffer_data, sizeof(GLfloat)*buffer_size);
            ebo.insert(index_data,  sizeof(GLuint)*index_size);

            vbo.bind();
            vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
            vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
            vao.unbind();

            vbo.unbind();
            ebo.unbind();

        }

        void delete_buffers(){
            vbo.destroy();
            ebo.destroy();
            vao.destroy();
        }
    };
    std::vector<Polygon> polygons;
    
    std::vector<Vector2r> v2{{150, 50}, {300,50}, {400,200}, {300,350}, {150,350}, {50,200}};
    polygons.emplace_back(v2, blue);
    // polygons.back().normalize_vertices(1280, 720);

    std::vector<Vector2r> verts{{200,50}, {340,155}, {300,350}, {100,350}, {50,150}};
    polygons.emplace_back(verts, red);
    // polygons.back().normalize_vertices(1280, 720);




    // GLfloat vertices[] = {
    //     -0.5f, -0.5f * float(sqrt(3)) / 3,     red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f, -0.5f * float(sqrt(3)) / 3,      red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, 0.5f * float(sqrt(3)) *2 / 3,    red.r_f, red.g_f, red.b_f, red.a_f
    // };
    GLuint last_index = 0;
    std::vector<GLfloat> vertices;
    // GLfloat vertices[] = {
    //     -0.5f, -0.5f * float(sqrt(3)) / 3,     red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f, -0.5f * float(sqrt(3)) / 3,      red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, 0.5f * float(sqrt(3)) *2 / 3,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     -0.5f / 2, 0.5f * float(sqrt(3)) / 6,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f / 2, 0.5f * float(sqrt(3)) / 6,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, -0.5f * float(sqrt(3)) / 3,    red.r_f, red.g_f, red.b_f, red.a_f

    // };
    std::vector<GLuint> index_buff;
    // GLuint index_buff[] = {
    //     0, 3, 5,
    //     3, 2, 4,
    //     5, 4, 1
    // };
    // Probar idea:
    // Utilizar un std::vector<GLfloat> para almacenar los vertices de los poligonos
    // Pasar a la funcion de openGL la direccion de memoria del inicio del vector usando vector.begin()
    // Y el tamaño usando vector.size()
    // Con esto deberia de ser suficiente para que openGL no se coje y utilice los datos de std::vector
    auto add_polygons = [&](){
        for(auto& p : polygons){
            for(auto v : p.vertices){
                vertices.push_back(v.x);
                vertices.push_back(v.y);
                vertices.push_back(p.color.r_f);
                vertices.push_back(p.color.g_f);
                vertices.push_back(p.color.b_f);
                vertices.push_back(p.color.a_f);
            }
            for(size_t i = last_index+1; i<(last_index+p.vertices.size()-1); ++i){
                index_buff.push_back(last_index);
                index_buff.push_back(i);
                index_buff.push_back(i+1);
            }

            last_index += p.vertices.size(); 
        }

    };
    add_polygons();

    auto add_polygon = [&](int p){
        vertices.clear();
        index_buff.clear();

        auto& polygon = polygons.at(p);

        // (x + y + color data (4 values))
        int vertex_size = 6;
        // Vertices size * vertex size
        int buffer_size = polygon.vertices.size()*(vertex_size);
        //(Ammount of triangles after teselating a polygon)*(number of vertices of a triangle) => (n_vertices-2)*(3)
        int index_size = (polygon.vertices.size()-2)*3;

        // Insert the data of each vertex into the buffer_data
        int count = 0;
        for(auto v : polygon.vertices){
            vertices.push_back(v.x);
            vertices.push_back(v.y);
            vertices.push_back(polygon.color.r_f);
            vertices.push_back(polygon.color.g_f);
            vertices.push_back(polygon.color.b_f);
            vertices.push_back(polygon.color.a_f);
        }
        
        // Insert the index of each vertex into the index_data
        for(size_t i = 1; i<polygon.vertices.size()-1; ++i){
            index_buff.push_back(0);
            index_buff.push_back(i);
            index_buff.push_back(i+1);
        }
    };

    int count = 0;
    for(auto v : vertices){
        std::cout << "Vertex " << count << ": " << v << "\n";
        if(++count >= 6){
            count = 0;
            std::cout << std::endl;
        }
    }
    count = 0;
    for(auto i : index_buff){
        std::cout << "Vertex " << count << ": " << i << "\n";
        if(++count >= 3){
            count = 0;
            std::cout << std::endl;
        }
    }

    std::cout << "Empezamos el programa de renderizado\n";

    ShaderProgram shader_P{};
    shader_P.addShader("shader.vert", GL_VERTEX_SHADER);
    shader_P.addShader("shader.frag", GL_FRAGMENT_SHADER);
    // shader_P.addShader("shader.geom", GL_GEOMETRY_SHADER);
    shader_P.link();

    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);

    // GLuint shaderProgram = glCreateProgram();

    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);
    // glLinkProgram(shaderProgram);
    VAO vao1{};
    VAO vao2{};
    VBO vbo1{};
    VBO vbo2{};
    EBO ebo1{};
    EBO ebo2{};

            
    // Bindeo el VAO
    vao1.bind();
    
    // Rellena "vertices" y "index_buff" con los datos del poligono pasado por parametro
    add_polygon(1);
    // Guardas el tamaño del index_buff para despues usarlo en glDrawElements
    int index_size_1 = index_buff.size();
    // Insertas los datos en el VBO
    vbo1.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
    // Insertas los datos en el EBO
    ebo1.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
    
    // Bindeo el VBO
    vbo1.bind();
    // Añadir los atributos al VAO
    vao1.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    vao1.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    // Unbineamos el VAO
    vao1.unbind();
    
    vao2.bind();
    add_polygon(0);
    int index_size_2 = index_buff.size();
    vbo2.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
    ebo2.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
    
    vbo2.bind();
    vao2.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    vao2.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    vao2.unbind();
    
    vao1.unbind();
    vao2.unbind();
    vbo1.unbind();
    vbo2.unbind();
    ebo1.unbind();
    ebo2.unbind();
    
    
    polygons.at(0).update_buffers();
    polygons.at(1).update_buffers();

    
    
    // GLuint VAO;
    // GLuint VBO;
    // GLuint EBO;

    // glGenVertexArrays(1, &VAO);

    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*index_buff.size(), index_buff.data(), GL_STATIC_DRAW);

    // // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);


    
    // // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(2* sizeof(float)));
    // glEnableVertexAttribArray(1);
    
    // glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Color bkg(BACKGROUND_COLOR);
    int c{};
    std::vector<Vector2r> vrts;
    Color col;
    Vector2r pos_t{};
    Color green(SOFT_GREEN);
    std::cout << "Do we start this?\n";
    while(!glfwWindowShouldClose(window)){
        glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader_P.use();
        // glUseProgram(shaderProgram);
        // vao2.bind();
        // glDrawElements(GL_TRIANGLES, index_size_2, GL_UNSIGNED_INT, 0);

        // vao1.bind();
        // glDrawElements(GL_TRIANGLES, index_size_1, GL_UNSIGNED_INT, 0);
        
        for(auto& p : polygons){
            p.vao.bind();
            glDrawElements(GL_TRIANGLES, (p.vertices.size()-2)*3,GL_UNSIGNED_INT, 0);
        }
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // // glDrawElements(primitive, numIndices, typeIndices, index of indices (?))

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Window Tittle");
        ImGui::Text("Window text!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            if(c++ <= 0){
                float w = std::rand()%SCREEN_WIDTH;
                float h = std::rand()%SCREEN_HEIGHT;

                (polygons.end()-1)->update_position(w, h);


                vrts.clear();
                std::cout << "A is pressed\n";
                auto pol = polygons.begin();
                for(auto v : pol->vertices){
                    vrts.push_back(v);
                }
                col = pol->color;
                pos_t = pol->position;
                pol->delete_buffers();
                polygons.erase(polygons.begin());

            }
        }
        else{
            if(c>0){
                polygons.emplace_back(vrts, green);
                polygons.back().position = pos_t;
                polygons.back().update_buffers();
            }
            c=0;
        } 

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);
    vao1.destroy();
    vao2.destroy();
    vbo1.destroy();
    ebo1.destroy();
    vbo2.destroy();
    ebo2.destroy();
    // for(auto& p: polygons){
    //     p.delete_buffers();
    // }
    shader_P.destroy();


    glfwDestroyWindow(window);
    glfwTerminate();
}



// void RenderSystem::init(){
//     // GLFW initialization values/flags
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Window creation
//     // CHANGE WINDOW TO AN ATTRIBUTE
//     GLFWwindow* window = glfwCreateWindow(1280, 720, "Collision Detection Learning Program", NULL, NULL);
//     if(window == NULL){
//         std::cout << "Window could not be created!\n"; 
//         glfwTerminate();
//     }
//     glfwMakeContextCurrent(window);


//     // ImGui initialization and link with the window
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO();
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 130");
//     ImGui::StyleColorsDark();

//     // Glad initialization and configuration
//     gladLoadGL();

//     glViewport(0, 0, 1280, 720);




//     // Initialize the shader program
//     ShaderProgram shader_P{};
//     shader_P.addShader("shader.vert", GL_VERTEX_SHADER);
//     shader_P.addShader("shader.frag", GL_FRAGMENT_SHADER);
//     // shader_P.addShader("shader.geom", GL_GEOMETRY_SHADER);
//     shader_P.link();

//     VAO vao{};
//     VBO vbo{};
//     EBO ebo{};
    
//     vao.bind(); 
    
//     vao.addAttrib(vbo, 0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
//     vao.addAttrib(vbo, 1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    
//     vao.unbind();
//     vbo.unbind();
//     ebo.unbind();

    
// }

// void RenderSystem::update(){
//     // Rendering
//     glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
//     glClear(GL_COLOR_BUFFER_BIT);
//     shader_p.use();
//     // glUseProgram(shaderProgram);
//     vao.bind();
    
//     // glDrawArrays(GL_TRIANGLES, 0, 3);
//     // glDrawElements(primitive, numIndices, typeIndices, index of indices (?))
//     glDrawElements(GL_TRIANGLES, index_buff.size(), GL_UNSIGNED_INT, 0);



//     // User Interfaze management
//     UI.update(); // Create a manager class for the user interface using the imgui library

//     // Swap the buffer for rendering the next frame and call the events poll
//     glfwSwapBuffers(window);
//     glfwPollEvents();


//     // Empty the vertices and index arrays
    
//     vbo.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
//     ebo.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
// }

// void draw_polygon(){
//     // Process the given data into the vertices and index_buff arrays


// }

// struct RenderStorage{
//     RenderStorage(std::vector<GLfloat>& _v, std::vector<GLuint>& _ib, uint32_t& _li) : vertices{_v}, index_buff{_ib}, last_index{_li}{}
//     RenderStorage() = delete;
//     std::vector<GLfloat>& vertices;
//     std::vector<GLuint>& index_buff;
//     uint32_t& last_index;
// };



// template <typename T>
// void draw(T const& drawable){
//     // drawable.draw(RenderStorage(vertices, index_buff, last_index));

// }

// void insert(){
//     // Insert and configure the data
//     // vao.bind();

//     // vbo.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
//     // ebo.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
    
//     // vao.unbind();
//     // vbo.unbind();
//     // ebo.unbind();
// }


// void drawUI(){
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();

//     ImGui::Begin("Window Tittle");
//     ImGui::Text("Window text!");
//     ImGui::End();

//     ImGui::Render();
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// }

// void render(){
//     // // Draw the background
//     // glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
//     // glClear(GL_COLOR_BUFFER_BIT);   

//     // // Draw all the polygons
//     // // This function will draw all the polygons storaged in the class
//     // drawAll();

//     // // Draw the interface
//     // // This function will execute all the logic behind the UI
//     // drawUI();


//     // // Swap the buffer and call the events at the end of the render iteration
//     // glfwSwapBuffers(window);
//     // glfwPollEvents();
// }

// void end(){
//     // IMPLEMENT THIS LATER
//     // // Delete all the vertex objects and the shader program
//     // glDeleteBuffers(1, &VBO);
//     // glDeleteVertexArrays(1, &VAO);
//     // glDeleteProgram(shaderProgram);
    

//     // // Delete the glfw window
//     // glfwDestroyWindow(window);
//     // glfwTerminate();
// }
