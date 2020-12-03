#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#endif

#define _USE_MATH_DEFINES // M_PI constant


#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <math.h>

#pragma once

struct Data;

void drawheatmap(const Data *data, int num_points);

void gaussian(float sigma);

// camera parameters depend on the window size, first implement a callback function that handles a window resize event and updates the matrices.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void drawGnome();

  
