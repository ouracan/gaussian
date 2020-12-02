#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#endif

#define _USE_MATH_DEFINES // M_PI constant


#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>

#pragma once

struct Data;

void drawheatmap(const Data *data, int num_points);

void gaussian(float sigma);



  
