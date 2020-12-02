
#include "header.h"


const int WINDOWS_WIDTH = 640;
const int WINDOWS_HEIGHT = 640;



    
      
int main(void)
{
  GLFWwindow* window;
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "Primitive Drawings", NULL, NULL);

  if(!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  //Enable anti-aliasing and smoothing

  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Define loop which terminates when the window is closed.
  //and Set up viewport using the size of the window and clear color buffer


  float sigma = 0.0f;
  
  while(!glfwWindowShouldClose(window))
    {
      float ratio;
      
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      ratio = (float)width / (float)height;
      glViewport(0,0,width,height);
      glClear(GL_COLOR_BUFFER_BIT);

      //set up orthographic projection

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      
      sigma+=0.01f;
      if(sigma>1.0f)
	sigma=0.01f;
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
