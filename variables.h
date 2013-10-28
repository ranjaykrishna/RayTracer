/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  
#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#include "Camera.h"
#include "Vertex.h"
#include "Light.h"
#include "GeometricPrimitive.h"

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif 

#ifdef MAINPROGRAM
int w = 600, h = 400 ; // width and height
float shininess;
float ambient[3];
float diffuse[3];
float specular[3];
float emission[3];
float attenuation[3];
#else
EXTERN int w, h ;
EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float attenuation[3];
EXTERN float shininess;
#endif 

EXTERN string outputFilename;

const int maxVertices = 50010;
EXTERN Vertex* vertices[maxVertices];

const int numLights = 100 ; 
EXTERN Light* lights[4*numLights]; 
EXTERN int numused; 

const int maxprimitives = 1001;
EXTERN GeometricPrimitive* geometricPrimitives[maxprimitives];
EXTERN int numprimitives;

EXTERN int maxdepth;

#endif