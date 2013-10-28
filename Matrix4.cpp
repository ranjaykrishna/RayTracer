#include <iostream>
#include <math.h>
#include "Matrix4.h"
 
Matrix4::Matrix4() {
	mat[0][0] = 1.f;
	mat[0][1] = 0.f;
	mat[0][2] = 0.f;
	mat[0][3] = 0.f;
	mat[1][0] = 0.f;
	mat[1][1] = 1.f;
	mat[1][2] = 0.f;
	mat[1][3] = 0.f;
	mat[2][0] = 0.f;
	mat[2][1] = 0.f;
	mat[2][2] = 1.f;
	mat[2][3] = 0.f;
	mat[3][0] = 0.f;
	mat[3][1] = 0.f;
	mat[3][2] = 0.f;
	mat[3][3] = 1.f;
}

Matrix4::Matrix4(float val) {
	mat[0][0] = val;
	mat[0][1] = 0.f;
	mat[0][2] = 0.f;
	mat[0][3] = 0.f;
	mat[1][0] = 0.f;
	mat[1][1] = val;
	mat[1][2] = 0.f;
	mat[1][3] = 0.f;
	mat[2][0] = 0.f;
	mat[2][1] = 0.f;
	mat[2][2] = val;
	mat[2][3] = 0.f;
	mat[3][0] = 0.f;
	mat[3][1] = 0.f;
	mat[3][2] = 0.f;
	mat[3][3] = val;
}

Matrix4::Matrix4(float a0, float a1, float a2, float a3, 
			float b0, float b1, float b2, float b3, 
			float c0, float c1, float c2, float c3, 
			float d0, float d1, float d2, float d3) {
	mat[0][0] = a0;
	mat[0][1] = a1;
	mat[0][2] = a2;
	mat[0][3] = a3;
	mat[1][0] = b0;
	mat[1][1] = b1;
	mat[1][2] = b2;
	mat[1][3] = b3;
	mat[2][0] = c0;
	mat[2][1] = c1;
	mat[2][2] = c2;
	mat[2][3] = c3;
	mat[3][0] = d0;
	mat[3][1] = d1;
	mat[3][2] = d2;
	mat[3][3] = d3;
}

void Matrix4::print(Matrix4& mat) {
	printf("MATRIX: %f, %f, %f, %f || %f, %f, %f, %f || %f, %f, %f, %f || %f, %f, %f, %f.\n", 
		mat.mat[0][0], mat.mat[0][1], mat.mat[0][2], mat.mat[0][3],
		mat.mat[1][0], mat.mat[1][1], mat.mat[1][2], mat.mat[1][3],
		mat.mat[2][0], mat.mat[2][1], mat.mat[2][2], mat.mat[2][3],
		mat.mat[3][0], mat.mat[3][1], mat.mat[3][2], mat.mat[3][3]);
}

Matrix4 Matrix4::createScalingMatrix(float sx, float sy, float sz) {
	Matrix4* mat = new Matrix4();
	mat->mat[0][0] = sx;
	mat->mat[1][1] = sy;
	mat->mat[2][2] = sz;
	return *mat;
}

Matrix4 Matrix4::createTranslatingMatrix(float tx, float ty, float tz) {
	Matrix4* mat = new Matrix4();
	mat->mat[0][3] = tx;
	mat->mat[1][3] = ty;
	mat->mat[2][3] = tz;
	return *mat;
}

Matrix4 Matrix4::multiply(float mul, Matrix4& mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat.mat[i][j] = mul * mat.mat[i][j];
		}
	}
	return mat;
}

Matrix4 Matrix4::divide(float val, Matrix4& mat) {
	if (val == 0) {
		return mat;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat.mat[i][j] = mat.mat[i][j] / val;
		}
	}
	return mat;
}

Matrix4 Matrix4::transpose(Matrix4& mat) {
	Matrix4* ret = new Matrix4();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret->mat[i][j] = mat.mat[j][i];
		}
	}
	return *ret;
}

Matrix4 Matrix4::add(Matrix4& mat1, Matrix4& mat2) {
	Matrix4* mat = new Matrix4();
	mat->mat[0][0] = mat1.mat[0][0] + mat2.mat[0][0];
	mat->mat[0][1] = mat1.mat[0][1] + mat2.mat[0][1];
	mat->mat[0][2] = mat1.mat[0][2] + mat2.mat[0][2];
	mat->mat[0][3] = mat1.mat[0][3] + mat2.mat[0][3];
	mat->mat[1][0] = mat1.mat[1][0] + mat2.mat[1][0];
	mat->mat[1][1] = mat1.mat[1][1] + mat2.mat[1][1];
	mat->mat[1][2] = mat1.mat[1][2] + mat2.mat[1][2];
	mat->mat[1][3] = mat1.mat[1][3] + mat2.mat[1][3];
	mat->mat[2][0] = mat1.mat[2][0] + mat2.mat[2][0];
	mat->mat[2][1] = mat1.mat[2][1] + mat2.mat[2][1];
	mat->mat[2][2] = mat1.mat[2][2] + mat2.mat[2][2];
	mat->mat[2][3] = mat1.mat[2][3] + mat2.mat[2][3];
	mat->mat[3][0] = mat1.mat[3][0] + mat2.mat[3][0];
	mat->mat[3][1] = mat1.mat[3][1] + mat2.mat[3][1];
	mat->mat[3][2] = mat1.mat[3][2] + mat2.mat[3][2];
	mat->mat[3][3] = mat1.mat[3][3] + mat2.mat[3][3];
	return *mat;
}

Matrix4 Matrix4::createRotatingMatrix(float degrees, Vertex& ax) {
	Vertex axis = Vertex::normalize(ax);
    float rad = -degrees * pi/180;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    Matrix4 temp = Matrix4(
    	x*x, x*y, x*z, 0.f, 
    	y*x, y*y, y*z, 0.f, 
    	z*x, z*y, z*z, 0.f, 
    	0.f, 0.f, 0.f, 0.f);
    Matrix4 temp2 = Matrix4(
    	0.f, z, -y, 0.f, 
    	-z, 0.f, x, 0.f, 
    	y, -x, 0.f, 0.f, 
    	0.f, 0.f, 0.f, 0.f);

    Matrix4 part1 = Matrix4((float)(cos(rad)));  
    Matrix4 part2 = multiply((float)(1.f - cos(rad)), temp);
    Matrix4 part3 = multiply((float)(sin(rad)), temp2);

    Matrix4 temp3 = add(part1, part2);
    Matrix4 R = add(temp3, part3);
    R.mat[3][3] = 1.f;
    return R;
}

Matrix4 Matrix4::multiply(Matrix4& mat1, Matrix4& mat2) {
	float a0 = mat1.mat[0][0]*mat2.mat[0][0] + mat1.mat[0][1]*mat2.mat[1][0] + mat1.mat[0][2]*mat2.mat[2][0] + mat1.mat[0][3]*mat2.mat[3][0];
	float a1 = mat1.mat[0][0]*mat2.mat[0][1] + mat1.mat[0][1]*mat2.mat[1][1] + mat1.mat[0][2]*mat2.mat[2][1] + mat1.mat[0][3]*mat2.mat[3][1];
	float a2 = mat1.mat[0][0]*mat2.mat[0][2] + mat1.mat[0][1]*mat2.mat[1][2] + mat1.mat[0][2]*mat2.mat[2][2] + mat1.mat[0][3]*mat2.mat[3][2];
	float a3 = mat1.mat[0][0]*mat2.mat[0][3] + mat1.mat[0][1]*mat2.mat[1][3] + mat1.mat[0][2]*mat2.mat[2][3] + mat1.mat[0][3]*mat2.mat[3][3];
	
	float b0 = mat1.mat[1][0]*mat2.mat[0][0] + mat1.mat[1][1]*mat2.mat[1][0] + mat1.mat[1][2]*mat2.mat[2][0] + mat1.mat[1][3]*mat2.mat[3][0];
	float b1 = mat1.mat[1][0]*mat2.mat[0][1] + mat1.mat[1][1]*mat2.mat[1][1] + mat1.mat[1][2]*mat2.mat[2][1] + mat1.mat[1][3]*mat2.mat[3][1];
	float b2 = mat1.mat[1][0]*mat2.mat[0][2] + mat1.mat[1][1]*mat2.mat[1][2] + mat1.mat[1][2]*mat2.mat[2][2] + mat1.mat[1][3]*mat2.mat[3][2];
	float b3 = mat1.mat[1][0]*mat2.mat[0][3] + mat1.mat[1][1]*mat2.mat[1][3] + mat1.mat[1][2]*mat2.mat[2][3] + mat1.mat[1][3]*mat2.mat[3][3];
	
	float c0 = mat1.mat[2][0]*mat2.mat[0][0] + mat1.mat[2][1]*mat2.mat[1][0] + mat1.mat[2][2]*mat2.mat[2][0] + mat1.mat[2][3]*mat2.mat[3][0];
	float c1 = mat1.mat[2][0]*mat2.mat[0][1] + mat1.mat[2][1]*mat2.mat[1][1] + mat1.mat[2][2]*mat2.mat[2][1] + mat1.mat[2][3]*mat2.mat[3][1];
	float c2 = mat1.mat[2][0]*mat2.mat[0][2] + mat1.mat[2][1]*mat2.mat[1][2] + mat1.mat[2][2]*mat2.mat[2][2] + mat1.mat[2][3]*mat2.mat[3][2];
	float c3 = mat1.mat[2][0]*mat2.mat[0][3] + mat1.mat[2][1]*mat2.mat[1][3] + mat1.mat[2][2]*mat2.mat[2][3] + mat1.mat[2][3]*mat2.mat[3][3];
	
	float d0 = mat1.mat[3][0]*mat2.mat[0][0] + mat1.mat[3][1]*mat2.mat[1][0] + mat1.mat[3][2]*mat2.mat[2][0] + mat1.mat[3][3]*mat2.mat[3][0];
	float d1 = mat1.mat[3][0]*mat2.mat[0][1] + mat1.mat[3][1]*mat2.mat[1][1] + mat1.mat[3][2]*mat2.mat[2][1] + mat1.mat[3][3]*mat2.mat[3][1];
	float d2 = mat1.mat[3][0]*mat2.mat[0][2] + mat1.mat[3][1]*mat2.mat[1][2] + mat1.mat[3][2]*mat2.mat[2][2] + mat1.mat[3][3]*mat2.mat[3][2];
	float d3 = mat1.mat[3][0]*mat2.mat[0][3] + mat1.mat[3][1]*mat2.mat[1][3] + mat1.mat[3][2]*mat2.mat[2][3] + mat1.mat[3][3]*mat2.mat[3][3];

	Matrix4* ret = new Matrix4(a0, a1, a2, a3, 
			b0, b1, b2, b3, 
			c0, c1, c2, c3, 
			d0, d1, d2, d3);
	return *ret;
}

/*
float product3(mat& mat, int x0, int y0, int x1, int y1, int x2, int y2) {
	return mat.mat[x0-1][y1-1] * mat.mat[x1-1][y1-1] * mat.mat[x2-1][y2-1];
}

float product4(mat& mat, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	return mat.mat[x0-1][y1-1] * mat.mat[x1-1][y1-1] * mat.mat[x2-1][y2-1] * mat.mat[x3-1][y3-1];
}
*/

Matrix4 Matrix4::inverse(Matrix4& mat) {
	/*float det = product3(mat,1,1,2,2,3,3,4,4) + product3(mat,1,1,2,3,3,4,4,2) + product3(mat,1,1,2,4,3,2,4,3)
			  + product3(mat,1,2,2,1,3,4,4,3) + product3(mat,1,2,2,3,3,1,4,4) + product3(mat,1,2,2,4,3,3,4,1)
			  + product3(mat,1,3,2,1,3,2,4,4) + product3(mat,1,3,2,2,3,4,4,1) + product3(mat,1,3,2,4,3,1,4,2)
			  + product3(mat,1,4,2,1,3,3,4,2) + product3(mat,1,4,2,2,3,1,4,3) + product3(mat,1,4,2,3,3,2,4,1)

			  - product3(mat,1,1,2,2,3,4,4,3) - product3(mat,1,1,2,3,3,2,4,4) - product3(mat,1,1,2,4,3,3,4,2)
			  - product3(mat,1,2,2,1,3,3,4,4) - product3(mat,1,2,2,3,3,4,4,1) - product3(mat,1,2,2,4,3,1,4,3)
			  - product3(mat,1,3,2,1,3,4,4,2) - product3(mat,1,3,2,2,3,1,4,4) - product3(mat,1,3,2,4,3,2,4,1)
			  - product3(mat,1,4,2,1,3,2,4,3) - product3(mat,1,4,2,2,3,3,4,1) - product3(mat,1,4,2,3,3,1,4,2);
	*/

	float m[16];
	float inv[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i + 4*j] = mat.mat[i][j];
		}
	}
	bool inverted = invertMatrix(m, inv);
	Matrix4* ret = new Matrix4::Matrix4();
	if (inverted) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret->mat[i][j] = inv[i + 4*j];
			}
		}
	}
	return *ret;
}

bool Matrix4::invertMatrix(float m[16], float invOut[16])
{
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}