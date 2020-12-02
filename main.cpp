#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#endif

#define _USE_MATH_DEFINES // M_PI constant


#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>



const int WINDOWS_WIDTH = 640;
const int WINDOWS_HEIGHT = 640;


struct Data
{
  GLfloat x,y,z;
};



void drawheatmap(const Data *data, int num_points)
{
  //locate the maximum and minimum values in the dataset
  float max_value = -999.9f;
  float min_value = 999.9f;
  for ( int i = 0; i < num_points; i++){
    const Data d = data[i];
    //clamp max / min value
    if (d.z > max_value){
      max_value = d.z;
    }
    if(d.z < min_value){
      min_value = d.z;
    }
  }
  const float halfmax = (max_value+min_value)/2;

  //display result
  glPointSize(2.0f);
  glBegin(GL_POINTS);

  for(int i = 0; i<num_points; i++)
    {
      const Data d = data[i];
      float value = d.z;
      float b = 1.0f - value/halfmax; 
      float r = value/halfmax - 1.0f; 
      if(b<0){
	b=0;
      }
      if(r<0){
	r=0;
      }
      float g= 1.0f - b -r;
      glColor4f(r,g,b,0.5f);
      glVertex3f(d.x,d.y,0.0f); //inefficient
    }
  glEnd();
}

void gaussian(float sigma)
{
  //construct a 1000 x 1000 grid
  const int grid_x = 1000;
  const int grid_y = 1000;
  const int num_points = grid_x * grid_y;
  Data *data = (Data*)malloc(sizeof(Data)*num_points);
  int data_counter = 0;
  for ( int x = -grid_x /2; x<grid_x/2;x+=1 ){
    for ( int y = -grid_y/2; y<grid_y/2; y+=1){
      float x_data = 2.0f *  x/grid_x;
      float y_data = 2.0f * y/grid_y;

      //compute the height z based on a 2D gaussian function
      float z_data = exp(-0.5f*(x_data*x_data)/(sigma*sigma) -0.5f*(y_data*y_data)/(sigma*sigma))/(sigma*sigma*2.0f*M_PI);
      data[data_counter].x = x_data;
      data[data_counter].y = y_data;
      data[data_counter].z = z_data;
      data_counter++;
    }
  }
  //visualize the result using a 2D heat map
  drawheatmap(data, num_points);
  free(data);
}



    
      
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
