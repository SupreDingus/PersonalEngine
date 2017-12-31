#version 330 core

layout (location = 0) in vec3 position; //Position var has attribute position 0
layout (location = 1) in vec3 color;    //Color var has attribute position 1
layout (location = 2) in vec2 texCoord; //Texture var has attrib. position 2

uniform mat4 Transform;
uniform mat4 Projection;
uniform mat4 View;

out vec2 TexCoord;

void main()
{
  //Projection * view * model * local
  //Model is the model's dimensions, local is the place in the world.
  //View is the camera direction, projection puts it on screen.
  gl_Position = Projection * View * Transform * vec4(position, 1.0f);
  
  //Invert the y on the texcoords.
  TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
