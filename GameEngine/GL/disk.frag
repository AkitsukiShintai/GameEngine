#version 130

uniform sampler2D sampler;

in vec4 coordinates;

out vec4 frag_color;

void main(void) {
  vec3 v = normalize(coordinates.xyz);
  vec2 uv = 0.5*vec2(v.x+1,1-v.y);
  frag_color = max(0,sign(v.z)) * texture(sampler,uv);
}

