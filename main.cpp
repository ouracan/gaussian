
#include "header.h"


const int WINDOWS_WIDTH = 1920;
const int WINDOWS_HEIGHT = 1080;

GLfloat alpha =210.0f, beta=-70.0f,zoom=2.0f;
float sigma = 0.1f;
float sign = 1.0f;
float step_size = 0.01f;

    
      
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
  glfwSwapInterval(1);

  //Enable anti-aliasing and smoothing

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glEnable(GL_BLEND);

  //for alpha blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);


  // initialize parameters for perspective rendering

  //Define loop which terminates when the window is closed.
  //and Set up viewport using the size of the window and clear color buffer



  
  while(!glfwWindowShouldClose(window))
    {
      float ratio;
      
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      framebuffer_size_callback(window, width, height);
      ratio = (float)width / (float)height;
      glViewport(0,0,width,height);
      glClear(GL_COLOR_BUFFER_BIT);

      //set up perspective rendering

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(1.0f,1.0f,1.0f,1.0f);


      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0,0.0,-2.0);
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
