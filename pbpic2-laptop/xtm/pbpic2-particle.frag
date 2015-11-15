#version 400

in vec4 colour;
uniform sampler2D particle_tex;

out vec4 outColor;

void main() {
  // outColor = colour;
  outColor = texture(particle_tex, gl_PointCoord) * colour;
}
