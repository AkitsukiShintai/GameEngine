#version 130
     attribute vec4 position;
     uniform mat4 model_matrix;
     void main() {
       gl_Position =  model_matrix * position;
     
     }