/* Douglas Buckley
   Professor Phillilps
   CS-330-T4213
   April 21, 2023*/

#include <iostream>
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <corecrt_math_defines.h>
#include <cmath>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/GLU.h>


#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

// Constructor
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

// Set dimentions for window and assign them to width and height
const unsigned int width = 1240;
const unsigned int height = 1080;

Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

// Vertice Coordinates
GLfloat vertices[] =
{ //     COORDINATES		 /        COLORS		  /   TexCoord  /     Normals   //
	// Rectangular Prism
//							   6---------7
// Front Upper Left 2		 / |       / |
// Front Upper Right 3		2---------3  |
// Back Lower Left 4		|  |      |  |
// Back Lower Right 5		|  4------|--5
// Back Upper Left 6		|/        |/
// Back Upper Right 7		0---------1

							// Front
	-0.25f, -1.00f,   0.25f,     1.00f, 0.00f, 0.00f,	0.0f, 0.0f,		0.8f, 0.5f, 0.0f, // Front Lower Left 0		    
	 0.25f, -1.00f,   0.25f,     0.00f, 1.00f, 0.00f,	0.9f, 0.0f,		0.8f, 0.5f, 0.0f, // Front Lower Right 1		  
	-0.25f,  1.00f,   0.25f,     0.00f, 0.00f, 1.00f,	0.0f, 1.0f,		0.8f, 1.0f, 0.0f, // Front Upper Left 2		 
	 0.25f,  1.00f,   0.25f,     1.00f, 1.00f, 0.00f,	0.9f, 1.0f,		0.8f, 1.0f, 0.0f, // Front Upper Right 3	

							// Back
	-0.25f, -1.00f,   0.15f,     1.00f, 0.00f, 1.00f,	0.9f, 0.0f,		0.0f, 0.5f,-0.8f, // Back Lower Left 4		
	 0.25f, -1.00f,   0.15f,     0.00f, 1.00f, 1.00f,	0.0f, 0.0f,		0.0f, 0.5f,-0.8f, // Back Lower Right 5		
	-0.25f,  1.00f,   0.15f,     1.00f, 1.00f, 1.00f,	0.9f, 1.0f,		0.0f, 0.5f,-0.8f, // Back Upper Left 6		
	 0.25f,  1.00f,   0.15f,     1.00f, 0.50f, 0.25f,	0.0f, 1.0f,		0.0f, 0.5f,-0.8f, // Back Upper Right 7		

							// Right
	 0.25f, -1.00f,   0.25f,     0.00f, 1.00f, 0.00f,	0.0f, 0.0f,		0.8f, 0.5f, -0.8f, // Front Lower Right 8		  
	 0.25f,  1.00f,   0.25f,     1.00f, 1.00f, 0.00f,	0.0f, 1.0f,		0.8f, 0.5f, -0.8f, // Front Upper Right 9	
	 0.25f, -1.00f,   0.15f,     0.00f, 1.00f, 1.00f,	0.9f, 0.0f,		0.8f, 0.5f, -0.8f, // Back Lower Right 10		
	 0.25f,  1.00f,   0.15f,     1.00f, 0.50f, 0.25f,	0.9f, 1.0f,		0.8f, 0.5f, -0.8f, // Back Upper Right 11		

							// Left
	-0.25f, -1.00f,   0.25f,     1.00f, 0.00f, 0.00f,	0.0f, 0.0f,	   -0.8f, 0.5f, 0.0f, // Front Lower Left 12    
	-0.25f,  1.00f,   0.25f,     0.00f, 0.00f, 1.00f,	0.0f, 1.0f,	   -0.8f, 0.5f, 0.0f, // Front Upper Left 13		 
	-0.25f, -1.00f,   0.15f,     1.00f, 0.00f, 1.00f,	0.0f, 0.0f,	   -0.8f, 0.5f, 0.0f, // Back Lower Left 14	
	-0.25f,  1.00f,   0.15f,     1.00f, 1.00f, 1.00f,	0.0f, 1.0f,	   -0.8f, 0.5f, 0.0f, // Back Upper Left 15		

	 // Top Front Circle
	 0.0000f, 1.0000f, 0.25f,    1.00f, 0.00f, 0.00f,	0.5000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 16	Center Vertex, start of Triangle Fan

	 0.2500f, 1.0000f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 17	Start of triangle fan
	 0.2415f, 1.0647f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.8f, 0.5f, 0.0f, // 18
	 0.2165f, 1.1250f, 0.25f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.8f, 0.5f, 0.0f, // 19
	 0.1768f, 1.1768f, 0.25f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.8f, 0.5f, 0.0f, // 20 
	 0.1250f, 1.2165f, 0.25f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.8f, 0.5f, 0.0f, // 21
	 0.0647f, 1.2415f, 0.25f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.8f, 0.5f, 0.0f, // 22 
	 0.0000f, 1.2500f, 0.25f,    1.00f, 0.50f, 0.25f,	0.0000f, 1.0000f,	0.8f, 0.5f, 0.0f, // 23	Top of Circle
	-0.0647f, 1.2415f, 0.25f,    1.00f, 0.50f, 0.25f,   0.2588f, 0.9659f,	0.8f, 0.5f, 0.0f, // 24
	-0.1250f, 1.2165f, 0.25f,    1.00f, 0.50f, 0.25f,   0.5000f, 0.8660f,	0.8f, 0.5f, 0.0f, // 25
	-0.1768f, 1.1768f, 0.25f,    1.00f, 0.50f, 0.25f,   0.7071f, 0.7071f,	0.8f, 0.5f, 0.0f, // 26
	-0.2165f, 1.1250f, 0.25f,    1.00f, 0.50f, 0.25f,   0.8660f, 0.5000f,	0.8f, 0.5f, 0.0f, // 27
	-0.2415f, 1.0647f, 0.25f,    1.00f, 0.50f, 0.25f,   0.9059f, 0.2588f,	0.8f, 0.5f, 0.0f, // 28
	-0.2500f, 1.0000f, 0.25f,    1.00f, 0.50f, 0.25f,   0.9000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 29
	 
	 
	// Top Back Circle
	0.0000f, 1.0000f, 0.15f,    1.00f, 0.00f, 0.00f,	0.5000f, 0.0000f,	0.0f, 0.5f, -0.8f, // 30	Center Vertex, start of Triangle Fan

	0.2500f, 1.0000f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.0f, 0.5f, -0.8f, // 31	Start of triangle fan
	0.2415f, 1.0647f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.0f, 0.5f, -0.8f, // 32
	0.2165f, 1.1250f, 0.15f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.0f, 0.5f, -0.8f, // 33
	0.1768f, 1.1768f, 0.15f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.0f, 0.5f, -0.8f, // 34 
	0.1250f, 1.2165f, 0.15f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.0f, 0.5f, -0.8f, // 35
	0.0647f, 1.2415f, 0.15f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.0f, 0.5f, -0.8f, // 36 
	0.0000f, 1.2500f, 0.15f,    1.00f, 0.50f, 0.25f,	0.0000f, 1.0000f,	0.0f, 0.5f, -0.8f, // 37	Top of Circle
   -0.0647f, 1.2415f, 0.15f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.0f, 0.5f, -0.8f, // 38
   -0.1250f, 1.2165f, 0.15f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.0f, 0.5f, -0.8f, // 39
   -0.1768f, 1.1768f, 0.15f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.0f, 0.5f, -0.8f, // 40
   -0.2165f, 1.1250f, 0.15f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.0f, 0.5f, -0.8f, // 41
   -0.2415f, 1.0647f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.0f, 0.5f, -0.8f, // 42
   -0.2500f, 1.0000f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.0f, 0.5f, -0.8f, // 43

   // Bottom Front Circle
	 0.0000f, -1.0000f, 0.25f,    1.00f, 0.00f, 0.00f,	0.5000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 44	Center Vertex, start of Triangle Fan

	 0.2500f, -1.0000f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 45	Start of triangle fan
	 0.2415f, -1.0647f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.8f, 0.5f, 0.0f, // 46
	 0.2165f, -1.1250f, 0.25f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.8f, 0.5f, 0.0f, // 47
	 0.1768f, -1.1768f, 0.25f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.8f, 0.5f, 0.0f, // 48 
	 0.1250f, -1.2165f, 0.25f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.8f, 0.5f, 0.0f, // 49
	 0.0647f, -1.2415f, 0.25f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.8f, 0.5f, 0.0f, // 50 
	 0.0000f, -1.2500f, 0.25f,    1.00f, 0.50f, 0.25f,	0.0000f, 1.0000f,	0.8f, 0.5f, 0.0f, // 51	Top of Circle
	-0.0647f, -1.2415f, 0.25f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.8f, 0.5f, 0.0f, // 52
	-0.1250f, -1.2165f, 0.25f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.8f, 0.5f, 0.0f, // 53
	-0.1768f, -1.1768f, 0.25f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.8f, 0.5f, 0.0f, // 54
	-0.2165f, -1.1250f, 0.25f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.8f, 0.5f, 0.0f, // 55
	-0.2415f, -1.0647f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.8f, 0.5f, 0.0f, // 56
	-0.2500f, -1.0000f, 0.25f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.8f, 0.5f, 0.0f, // 57

	// Bottom Back Circle
	 0.0000f, -1.0000f, 0.15f,    1.00f, 0.00f, 0.00f,	0.5000f, 0.0000f,	0.0f, 0.0f, 0.0f, // 58	Center Vertex, start of Triangle Fan

	 0.2500f, -1.0000f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9000f, 0.0000f,	0.0f, 0.0f, 0.0f, // 59	Start of triangle fan
	 0.2415f, -1.0647f, 0.15f,    1.00f, 0.50f, 0.25f,	0.9059f, 0.2588f,	0.0f, 0.0f, 0.0f, // 60
	 0.2165f, -1.1250f, 0.15f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.0f, 0.0f, 0.0f, // 61
	 0.1768f, -1.1768f, 0.15f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.0f, 0.0f, 0.0f, // 62 
	 0.1250f, -1.2165f, 0.15f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.0f, 0.0f, 0.0f, // 63
	 0.0647f, -1.2415f, 0.15f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.0f, 0.0f, 0.0f, // 64 
	 0.0000f, -1.2500f, 0.15f,    1.00f, 0.50f, 0.25f,	0.0000f, 1.0000f,	0.0f, 0.0f, 0.0f, // 65	Top of Circle
	-0.0647f, -1.2415f, 0.15f,    1.00f, 0.50f, 0.25f,	0.2588f, 0.9659f,	0.0f, 0.0f, 0.0f, // 66
	-0.1250f, -1.2165f, 0.15f,    1.00f, 0.50f, 0.25f,	0.5000f, 0.8660f,	0.0f, 0.0f, 0.0f, // 67
	-0.1768f, -1.1768f, 0.15f,    1.00f, 0.50f, 0.25f,	0.7071f, 0.7071f,	0.0f, 0.0f, 0.0f, // 68
	-0.2165f, -1.1250f, 0.15f,    1.00f, 0.50f, 0.25f,	0.8660f, 0.5000f,	0.0f, 0.0f, 0.0f, // 69
	-0.2415f, -1.0647f, 0.15f,    1.00f, 0.50f, 0.25f,  0.9059f, 0.2588f,	0.0f, 0.0f, 0.0f, // 70
	-0.2500f, -1.0000f, 0.15f,    1.00f, 0.50f, 0.25f,  0.9000f, 0.0000f,	0.0f, 0.0f, 0.0f, // 71
};

GLfloat Pvertices[] =
{
	// Table Plane
	5.0000f, -2.0000f,  1.00f,    1.00f, 0.00f, 0.0f,	1.0f, 0.0f,		0.8f, 1.0f, 0.8f, // 0		66--------------67
   -5.0000f, -2.0000f,  1.00f,    0.00f, 0.00f, 1.00f,	0.0f, 0.0f,		0.8f, 1.0f, 0.8f, // 1		|				|
   -5.0000f, -2.0000f, -5.00f,    0.00f, 1.00f, 0.00f,	0.0f, 1.0f,		0.8f, 1.0f, 0.8f, // 2		|				|
	5.0000f, -2.0000f, -5.00f,    1.00f, 0.00f, 1.00f,	1.0f, 1.0f,		0.8f, 1.0f, 0.8f, // 3		65--------------64
};

GLfloat Cvertices[] =
{

//							   6---------7
// Front Upper Left 2		 / |       / |
// Front Upper Right 3		2---------3  |
// Back Lower Left 4		|  |      |  |
// Back Lower Right 5		|  4------|--5
// Back Upper Left 6		|/        |/
// Back Upper Right 7		0---------1

							// Front
	 2.25f, -1.50f,  -2.75f,     1.00f, 0.00f, 0.00f,	0.0f, 0.0f,		0.8f, 1.5f, 0.0f, // Front Lower Left 0		    
	 2.75f, -1.50f,  -2.75f,     0.00f, 1.00f, 0.00f,	1.0f, 0.0f,		0.8f, 1.5f, 0.0f, // Front Lower Right 1		  
	 2.25f, -1.00f,  -2.75f,     0.00f, 0.00f, 1.00f,	0.0f, 1.0f,		0.8f, 1.0f, 0.0f, // Front Upper Left 2		 
	 2.75f, -1.00f,  -2.75f,     1.00f, 1.00f, 0.00f,	1.0f, 1.0f,		0.8f, 1.0f, 0.0f, // Front Upper Right 3	

							// Back
	 2.25f, -1.50f,  -3.25f,     1.00f, 0.00f, 1.00f,	0.0f, 0.0f,		0.0f, 0.5f, -0.8f, // Back Lower Left 4		
	 2.75f, -1.50f,  -3.25f,     0.00f, 1.00f, 1.00f,	1.0f, 0.0f,		0.0f, 0.5f, -0.8f, // Back Lower Right 5		
	 2.25f, -1.00f,  -3.25f,     1.00f, 1.00f, 1.00f,	0.0f, 1.0f,		0.0f, 0.5f, -0.8f, // Back Upper Left 6		
	 2.75f, -1.00f,  -3.25f,     1.00f, 0.50f, 0.25f,	1.0f, 1.0f,		0.0f, 0.5f, -0.8f, // Back Upper Right 7		

							// Right
	 2.75f, -1.50f,  -2.75f,     0.00f, 1.00f, 0.00f,   0.0f, 0.0f,		0.8f, 1.0f,  0.0f, // Front Lower Right 8		  
	 2.75f, -1.00f,  -2.75f,     1.00f, 1.00f, 0.00f,   0.0f, 1.0f,		0.8f, 1.0f,  0.0f, // Front Upper Right 9	
	 2.75f, -1.50f,  -3.25f,     0.00f, 1.00f, 1.00f,	1.0f, 0.0f,		0.8f, 1.5f, -0.8f, // Back Lower Right 10		
	 2.75f, -1.00f,  -3.25f,     1.00f, 0.50f, 0.25f,	1.0f, 1.0f,		0.0f, 1.5f, -0.8f, // Back Upper Right 11		

							// Left
	 2.25f, -1.50f,  -2.75f,     1.00f, 0.00f, 0.00f,	0.0f, 0.0f,	   -0.8f, 0.5f, -0.8f,  // Front Lower Left 12    
	 2.25f, -1.00f,  -2.75f,     0.00f, 0.00f, 1.00f,	0.0f, 1.0f,	   -0.8f, 0.5f, -0.8f,  // Front Upper Left 13		 
	 2.25f, -1.50f,  -3.25f,     1.00f, 0.00f, 1.00f,	1.0f, 0.0f,	   -0.8f, 0.5f, -0.8f,  // Back Lower Left 14	
	 2.25f, -1.00f,  -3.25f,     1.00f, 1.00f, 1.00f,	1.0f, 1.0f,	   -0.8f, 0.5f, -0.8f,  // Back Upper Left 15			

							// Top
	 2.25f, -1.00f,  -2.75f,     1.00f, 0.00f, 0.00f,	1.0f, 1.0f,	   -0.8f, 0.5f, -0.8f,  // Front Upper Left 16   
	 2.75f, -1.00f,  -2.75f,     1.00f, 0.00f, 1.00f,	0.0f, 0.0f,	   -0.8f, 0.5f, 0.0f,  // Front Upper Right 17	
	 2.25f, -1.00f,  -3.25f,     0.00f, 0.00f, 1.00f,	0.0f, 1.0f,	   -0.8f, 0.5f, -0.8f,  // Back Upper Left 18
	 2.75f, -1.00f,  -3.25f,     1.00f, 1.00f, 1.00f,	1.0f, 0.0f,	   -0.8f, 0.5f, 0.0f,  // Back Upper Right 19	

							// Bottom
	 2.25f,  -1.50f, -2.75f,     1.00f, 0.00f, 0.00f,	0.0f, 0.0f,	   -0.8f, 0.5f, 0.0f,  // Front Lower Left 20    
	 2.75f,  -1.50f, -2.75f,     0.00f, 0.00f, 1.00f,	1.0f, 0.0f,	   -0.8f, 0.5f, 0.0f,  // Front Lower Right 21		 
	 2.25f,  -1.50f, -3.25f,     1.00f, 0.00f, 1.00f,	0.0f, 1.0f,	   -0.8f, 0.5f, 0.0f,  // Back Lower Left 22	
	 2.75f,  -1.50f, -3.25f,     1.00f, 1.00f, 1.00f,	1.0f, 1.0f,	   -0.8f, 0.5f, 0.0f,  // Back Lower Right 23	

};

GLfloat Svertices[] =
{
	-2.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-2.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 -1.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 -1.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-2.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-2.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 -2.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 .25f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-2.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 -1.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 -2.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 .25f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 -2.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 -1.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 -2.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 .25f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

	 -2.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-1.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 -2.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 .25f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
	

};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Indices for vertice order
GLuint indices[] =
{
// Front Side
	0, 1, 2,
	1, 2, 3,
// Right Side
	3, 1, 5,
	5, 3, 7,
// Back Side
	7, 5, 4,
	4, 7, 6,
// Left Side
	6, 4, 0,
	0, 2, 6,


	// Top Front Circle
   17, 16, 18, 
   18, 16, 19,
   19, 16, 20,
   20, 16, 21,
   21, 16, 22,
   22, 16, 23,
   23, 16, 24,
   24, 16, 25,
   25, 16, 26,
   26, 16, 27,
   27, 16, 28,
   28, 16, 29,
   29, 16, 28,

	// Top Back Circle
   31, 30, 32,
   32, 30, 33,
   33, 30, 34,
   34, 30, 35,
   35, 30, 36,
   36, 30, 37,
   37, 30, 38,
   38, 30, 39,
   39, 30, 40,
   40, 30, 41,
   41, 30, 42,
   42, 30, 43,
   43, 30, 42,

   // Bottom Front Circle
   45, 44, 46,
   46, 44, 47,
   47, 44, 48,
   48, 44, 49,
   49, 44, 50,
   50, 44, 51,
   51, 44, 52,
   52, 44, 53,
   53, 44, 54,
   54, 44, 55,
   55, 44, 56,
   56, 44, 57,
   57, 44, 56,

   // Bottom Back Circle
   59, 58, 60,
   60, 58, 61,
   61, 58, 62,
   62, 58, 63,
   63, 58, 64,
   64, 58, 65,
   65, 58, 66,
   66, 58, 67,
   67, 58, 68,
   68, 58, 69,
   69, 58, 70,
   70, 58, 71,
   71, 58, 70,

   // Bridge Top
   17, 18, 31,
   31, 32, 18,
   18, 19, 32,
   32, 33, 19,
   19, 20, 33,
   33, 34, 20,
   20, 21, 34,
   34, 35, 21,
   21, 22, 35,
   35, 36, 22, 
   22, 23, 36,
   36, 37, 23,
   23, 24, 37,
   37, 38, 24,
   24, 25, 38,
   38, 39, 25,
   25, 26, 39,
   39, 40, 26,
   26, 27, 40,
   40, 41, 27,
   27, 28, 41,
   41, 42, 28,
   28, 29, 42,
   42, 43, 29,
   29, 30, 43,
   

   // Bottom Bridge
   45, 46, 59,
   59, 60, 46,
   46, 47, 60,
   60, 61, 47,
   47, 48, 61,
   61, 62, 48,
   48, 49, 62,
   62, 63, 49,
   49, 50, 63,
   63, 64, 50,
   50, 51, 64,
   64, 65, 51,
   51, 52, 65,
   65, 66, 52,
   52, 53, 66,
   66, 67, 53,
   53, 54, 67,
   67, 68, 54,
   54, 55, 68,
   68, 69, 55,
   55, 56, 69,
   69, 70, 56,
   56, 57, 70,
   70, 71, 57,
   57, 58, 71,
   71, 70, 58
   

};

GLuint Pindices[] =
{
	// Table Plane
   0, 1, 2,
   2, 3, 0,

};

GLuint Cindices[] =
{
	// Front Side
	0, 1, 2,
	1, 2, 3,
	// Back Side
	4, 5, 6,
	6, 7, 5,
	// Right Side
	 8,  9, 10,
	10, 11,  9,
	// Left Side
	12, 13, 14,
	14, 15, 13,
	// Top Side
	16, 17, 18,
	18, 19, 17,
	// Bottom Side
	20, 21, 22,
	22, 23, 21
};

GLuint Sindices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side


};

int main() {

	// Initialize GLFW
	glfwInit();

	// Remind GLFW the version  of OpenGL we plan to run, this will be for better performance
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Tell GLFW that we are using the CORE profile, this will open more modern features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW Window with dimensions: 800 pixels x 800 pixels
	// Window titled with author's name for proof of authenticity
	GLFWwindow* window = glfwCreateWindow(width, height, "Milestone by Douglas", NULL, NULL);

	// Error Check for failed window
	if (window == NULL) 
	{
		// Display error message
		std::cout << "Failed to create GLFW window! :(" << std::endl;
		glfwTerminate();
		// Return error code
		return -1;
	}
	
	// Introduce widnow into current context
	glfwMakeContextCurrent(window);
	glfwSetScrollCallback(window, scrollCallback);

	// Load GLAD so it configures OpenGL
	gladLoadGL();


	// Specify the viewport of OpenGL in the window. Goes from top left of screen to bottom right
	glViewport(0, 0, width, height);


	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	
	
	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(Pvertices, sizeof(Pvertices));

	EBO EBO2(Pindices, sizeof(Pindices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(Cvertices, sizeof(Cvertices));

	EBO EBO3(Cindices, sizeof(Cindices));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));

	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	VAO VAO4;
	VAO4.Bind();

	VBO VBO4(Svertices, sizeof(Svertices));

	EBO EBO4(Sindices, sizeof(Sindices));

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));

	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	glm::vec3 biscuitPos[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -1.0f),
			glm::vec3(-1.0f, 0.0f, -1.0f)
	};

	
	glm::mat4 biscuitModel = glm::mat4(1.0f);
	for (unsigned int i = 0; i < 1; i++) {
		glm::mat4 biscuitModel = glm::mat4(1.0f);
		biscuitModel = glm::mat4(1.0f);
		biscuitModel = glm::translate(biscuitModel, biscuitPos[i]);
		biscuitModel = glm::rotate(biscuitModel, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	glm::vec3 cakePos[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -1.0f),
			glm::vec3(-1.0f, 0.0f, -1.0f)
	};

	glm::mat4 cakeModel = glm::mat4(1.0f);
	for (unsigned int i = 0; i < 1; i++) {
		glm::mat4 cakeModel = glm::mat4(1.0f);
		cakeModel = glm::mat4(1.0f);
		cakeModel = glm::translate(cakeModel, cakePos[i]);
		cakeModel = glm::rotate(cakeModel, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	glm::vec3 strawberryPos[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -1.0f),
			glm::vec3(-1.0f, 0.0f, -1.0f)
	};

	glm::mat4 strawberryModel = glm::mat4(1.0f);
	for (unsigned int i = 0; i < 1; i++) {
		glm::mat4 strawberryModel = glm::mat4(1.0f);
		strawberryModel = glm::mat4(1.0f);
		strawberryModel = glm::translate(strawberryModel, strawberryPos[i]);
		strawberryModel = glm::rotate(strawberryModel, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 3, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(biscuitModel));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 2, GL_FALSE, glm::value_ptr(cakeModel));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 3, GL_FALSE, glm::value_ptr(strawberryModel));


	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);




	// Texture
	Texture wafer("Lady Finger Raw.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	wafer.texUnit(shaderProgram, "tex0", 0);

	Texture table("Table.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
	table.texUnit(shaderProgram, "tex1", 1);

	Texture cake("Cake.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGB, GL_UNSIGNED_BYTE);
	cake.texUnit(shaderProgram, "tex2", 2);

	Texture strawberry("Strawberry.png", GL_TEXTURE_2D, GL_TEXTURE3, GL_RGB, GL_UNSIGNED_BYTE);
	strawberry.texUnit(shaderProgram, "tex3", 3);

	// Enables Depth Buffer Test
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		// Specify color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles Camera inputs
		camera.Inputs(window);

		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Activate the shader program through OpenGL
		shaderProgram.Activate();

		camera.Matrix(shaderProgram, "camMatrix");
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		// Binds the texture so it appears in rendering
		wafer.Bind();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, (sizeof(indices) - 16) / sizeof(int), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(indices + 16)/ sizeof(int), GL_UNSIGNED_INT, 0);

		table.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(Pindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		cake.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(Cindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		strawberry.Bind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(Sindices)  / sizeof(int), GL_UNSIGNED_INT, 0);



		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");

		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap back buffer with the front buffer
		glfwSwapBuffers(window);

		// Manages all GLFW events
		glfwPollEvents();
	}

	// Delete all objects created
	VAO1.Delete();
	VAO2.Delete();
	VAO3.Delete();
	VAO4.Delete();
	VBO1.Delete();
	VBO2.Delete();
	VBO3.Delete();
	VBO4.Delete();
	EBO1.Delete();
	EBO2.Delete();
	EBO3.Delete();
	EBO4.Delete();
	wafer.Delete();
	table.Delete();
	cake.Delete();
	strawberry.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();

	// Close window before ending the program
	glfwDestroyWindow(window);
	
	// Terminate GLFW before closing program
	glfwTerminate();

	return 0;
}

// Whenever the mouse scroll wheel scrolls, this callback will be called
void scrollCallback(GLFWwindow*, double xOffset, double yOffset) {
	camera.processMouseScroll(yOffset);
}