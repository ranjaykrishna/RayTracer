#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <FreeImage.h>
#include <math.h>

using namespace std;  

// Main variables in the program.  
#define MAINPROGRAM
#define READFILE
#include "variables.h" 
#include "readfile.h"
#include "Sample.h"
#include "Ray.h"
#include "Color.h"
#include "Film.h"
#include "RayTracer.h"

void initColor() {
  attenuation[0] = 1; attenuation[1] = 0; attenuation[2] = 0;
  ambient[0] = .2; ambient[1] = .2; ambient[2] = .2;
  shininess = 0;
  diffuse[0] = 0; diffuse[1] = 0; diffuse[2] = 0;
  specular[0] = 0; specular[1] = 0; specular[2] = 0;
  emission[0] = 0; emission[1] = 0; emission[2] = 0;
}

int main(int argc, char* argv[]) {
  FreeImage_Initialise();
  
  Camera camera;  
  Sample sample;
  Ray ray;
  Color* color = new Color(0.f, 0.f, 0.f);

  initColor();

  readfile(argv[1], &camera);

  const float pi = 3.14159265 ;
  float fovx = 2 * atan( tan(camera.fovy * pi/180/2.f) * ((float) w) / ((float) h) ) * 180/pi;

  Film film = Film::Film(w, h);
  while (Sample::getSample(&sample, w, h)) {
      if (sample.x % 700 == 0) printf("Sample: %d, %d\n", sample.x, sample.y);
      if (sample.y < 200) continue;
      camera.generateRay(sample, &ray, w, h, fovx, camera.fovy);
      RayTracer::trace(ray, 0, color, maxdepth, numprimitives, geometricPrimitives, numused, lights, attenuation); 
      film.commit(sample, *color);
      if (sample.y > 250) break;
  }
  film.writeImage(outputFilename);

  FreeImage_DeInitialise();
  return 0;
}
