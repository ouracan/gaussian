
#include "header.h"


const int WINDOWS_WIDTH = 1280;
const int WINDOWS_HEIGHT = 720;

GLfloat alpha =210.0f, beta=-70.0f,zoom=4.0f;

    
      
int main(void)
{
  GLFWwindow* window;
  int width, height;


  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "Primitive Drawings", NULL, NULL);

  if(!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  
  //handle window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // get the window size

  glfwGetFramebufferSize(window, &width, &height);

  //initialze openGl camera
  framebuffer_size_callback(window, width, height);

  //Enable anti-aliasing and smoothing
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);



  //for alpha blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);


  //initialize paramters to be used ensuite
  float sigma = 0.1f;
  float sign = 1.0f;
  float step_size = 0.01f;


 

  
  while(!glfwWindowShouldClose(window))
    {
     
      //set up perspective rendering

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.0f,0.0f,0.0f,1.0f);

      //draw the scene, switch to modelview, so transformation applies to the entire model
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0,0.0,-zoom);
      glRotatef(beta,1.0,0.0,0.0);
      glRotatef(alpha,0.0,0.0,1.0);

      //draw the 3 axis at corner / center
      drawGnome();

      
      sigma = sigma+sign*step_size;
      if(sigma>1.0f){

  
	sign = -1.0f;
      }
      if(sigma<0.1f){
	sign = 1.0f;
      }
      gaussian(sigma);
   

      //swap the front and back buffers of the window and process event queue
      //such as IO to avoid lock-up

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  //release the memory and termiante the GLFW library

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
