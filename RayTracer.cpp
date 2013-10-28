#include <math.h>
#include <algorithm>
#include <iostream>
#include "RayTracer.h"
#include "LocalGeo.h"
#include "BRDF.h"

void setColor(Color* color, Color& ret) {
      color->r = ret.r;
      color->g = ret.g;
      color->b = ret.b;
}

void addColor(Color* color, Color& ret) {
      color->r = color->r + ret.r;
      color->g = color->g + ret.g;
      color->b = color->b + ret.b;     
}

bool RayTracer::getIntersect(
      Ray& ray,
      float* thit,
      LocalGeo* localGeo, 
      GeometricPrimitive* primitive, 
      int numPrimitives, 
      GeometricPrimitive* primitives[],
      int* primitiveIndex) {

      *thit = 10000;
      float t_temp;
      LocalGeo l_temp;
      GeometricPrimitive primitive_temp;
      bool ret = false;

      for (int i = 0; i < numPrimitives; i++) {
            int num_int = 0;
            GeometricPrimitive* p = *(primitives + i);
            if (p->intersect(ray, &t_temp, &l_temp, &primitive_temp)) {
                  if (t_temp < *thit) {
                        *thit = t_temp;
                        *localGeo = l_temp;
                        *primitive = primitive_temp;
                        *primitiveIndex = i;
                  }
                  ret = true;
            }
      }
      return ret;
}

bool RayTracer::getIntersectP(Ray& ray, int numPrimitives, GeometricPrimitive* primitives[], int primitiveIndex) {
      for (int i = 0; i < numPrimitives; i++) {
            GeometricPrimitive* p = *(primitives + i);
            if (p->intersectP(ray)) {
            //if (i != primitiveIndex && p->intersectP(ray)) {
                  return true;
            }
      }
      return false;
}

Color timesVertex(Color& color, Vertex& vertex) {
      Color* c = new Color::Color(
            color.r * vertex.x,
            color.g * vertex.y,
            color.b * vertex.z
            );
      return *c;
}

Color timesColor(Color& color, Color& vertex) {
      Color* c = new Color::Color(
            color.r * vertex.r,
            color.g * vertex.g,
            color.b * vertex.b
            );
      return *c;
}

Color timesScalar(Color& color, float val) {
      Color* c = new Color::Color(
            color.r * val,
            color.g * val,
            color.b * val
            );
      return *c;
}

Color ComputeLight (Vertex& direction, Color& lightcolor, Vertex& normal, Vertex& halfvec, Color& mydiffuse, Color& myspecular, float myshininess) {

        float nDotL = Vertex::dot(normal, direction)  ;
        nDotL = std::max(nDotL, 0.f);
        Color lambert_temp = timesColor(lightcolor, mydiffuse);       
        Color lambert = timesScalar(lambert_temp, nDotL);  

        float nDotH = Vertex::dot(normal, halfvec) ; 
        nDotH = std::max(nDotH, 0.f);
        Color phong_temp = timesColor(lightcolor, myspecular);
        Color phong = timesScalar(phong_temp, pow(nDotH, myshininess)); 

        // printf("NORMAL: %f, %f, %f.\n", normal.x, normal.y, normal.z);
        // printf("DIRECTION: %f, %f, %f.\n", direction.x, direction.y, direction.z);
        // printf("nDOTL: %f, nDOTH: %f\n", nDotL, nDotH);
        // printf("PHONG: %f, %f, %f.\n", phong.r, phong.g, phong.b);
        // printf("LAMBERT: %f, %f, %f.\n", lambert.r, lambert.g, lambert.b);

        Color* retval = new Color::Color(
            lambert.r + phong.r,
            lambert.g + phong.g,
            lambert.b + phong.b); 
        return *retval ;            
}  

Color shading(Ray& ray, LocalGeo& localGeo, BRDF& brdf, Ray& lray, Color& lcolor) {
      Vertex direction = *lray.dir;
      Vertex normal = *localGeo.normal;
      Vertex half_temp = Vertex::subtract(*lray.dir, *ray.dir);
      Vertex halfvec = Vertex::normalize(half_temp);
      Color ret = ComputeLight(direction, lcolor, normal, halfvec, *brdf.kd, *brdf.ks, brdf.shininess);
      return ret;
}

Ray createReflectRay(LocalGeo& localGeo, Ray& ray) {
      Vertex* pos = new Vertex::Vertex(localGeo.pos->x, localGeo.pos->y, localGeo.pos->z);

      Vertex normal = Vertex::Vertex(localGeo.normal->x, localGeo.normal->y, localGeo.normal->z);
      float mul = 2 * Vertex::dot(*ray.dir, normal);
      Vertex ri_c = Vertex::multiply(mul, normal);
      Vertex ri = Vertex::subtract(*ray.dir, ri_c);
      ri = Vertex::normalize(ri);
      Vertex* dir = new Vertex::Vertex(ri.x, ri.y, ri.z);
      Ray* new_ray = new Ray::Ray(pos, dir, ray.t_min, ray.t_max);
      return *new_ray;
}

void RayTracer::trace(
      Ray& ray, 
      int depth, 
      Color* color, 
      int maxdepth, 
      int numPrimitives, 
      GeometricPrimitive* primitives[],
      int numused,
      Light* lights[],
      float attenuation[]
      ) {

      if (depth > maxdepth) {
            Color ret = Color::Color(0.f, 0.f, 0.f);
            setColor(color, ret);
            return;
      }
      float thit;
      LocalGeo localGeo;
      GeometricPrimitive primitive;
      BRDF brdf;
      int primitiveIndex;
      if (!getIntersect(ray, &thit, &localGeo, &primitive, numPrimitives, primitives, &primitiveIndex)) {
            Color ret = Color::Color(0.f, 0.f, 0.f);
            setColor(color, ret);
            return;
      }
      // Obtain the brdf at intersection point
      primitive.getBRDF(localGeo, &brdf);
      Color ret = Color::Color(0.f,0.f,0.f);
      setColor(color, ret);

      // There is an intersection, loop through all light source
      for (int i = 0; i < numused; i++) {
            Ray lray;
            Color lcolor;
            Light* light = *(lights + i);
            light->generateLightRay(localGeo, &lray, &lcolor);
           
            // Check if the light is blocked or not
            if (!getIntersectP(lray, numPrimitives, primitives, primitiveIndex)) {
                  // If not, do shading calculation for this
                  // light source
                  Color shade = shading(ray, localGeo, brdf, lray, lcolor);
                  float attenuatedValue = 1.f;
                  if (light->type == 1) {
                       Vertex distance = Vertex::subtract(*localGeo.pos, *light->pos);
                       float dist = sqrt(pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2));
                       attenuatedValue = 1.f/(attenuation[0] + attenuation[1] * dist + attenuation[2] * dist * dist);
                  }
                  Color attenuatedColor = timesScalar(shade, attenuatedValue);
                  addColor(color, attenuatedColor);
            }
      }
      addColor(color, *brdf.ka);
      addColor(color, *brdf.ke);
      
      // Handle mirror reflection
      if (brdf.ks->r > 0 || brdf.ks->g > 0 || brdf.ks->b > 0) {
            Ray reflectRay = createReflectRay(localGeo, ray);
            Color tempColor;
            // Make a recursive call to trace the reflected ray
            trace(reflectRay, 
                  depth+1, 
                  &tempColor,
                  maxdepth, 
                  numPrimitives, 
                  primitives,
                  numused,
                  lights,
                  attenuation);
            Color reflectColor = timesColor(tempColor, *brdf.ks);
            addColor(color, reflectColor);
      }
}