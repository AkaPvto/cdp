#version 330 core

out vec4 FragColor;
in vec4 color;

// Blending only works with rectangles
// vec2(xMin)
// vec2(xMax)
// vec2(yMin)
// vec2(yMax)

struct Projection{
    vec2 xMax;
    vec2 xMin;
    vec2 yMax;
    vec2 yMin;
};

uniform Projection projectionsArray[15];
uniform vec4 intersecColor;

void main(){
    FragColor = color;

    int nProjections = int(length(projectionsArray));

    int inRect = 0;
    for(int i = 0; i < nProjections ; i++){
        if((xMax >= gl_FragCoord.x && xMin <= gl_FragCoord.x) && (yMax >= gl_FragCoord.y && yMin <= gl_FragCoord.y)){
            inRect++;
            if(inRect >= 2){
                FragColor = intersecColor;
                break;
            }
        }
    }
}