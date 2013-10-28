#include <iostream>
#include "GeometricPrimitive.h"
#include "Transform.h"

GeometricPrimitive::GeometricPrimitive(Shape* s, BRDF* b, Matrix4* oTW, Matrix4* wTO) {
	shape = s;
	brdf = b;
	worldToObj = wTO;
	objToWorld = oTW;
}

bool GeometricPrimitive::intersect(Ray& ray, float* thit, LocalGeo* l, GeometricPrimitive* s)  {
    Ray oray = Transform::multiply(*worldToObj, ray);
    if (!shape->intersect(oray, thit, l))  return false;

    Vertex* pos = Transform::multiply(*objToWorld, *(l->pos));
    *l->pos = *pos;
    Matrix4 worldToObj_transpose = Matrix4::transpose(*worldToObj);
    Vertex* nor = Transform::multiply(worldToObj_transpose, *(l->normal));
    *nor = Vertex::normalize(*nor);
    *l->normal = *nor;

    *s = *this;
    return true;                               
}
 
bool GeometricPrimitive::intersectP(Ray& ray) {
    Ray oray = Transform::multiply(*worldToObj, ray);
    return shape->intersectP(oray);                        
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* b) {
    *b = *brdf;
}

GeometricPrimitive::GeometricPrimitive() {
    
}