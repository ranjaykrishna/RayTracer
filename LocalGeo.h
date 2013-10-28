#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Vertex.h" 

class LocalGeo {
public:
	Vertex* pos;
	Vertex* normal;
	LocalGeo();
	LocalGeo(Vertex* _pos, Vertex* _normal);
};

#endif