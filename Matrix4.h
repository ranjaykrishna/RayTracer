#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vertex.h"

const float pi = 3.14159265 ; 

class Matrix4 {
	public:
		float mat[4][4];
		Matrix4();
		Matrix4(float val);
		Matrix4(float a0, float a1, float a2, float a3, 
			float b0, float b1, float b2, float b3, 
			float c0, float c1, float c2, float c3, 
			float d0, float d1, float d2, float d3);
		static Matrix4 createScalingMatrix(float sx, float sy, float sz);
		static Matrix4 createRotatingMatrix(float degrees, Vertex& axis);
		static Matrix4 createTranslatingMatrix(float tx, float ty, float tz);
		static Matrix4 multiply(float mul, Matrix4& mat);
		static Matrix4 divide(float val, Matrix4& mat);
		static Matrix4 add(Matrix4& mat1, Matrix4& mat2);
		static Matrix4 multiply(Matrix4& mat1, Matrix4& mat2);
		static Matrix4 inverse(Matrix4& mat);
		static bool invertMatrix(float m[16], float invOut[16]);
		static Matrix4 transpose(Matrix4& mat);
		static void print(Matrix4& mat);
};

#endif