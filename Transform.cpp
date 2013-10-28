#include <iostream>
#include "Transform.h"

Vertex* Transform::multiply(Matrix4& mat, Vertex& vec) {
  float x = mat.mat[0][0]*vec.x + mat.mat[0][1]*vec.y + mat.mat[0][2]*vec.z + mat.mat[0][3];
  float y = mat.mat[1][0]*vec.x + mat.mat[1][1]*vec.y + mat.mat[1][2]*vec.z + mat.mat[1][3];
  float z = mat.mat[2][0]*vec.x + mat.mat[2][1]*vec.y + mat.mat[2][2]*vec.z + mat.mat[2][3];
  Vertex* ret = new Vertex::Vertex(x, y, z);
  return ret;
}

Vertex* Transform::multiply3(Matrix4& mat, Vertex& vec) {
  float x = mat.mat[0][0]*vec.x + mat.mat[0][1]*vec.y + mat.mat[0][2]*vec.z;
  float y = mat.mat[1][0]*vec.x + mat.mat[1][1]*vec.y + mat.mat[1][2]*vec.z;
  float z = mat.mat[2][0]*vec.x + mat.mat[2][1]*vec.y + mat.mat[2][2]*vec.z;
  Vertex* ret = new Vertex::Vertex(x, y, z);
  return ret;
}

Ray Transform::multiply(Matrix4& mat, Ray& ray) {
	Vertex* pos = multiply(mat, *ray.pos);
	Vertex* dir = multiply3(mat, *ray.dir);
  dir = new Vertex::Vertex(dir->x, dir->y, dir->z);
	Ray* new_ray = new Ray::Ray(pos, dir, ray.t_min, ray.t_max);
	return *new_ray;
}

Transform::Transform()
{

}

Vertex Transform::upvector(Vertex &up, Vertex & zvec) {
  Vertex x = Vertex::cross(up, zvec); 
  Vertex y = Vertex::cross(zvec, x); 
  Vertex ret = Vertex::normalize(y); 
  return ret; 
}