/*****************************************************************************/
/*!
  Shader implementation. Loads, compiles, and links shaders.
*/
/*****************************************************************************/
#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragPath)
{
  //Get the shaders.
  std::string vertexCode, fragCode;
  std::ifstream vShaderFile, fShaderFile;

  //Enable exception throwing on ifstreams.
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);

  try
  {
    //Open the files.
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragPath);

    //Read the files into a stream.
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    
    //Close files before we forget.
    vShaderFile.close();
    fShaderFile.close();

    //Convert streams into GLchar arrays.
    vertexCode = vShaderStream.str();
    fragCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "Shader files not read successfully." << std::endl;
  }

  //Copy code into OpenGL variables. (GLchar)
  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar* fShaderCode = fragCode.c_str();

  //Compile shaders.
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  //Compile vertex shader...
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    //Print debug message, if necessary.
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error compiling vertex shader!\n" << infoLog << std::endl;
  }

  //Compile frag shader...
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "Error compiling fragment shader!\n" << infoLog << std::endl;
  }

  //Create the shader program.
  this->program = glCreateProgram();
  glAttachShader(this->program, vertex);
  glAttachShader(this->program, fragment);
  glLinkProgram(this->program);
  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if (!success)
  {
    //Print debug message, if necessary.
    glGetProgramInfoLog(this->program, 512, NULL, infoLog);
    std::cout << "Error linking the shader program!\n" << infoLog << std::endl;
  }

  //Now that we're done with the vertex and fragment shaders, delete them.
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use()
{
  //Just call the OpenGL use function.
  glUseProgram(this->program);
}

void Shader::operator()(const GLchar* vertexPath, const GLchar* fragPath)
{
  //Get the shaders.
  std::string vertexCode, fragCode;
  std::ifstream vShaderFile, fShaderFile;

  //Enable exception throwing on ifstreams.
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);

  try
  {
    //Open the files.
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragPath);

    //Read the files into a stream.
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    //Close files before we forget.
    vShaderFile.close();
    fShaderFile.close();

    //Convert streams into GLchar arrays.
    vertexCode = vShaderStream.str();
    fragCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "Shader files not read successfully." << std::endl;
  }

  //Copy code into OpenGL variables. (GLchar)
  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar* fShaderCode = fragCode.c_str();

  //Compile shaders.
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  //Compile vertex shader...
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    //Print debug message, if necessary.
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error compiling vertex shader!\n" << infoLog << std::endl;
  }

  //Compile frag shader...
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "Error compiling fragment shader!\n" << infoLog << std::endl;
  }

  //Create the shader program.
  this->program = glCreateProgram();
  glAttachShader(this->program, vertex);
  glAttachShader(this->program, fragment);
  glLinkProgram(this->program);
  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if (!success)
  {
    //Print debug message, if necessary.
    glGetProgramInfoLog(this->program, 512, NULL, infoLog);
    std::cout << "Error linking the shader program!\n" << infoLog << std::endl;
  }

  //Now that we're done with the vertex and fragment shaders, delete them.
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::SetUniform(int var, const GLchar* name)
{
  glUniform1i(glGetUniformLocation(program, name), var);
}

void Shader::SetUniform(float var, const GLchar* name)
{
  glUniform1f(glGetUniformLocation(program, name), var);
}
