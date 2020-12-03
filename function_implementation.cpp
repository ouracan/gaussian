#include "header.h"






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
  glPointSize(3.0f);
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
      glColor4f(r,g,b,0.25f);
      glVertex3f(d.x,d.y,d.z); //inefficient
    }
  glEnd();
}

void gaussian(float sigma)
{

  const int grid_x = 400;
  const int grid_y = 400;
  const int num_points = grid_x * grid_y;
  Data *data = (Data*)malloc(sizeof(Data)*num_points);
  int data_counter = 0;

  //standard deviation
  const float sigma2 = sigma*sigma;

  //amplitude
  const float sigma_const = 10.0f*(sigma*2.0f*(float)M_PI);

  
  for ( int x = -grid_x /2.0f; x<grid_x/2.0f;x+=1.0f ){
    for ( int y = -grid_y/2.0f; y<grid_y/2.0f; y+=1.0f){
      float x_data = 2.0f *  x/grid_x;
      float y_data = 2.0f * y/grid_y;
      

      //set the mean to 0,compute the height z based on a 2D gaussian function
      float z_data = exp(-0.5f*(x_data*x_data)/(sigma2) -0.5f*(y_data*y_data)/(sigma*sigma))/sigma_const;
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  const float fovY = 45.0f;
  const float front = 0.1f;
  const float back = 128.0f;
  float ratio = 1.0f;
  if (height < 0){
    ratio = (float)width / (float)height;
  }

    //set up the viewport of the virtual camera (using the window size)
    glViewport(0,0,width,height);

    //specify the matrix mode as GL_PROJECTION and allow subsequent matrix operation to be applied to the projection matrix stack
    glMatrixMode(GL_PROJECTION);

    //load the identity matrix (reset the matrix to default state)
    glLoadIdentity();

    //set up the perspective projection matrix for the virtual camera
    gluPerspective(fovY, ratio, front, back);

}

void drawGnome(){
  glLineWidth(4.0f);
  glBegin(GL_LINES);


  //draw a red line for the x-aixs
  glColor4f(1.0f,0.0f,0.0f,0.5f);
  glVertex3f(0.0f,0.0f,0.0f);
  glColor4f(1.0f,0.0f,0.0f,0.5f);
  glVertex3f(0.3f,0.0f,0.0f);

    //draw a green line for the x-aixs
  glColor4f(0.0f,1.0f,0.0f,0.5f);
  glVertex3f(0.0f,0.0f,0.0f);
  glColor4f(0.0f,1.0f,0.0f,0.5f);
  glVertex3f(0.f,0.0f,0.3f);

    //draw a bleu line for the x-aixs
  glColor4f(0.0f,0.0f,1.0f,0.5f);
  glVertex3f(0.0f,0.0f,0.0f);
  glColor4f(1.0f,0.0f,1.0f,0.5f);
  glVertex3f(0.0f,0.3f,0.0f);


}
