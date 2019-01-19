#version 130

uniform sampler2D usampler;
in vec2 vtexture_coord;

out vec4 frag_color;

void main(void) {
  vec4 r = texture(usampler,vtexture_coord).xyzw;
  frag_color = r;//vec4(1,1,0,1);//
}

