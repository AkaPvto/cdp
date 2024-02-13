#version 330 core

out vec4 FragColor;
in vec4 color;


uniform vec4 intersecColor;
uniform vec4 sensitiveColor1;
uniform vec4 sensitiveColor2;

void main(){
    vec4 prev_color = FragColor;

    FragColor = color;

    // if(prev_color == sensitiveColor1) FragColor = intersecColor;

    // // check if the given color is one of the sensitive colors
    // if(color == sensitiveColor1 || color == sensitiveColor2){
    //     // if the fragment's current color is not the same as the given color
    //     if(color != prev_color){
    //         // if the fragment's current color is one of the sensitive colors
    //         if(prev_color == sensitiveColor1 || prev_color == sensitiveColor2){
    //             FragColor = intersecColor;
    //         }
    //     }
    // }


}