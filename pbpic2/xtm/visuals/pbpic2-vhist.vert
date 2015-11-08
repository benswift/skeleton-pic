#version 400

layout(location = 0) in vec2 vertex_position;

uniform vec3 line_colour;
uniform vec2 nxny;

out vec4 colour;

void main () {
  colour = vec4(1,1,1,1);
  gl_Position = vec4(vertex_position.x/nxny.x,vertex_position.y/10000., 1.0, 1.0);
}
