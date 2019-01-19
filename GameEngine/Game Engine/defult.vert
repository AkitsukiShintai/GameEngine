#version 130

attribute vec4 position;
//attribute vec2 texture_coord;

uniform vec2 texture_coord;
uniform mat4 model_matrix;
out vec2 vtexture_coord;

vec2 getuv(vec4 pos){	

		vec4 uv =mat4(1.0f,0.0f,0.0f,0.0f,
						 0.0f,1.0f,0.0f,0.0f,
						 0.0f,0.0f,1.0f,0.0f,
						 0.0f,1.0f,0.0f,1.0f)  *  mat4(0.5f,0.0f,0.0f,0.0f,
						 0.0f,0.5f,0.0f,0.0f,
						 0.0f,0.0f,1.0f,0.0f,
						 0.0f,0.0f,0.0f,1.0f)*
					mat4(1.0f,0.0f,0.0f,0.0f,
						 0.0f,1.0f,0.0f,0.0f,
						 0.0f,0.0f,1.0f,0.0f,
						 1.0f,1.0f,0.0f,1.0f)  * 
					pos;
		vec2 t= vec2(uv.x,uv.y);
		return t;
}

void main() {
  
  gl_Position = model_matrix*position;
  vtexture_coord = getuv(position); //vec2(position.x,uv.y)position;
}

