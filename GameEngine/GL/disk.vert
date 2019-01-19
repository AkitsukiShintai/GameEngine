#version 130

in vec4 position;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out vec4 coordinates;

void main() {
  coordinates = position;
  gl_Position = persp_matrix * view_matrix * model_matrix * position;
}

