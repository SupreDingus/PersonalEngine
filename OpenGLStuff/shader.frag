#version 330 core

in vec2 TexCoord; //Also get the texture stuff.

out vec4 color;

//Uniforms.
uniform sampler2D ourTexture;
uniform int Grey;

void main()
{
  //Setting the color to what's on the texture - standard.
  if(Grey != 1)
  {
    color = texture(ourTexture, TexCoord);
    return;
  }
  
  //Greyscale. Find the highest value, set that as each value.
  vec4 check = texture(ourTexture, TexCoord);
  float max;

  if(check.x > check.y)
    max = check.x;
  else
    max = check.y;

  if(check.z > max)
    max = check.z;

  color = vec4(max, max, max, 1.f);
}
