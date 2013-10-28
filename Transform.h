#include "Vertex.h"
#include "Matrix4.h"
#include "Ray.h"

class Transform  {
public:
	Transform();
	static Vertex* multiply(Matrix4& mat, Vertex& eye);
	static Vertex* multiply3(Matrix4& mat, Vertex& eye);
	static Vertex upvector(Vertex& up, Vertex& zvec);
	static Ray multiply(Matrix4& mat, Ray& ray);
};

