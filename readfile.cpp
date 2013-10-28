
// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

using namespace std;
#include "variables.h" 
#include "readfile.h"
#include "Vertex.h"
#include "Camera.h"
#include "Transform.h"
#include "Shape.h"
#include "BRDF.h"
#include "GeometricPrimitive.h"
#include "Matrix4.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

#define READFILE
// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

void rightMultiply(Matrix4& mat, stack<Matrix4>& transfstack) {
  Matrix4 t = transfstack.top();
  Matrix4 mul = Matrix4::multiply(t, mat);
  transfstack.pop();
  transfstack.push(mul);
}

void readfile(const char* filename, Camera* camera) {

  stack<Matrix4> transfstack; 
  Matrix4* iden = new Matrix4::Matrix4(1.f);
  transfstack.push(*iden);

  int maxverts;
  int currverts = 0;

  maxdepth = 5;

  outputFilename = "testscenes/output.png";

  string str, cmd; 
  ifstream in;
  in.open(filename);
  if (in.is_open()) {

    getline (in, str); 
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 
        //printf("%s\n", str.c_str());
        stringstream s(str);
        s >> cmd; 
        int i; 
        float values[10]; // Position and color for light, colors for others
        // Up to 10 params for cameras.  
        bool validinput; // Validity of input 

        // Process the light, add it to database.
        // Lighting Command
        if (cmd == "directional") {
          if (numused >= numLights) { 
            cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
          } else {
            validinput = readvals(s, 6, values); // Position/color for lts.
            if (validinput) {
              Color* color = new Color(values[3], values[4], values[5]);
              Vertex v_temp = Vertex::Vertex(values[0], values[1], values[2]);
              v_temp = Vertex::normalize(v_temp);
              Vertex* v = new Vertex(-v_temp.x, -v_temp.y, -v_temp.z);
              Light* light = new Light(0, v, color);
              lights[numused] = light;
              ++numused; 
            }
          }
        }

        else if (cmd == "point") {
          if (numused >= numLights) { 
            cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
          } else {
            validinput = readvals(s, 6, values);
            if (validinput) {
              Color* color = new Color(values[3], values[4], values[5]);
              Vertex v_temp = Vertex::Vertex(values[0], values[1], values[2]);
              Vertex* v = new Vertex(v_temp.x, v_temp.y, v_temp.z);
              Light* light = new Light(1, v, color);
              lights[numused] = light;
              ++numused; 
            }
          }
        }

        else if (cmd == "maxverts") {
          validinput = readvals(s, 1, values);
          if (validinput) {
            maxverts = values[0];
          }
        }

        else if (cmd == "vertex") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            Vertex* temp = new Vertex::Vertex(values[0], values[1], values[2]);
            if (currverts < maxVertices) {
              vertices[currverts] = temp;
              currverts++;
            }
          }
        }

        else if (cmd == "tri") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            if (numprimitives < maxprimitives) {
              Shape* shape = new Shape::Shape(vertices[(int)(values[0])], vertices[(int)(values[1])], vertices[(int)(values[2])]);
              
              Color* diffuseColor = new Color::Color(diffuse[0], diffuse[1], diffuse[2]);
              Color* specularColor = new Color::Color(specular[0], specular[1], specular[2]);
              Color* ambientColor = new Color::Color(ambient[0], ambient[1], ambient[2]);
              Color* emissionColor = new Color::Color(emission[0], emission[1], emission[2]);
              BRDF* brdf = new BRDF::BRDF(diffuseColor, specularColor, ambientColor, emissionColor, shininess);
              
              Matrix4 objToWorld_temp = transfstack.top();
              Matrix4* objToWorld = new Matrix4::Matrix4(
                objToWorld_temp.mat[0][0], objToWorld_temp.mat[0][1], objToWorld_temp.mat[0][2], objToWorld_temp.mat[0][3],
                objToWorld_temp.mat[1][0], objToWorld_temp.mat[1][1], objToWorld_temp.mat[1][2], objToWorld_temp.mat[1][3],
                objToWorld_temp.mat[2][0], objToWorld_temp.mat[2][1], objToWorld_temp.mat[2][2], objToWorld_temp.mat[2][3],
                objToWorld_temp.mat[3][0], objToWorld_temp.mat[3][1], objToWorld_temp.mat[3][2], objToWorld_temp.mat[3][3]
                );
              Matrix4 worldToObj_temp = Matrix4::inverse(objToWorld_temp);
              Matrix4* worldToObj = new Matrix4::Matrix4(
                worldToObj_temp.mat[0][0], worldToObj_temp.mat[0][1], worldToObj_temp.mat[0][2], worldToObj_temp.mat[0][3],
                worldToObj_temp.mat[1][0], worldToObj_temp.mat[1][1], worldToObj_temp.mat[1][2], worldToObj_temp.mat[1][3],
                worldToObj_temp.mat[2][0], worldToObj_temp.mat[2][1], worldToObj_temp.mat[2][2], worldToObj_temp.mat[2][3],
                worldToObj_temp.mat[3][0], worldToObj_temp.mat[3][1], worldToObj_temp.mat[3][2], worldToObj_temp.mat[3][3]
                );

              GeometricPrimitive* gp = new GeometricPrimitive(shape, brdf, objToWorld, worldToObj);
              geometricPrimitives[numprimitives] = gp;
              numprimitives++;
            }
          }
        }

        else if (cmd == "maxdepth") {
          validinput = readvals(s,1,values);
          if (validinput) {
            maxdepth = values[0];
          }
        }

        else if (cmd == "output") {
          s >> outputFilename;
          cout << "OUTPUT FILENAME: ";
          cout << outputFilename;
          cout << "\n";
        }

        else if (cmd == "attenuation") {
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              attenuation[i] = values[i]; 
            }
          }
        }

        else if (cmd == "ambient") {
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              ambient[i] = values[i]; 
            }
          }
        } else if (cmd == "diffuse") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              emission[i] = values[i]; 
            }
          }
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values); 
          if (validinput) {
            shininess = values[0]; 
          }
        } else if (cmd == "size") {
          validinput = readvals(s,2,values); 
          if (validinput) { 
            w = (int) values[0]; h = (int) values[1]; 
          } 
        } else if (cmd == "camera") {
          validinput = readvals(s,10,values);
          if (validinput) {            
            Vertex* eye = new Vertex::Vertex(values[0], values[1], values[2]);
            Vertex* center = new Vertex::Vertex(values[3], values[4], values[5]);
            Vertex*  up = new Vertex::Vertex(values[6], values[7], values[8]);
            Vertex eye_center = Vertex::subtract(*eye, *center);
            Vertex upinit = Transform::upvector(*up, eye_center);
            up = new Vertex::Vertex(upinit.x, upinit.y, upinit.z);
            float fovy = values[9];

            Vertex a = Vertex::subtract(*eye, *center);
            Vertex z = Vertex::normalize(a);
            Vertex x = Vertex::cross(*up, z);
            x = Vertex::normalize(x);
            Vertex y = Vertex::cross(z, x);

            Vertex* uu = new Vertex::Vertex(x.x, x.y, x.z);
            Vertex* vv = new Vertex::Vertex(y.x, y.y, y.z);
            Vertex* ww = new Vertex::Vertex(z.x, z.y, z.z);

            Camera* c = new Camera::Camera(eye, center, up, fovy, uu, vv, ww);
            *camera = *c;
          }
        }

        else if (cmd == "sphere") {
          validinput = readvals(s,4,values); 
          if (validinput) {
            if (numprimitives < maxprimitives) {
              Vertex* center = new Vertex::Vertex(values[0], values[1], values[2]);
              Shape* shape = new Shape::Shape(center, values[3]);
              
              Color* diffuseColor = new Color::Color(diffuse[0], diffuse[1], diffuse[2]);
              Color* specularColor = new Color::Color(specular[0], specular[1], specular[2]);
              Color* ambientColor = new Color::Color(ambient[0], ambient[1], ambient[2]);
              Color* emissionColor = new Color::Color(emission[0], emission[1], emission[2]);
              
              BRDF* brdf = new BRDF::BRDF(diffuseColor, specularColor, ambientColor, emissionColor, shininess);
              
              Matrix4 objToWorld_temp = transfstack.top();
              Matrix4* objToWorld = new Matrix4::Matrix4(
                objToWorld_temp.mat[0][0], objToWorld_temp.mat[0][1], objToWorld_temp.mat[0][2], objToWorld_temp.mat[0][3],
                objToWorld_temp.mat[1][0], objToWorld_temp.mat[1][1], objToWorld_temp.mat[1][2], objToWorld_temp.mat[1][3],
                objToWorld_temp.mat[2][0], objToWorld_temp.mat[2][1], objToWorld_temp.mat[2][2], objToWorld_temp.mat[2][3],
                objToWorld_temp.mat[3][0], objToWorld_temp.mat[3][1], objToWorld_temp.mat[3][2], objToWorld_temp.mat[3][3]
                );
              Matrix4 worldToObj_temp = Matrix4::inverse(objToWorld_temp);
              Matrix4* worldToObj = new Matrix4::Matrix4(
                worldToObj_temp.mat[0][0], worldToObj_temp.mat[0][1], worldToObj_temp.mat[0][2], worldToObj_temp.mat[0][3],
                worldToObj_temp.mat[1][0], worldToObj_temp.mat[1][1], worldToObj_temp.mat[1][2], worldToObj_temp.mat[1][3],
                worldToObj_temp.mat[2][0], worldToObj_temp.mat[2][1], worldToObj_temp.mat[2][2], worldToObj_temp.mat[2][3],
                worldToObj_temp.mat[3][0], worldToObj_temp.mat[3][1], worldToObj_temp.mat[3][2], worldToObj_temp.mat[3][3]
                );

              GeometricPrimitive* gp = new GeometricPrimitive(shape, brdf, objToWorld, worldToObj);
              geometricPrimitives[numprimitives] = gp;
              numprimitives++;
            }
          }
        }

        else if (cmd == "translate") {
          validinput = readvals(s, 3, values);
          if (validinput) {
            Matrix4 tr = Matrix4::createTranslatingMatrix(values[0], values[1], values[2]);
            rightMultiply(tr, transfstack);
          }
        }

        else if (cmd == "scale") {
          validinput = readvals(s, 3, values);
          if (validinput) {
            Matrix4 sc = Matrix4::createScalingMatrix(values[0], values[1], values[2]);
            rightMultiply(sc, transfstack);
          }
        }

        else if (cmd == "rotate") {
          validinput = readvals(s, 4, values);
          if (validinput) {
            Vertex axis = Vertex::Vertex(values[0], values[1], values[2]);
            Matrix4 R = Matrix4::createRotatingMatrix(values[3], axis);
            rightMultiply(R, transfstack);
          }
        }

        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        }
        
        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n"; 
        }
      }
      getline (in, str); 
    }

  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n"; 
    throw 2; 
  }
}
