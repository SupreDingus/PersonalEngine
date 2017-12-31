/*****************************************************************************/
/*!
  Math Source. Does the math stuff.
*/
/*****************************************************************************/
#include "Math.h"

void Normalize(Vec3& norm)
{
  //Get the length.
  float div = (norm.x * norm.x) + (norm.y * norm.y) + (norm.z * norm.z);
  div = sqrt(div);

  //Divide each component by the length.
  norm.x = norm.x / div;
  norm.y = norm.y / div;
  norm.z = norm.z / div;
}

void Normalize(Vec4& norm)
{
  //Get the length.
  float div = (norm.x * norm.x) + (norm.y * norm.y) + (norm.z * norm.z) + (norm.w * norm.w);
  div = sqrt(div);

  //Divide each component by the length.
  norm.x = norm.x / div;
  norm.y = norm.y / div;
  norm.z = norm.z / div;
  norm.w = norm.w / div;
}

void Normalize(GLVec3& norm)
{
  // Get the length.
  float div = (norm.x * norm.x) + (norm.y * norm.y) + (norm.z * norm.z);
  div = sqrt(div);

  //Divide each component by the length.
  norm.x = norm.x / div;
  norm.y = norm.y / div;
  norm.z = norm.z / div;
}

void Normalize(GLVec4& norm)
{
  //Get the length.
  float div = (norm.x * norm.x) + (norm.y * norm.y) + (norm.z * norm.z) + (norm.w * norm.w);
  div = sqrt(div);

  //Divide each component by the length.
  norm.x = norm.x / div;
  norm.y = norm.y / div;
  norm.z = norm.z / div;
  norm.w = norm.w / div;
}

Vec3 XYPerpendicular(Vec3 line)
{
  //Rotate 90 degrees counter clockwise.
  //Do this by negating the y, and switching the values.
  Vec3 ret;
  ret.x = -line.y;
  ret.y = line.x;
  ret.z = line.z;

  return ret;
}
