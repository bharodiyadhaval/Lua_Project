//Shalin
//Dhaval
//Prakash
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>	
#include <ctime>
#include<math.h>
// C++ cin, cout, etc.
//#include "linmath.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include<time.h>

#include <stdlib.h>
#include <stdio.h>
// Add the file stuff library (file stream>
#include <fstream>
#include <sstream>		// "String stream"
#include <string>

#include <vector>		//  smart array, "array" in most languages

#include "Utilities.h"

#include "ModelUtilities.h"

#include "cMesh.h"

#include "cShaderManager.h" 

#include "cGameObject.h"

#include "cVAOMeshManager.h"


extern "C" {
#include<Lua5.3.3\lua.h>
#include<Lua5.3.3\lualib.h>
#include<Lua5.3.3\lauxlib.h>
}
#define lua_open()  luaL_newstate()
lua_State* L;








// This is the function "signature" for the 
//	function WAY at the bottom of the file.
void PhysicsStep( double deltaTime );



//Commented Out

// Supposed to match the shader vertex layout...
//class cVertex
//{
//public:
//    float x, y, z;		// Position (vec2)	float x, y;	
//    float r, g, b;		// Colour (vec3)
//};


//cVertex vertices[3] =
//{
//	//  x       y    r      g    b
//    { -0.6f, -0.4f, 1.0f, 0.0f, 0.0f },	// Red
//    {  0.6f, -0.4f, 1.0f, 0.0f, 0.0f },	// Green
//    {   0.f,  0.6f, 1.0f, 0.0f, 0.0f }	// Blue
//};

// 453 vertices, so we'll make our array a little buffer

//cVertex vertices[4096];		// Stack based array (1Mbyte)
//cVertex* p_gVertices = 0;			// Heap based (to be an) array


//int g_numberOfVertices = 0;				// vertices
//int g_numberOfIndicies = 0;
//int g_numberOfTriangles = 0;			// faces

// This is a "c style" static allocated array
// Fixed in size, set at compile time, 
//  and in c, it's full of garbage values

//	static const int MAXNUMBEROFGAMEOBJECTS = 10;
//	cGameObject* g_GameObjects[MAXNUMBEROFGAMEOBJECTS];

// Remember to #include <vector>...



std::vector< cGameObject* >  g_vecGameObjects;


glm::vec3 g_cameraXYZ = glm::vec3( 30.0f,31.0f,40.0f );	// 5 units "down" z
glm::vec3 g_cameraTarget_XYZ = glm::vec3( 30.0f,30.0f,30.0f );

cVAOMeshManager* g_pVAOManager = 0;		// or NULL, or nullptr


//Commented Out



cShaderManager*		g_pShaderManager;		// Heap, new (and delete)


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

	if ( key == GLFW_KEY_SPACE  )
	{
//		::g_GameObjects[1]->position.y += 0.01f;
		::g_vecGameObjects[1]->position.y += 0.01f;
	}

	const float CAMERASPEED = 0.1f;
	switch ( key )
	{
	case GLFW_KEY_A:		// Left
		g_cameraXYZ.x -= CAMERASPEED;
//		g_cameraTarget_XYZ.x -= CAMERASPEED;
		break;
	case GLFW_KEY_D:		// Right
		g_cameraXYZ.x += CAMERASPEED;
//		g_cameraTarget_XYZ.x += CAMERASPEED;
		break;
	case GLFW_KEY_W:		// Forward (along z)
		g_cameraXYZ.z += CAMERASPEED;
		break;
	case GLFW_KEY_S:		// Backwards (along z)
		g_cameraXYZ.z -= CAMERASPEED;
		break;
	case GLFW_KEY_Q:		// "Down" (along y axis)
		g_cameraXYZ.y -= CAMERASPEED;
		break;
	case GLFW_KEY_E:		// "Up" (along y axis)
		g_cameraXYZ.y += CAMERASPEED;
		break;

	}
	return;
}





float ip[10][3];
//First time function variable

int isFirsttime[500];
int isEnd[500];
int methodinstance;
float position[500][3];
float orientation[500][3];
int isFirsttime2[50];
float position2[50][3];
int afterinstance;


int inif2 = 0;
int inif = 0;
int i[500];
int j[500];
float ix=0, iy=0, iz=0;
int printflag = 0, positionflag = 0;
int q;
int k;

float dist;
int easein;
int easeout;

int MoveTo(lua_State *L)
{
	inif = 0;

	methodinstance = lua_tonumber(L, 1);
	if (isEnd[methodinstance] != 1)
	{
		isEnd[methodinstance] = 0;
		float cord[3];
		int obj;
		obj = lua_tonumber(L, 2);
		cord[0] = lua_tonumber(L, 3);
		cord[1] = lua_tonumber(L, 4);
		cord[2] = lua_tonumber(L, 5);

		float seconds = 100*lua_tonumber(L, 6);

		easein = lua_tonumber(L, 7);
		easeout = lua_tonumber(L, 8);
		dist = lua_tonumber(L, 9);
		float dev = seconds;
		if (isFirsttime[methodinstance] == 1)
		{
			//First Time
			position[methodinstance][0] = g_vecGameObjects[obj]->position.x;
			position[methodinstance][1] = g_vecGameObjects[obj]->position.y;
			position[methodinstance][2] = g_vecGameObjects[obj]->position.z;
			printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds\n", obj, position[methodinstance][0], position[methodinstance][1], position[methodinstance][2], cord[0], cord[1], cord[2], seconds);
			isFirsttime[methodinstance] = 0;
			i[methodinstance] = 2000;
		}
	

		
		if (  ( abs(position[methodinstance][0] - g_vecGameObjects[obj]->position.x) <= abs(cord[0] - position[methodinstance][0])*dist/100&&abs(abs(cord[0] - position[methodinstance][0])*dist/100 - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(position[methodinstance][1] - g_vecGameObjects[obj]->position.y) <= abs(cord[1] - position[methodinstance][1])*dist / 100 && abs(abs(cord[1] - position[methodinstance][1])*dist / 100 - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(position[methodinstance][2] - g_vecGameObjects[obj]->position.z) <= abs(cord[2] - position[methodinstance][2])*dist / 100 && abs(abs(cord[2] - position[methodinstance][2])*dist / 100 - g_vecGameObjects[obj]->position.z) >= 0.01) && i[methodinstance]>=0)
		{
			dev = dev+i[methodinstance];
			i[methodinstance] = i[methodinstance] - ((2000-seconds)/ abs(cord[0] - position[methodinstance][0])*dist/100)/easein*12;
			//k = k +k*1.1;
			printf("this is I yo:%d",i[methodinstance]);
				
		}
		else
		{
			if (abs(cord[0] - g_vecGameObjects[obj]->position.x) <= (cord[0] - position[methodinstance][0])*0.15&&abs(cord[0] - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(cord[1] - g_vecGameObjects[obj]->position.y) <= (cord[1] - position[methodinstance][1])*0.15&&abs(cord[1] - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(cord[2] - g_vecGameObjects[obj]->position.z) <= (cord[2] - position[methodinstance][2])*0.15&&abs(cord[2] - g_vecGameObjects[obj]->position.z) >= 0.01)
			{


				dev = dev + j[methodinstance];
				j[methodinstance] = j[methodinstance] + 6 * easeout;
				k = k + 2;
			}
			else
			{
				dev = seconds;
			}
		
		}
		
		/*else
		{
			dev=seconds;
		}*/
		


	
		if (abs(g_vecGameObjects[obj]->position.x - cord[0])>=0.010 || abs(g_vecGameObjects[obj]->position.y - cord[0]) >= 0.010 || abs(g_vecGameObjects[obj]->position.y - cord[0]) >= 0.010)
		{
			g_vecGameObjects[obj]->position.x += (cord[0] - position[methodinstance][0] )/ dev ;
			g_vecGameObjects[obj]->position.y +=  (cord[1] - position[methodinstance][1]) / dev ;
			g_vecGameObjects[obj]->position.z += (cord[2] - position[methodinstance][2]) / dev ;
			//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - position[methodinstance][0]) / dev);
			inif = 1;
		}

		if( abs(ceil(g_vecGameObjects[obj]->position.x * 100) / 100 - cord[0]) <= 0.010 && abs(ceil(g_vecGameObjects[obj]->position.y * 100) / 100 - cord[1]) <= 0.010 && abs(ceil(g_vecGameObjects[obj]->position.z * 100) / 100 - cord[2]) <= 0.010)
		{
			isEnd[methodinstance] = 1;
			positionflag = 0;
			//For the last time
			time_t timer;
			struct tm * timeinfo;
			time(&timer);
			timeinfo = localtime(&timer);
		//	std::cout << asctime(timeinfo) << "\n";
			std::cout << g_vecGameObjects[methodinstance]->position.x << ",";
			 std::cout << g_vecGameObjects[methodinstance]->position.y << ",";
			 std::cout << g_vecGameObjects[methodinstance]->position.z << ",";
			printf("\nThe method %d has ended", methodinstance);
		
		}


		return 3;
	}
	else
	{
	
		return 3;
	}
	

}



///////////////////////////////


int MoveToAfter(lua_State *L)
{
	afterinstance = lua_tonumber(L, 1);
	methodinstance = lua_tonumber(L, 2);
	
	inif = 0;
	if (isEnd[methodinstance] != 1)
	{
		isEnd[methodinstance] = 0;
		if (isEnd[afterinstance] == 1)
		{
			//printf("\nMethod 2 start");
			float cord[3];
			int obj;

			obj = lua_tonumber(L, 3);
			cord[0] = lua_tonumber(L, 4);
			cord[1] = lua_tonumber(L, 5);
			cord[2] = lua_tonumber(L, 6);

			float seconds = 100 * lua_tonumber(L, 7);
			easein = lua_tonumber(L, 8);
			easeout = lua_tonumber(L, 9);
			dist = lua_tonumber(L, 10);
			float dev = seconds;
			if (isFirsttime[methodinstance] == 1)
			{
				i[methodinstance] = 2000;
				j[methodinstance] = 0;
				k = 1;
				position[methodinstance][0] = g_vecGameObjects[obj]->position.x;
				position[methodinstance][1] = g_vecGameObjects[obj]->position.y;
				position[methodinstance][2] = g_vecGameObjects[obj]->position.z;
				printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds", obj, position[methodinstance][0], position[methodinstance][1], position[methodinstance][2], cord[0], cord[1], cord[2], seconds);
				isFirsttime[methodinstance] = 0;
			}
			if ((abs(position[methodinstance][0] - g_vecGameObjects[obj]->position.x) <= abs(cord[0] - position[methodinstance][0])*dist / 100 && abs(abs(cord[0] - position[methodinstance][0])*dist / 100 - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(position[methodinstance][1] - g_vecGameObjects[obj]->position.y) <= abs(cord[1] - position[methodinstance][1])*dist / 100 && abs(abs(cord[1] - position[methodinstance][1])*dist / 100 - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(position[methodinstance][2] - g_vecGameObjects[obj]->position.z) <= abs(cord[2] - position[methodinstance][2])*dist / 100 && abs(abs(cord[2] - position[methodinstance][2])*dist / 100 - g_vecGameObjects[obj]->position.z) >= 0.01) && i[methodinstance] >= 0)
			{
				dev = dev + i[methodinstance];
				i[methodinstance] = i[methodinstance] - ((2000 - seconds) / abs(cord[0] - position[methodinstance][0])*dist/100) / easein * 12;
				//k = k +k*1.1;
			//	printf("this is i[methodinstance] yo:%d", i[methodinstance]);

			}
			else
			{
				if (abs(cord[0] - g_vecGameObjects[obj]->position.x) <= (cord[0] - position[methodinstance][0])*0.15&&abs(cord[0] - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(cord[1] - g_vecGameObjects[obj]->position.y) <= (cord[1] - position[methodinstance][1])*0.15&&abs(cord[1] - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(cord[2] - g_vecGameObjects[obj]->position.z) <= (cord[2] - position[methodinstance][2])*0.15&&abs(cord[2] - g_vecGameObjects[obj]->position.z) >= 0.01)
				{


					dev = dev + j[methodinstance];
					j[methodinstance] = j[methodinstance] + 6 * easeout;
					k = k + 2;
				}
				else
				{
					dev = seconds;
				}

			}



			/*time_t timer;
			struct tm * timeinfo;
			time(&timer);
			timeinfo = localtime(&timer);
			*/
			/*if (flag1 != 1)
			{
			std::cout << asctime(timeinfo);
			flag1 = 1;
			}
			*/



			if (abs(ceil(g_vecGameObjects[obj]->position.x * 100) / 100 - cord[0]) >= 0.010 || abs(ceil(g_vecGameObjects[obj]->position.y * 100) / 100 - cord[1]) >= 0.010 || abs(ceil(g_vecGameObjects[obj]->position.z * 100) / 100 - cord[2]) >= 0.010)
			{
				g_vecGameObjects[obj]->position.x += ceil(10000 * (cord[0] - position[methodinstance][0]) / dev) / 10000;
				g_vecGameObjects[obj]->position.y += ceil(10000 * (cord[1] - position[methodinstance][1]) / dev) / 10000;
				g_vecGameObjects[obj]->position.z += ceil(10000 * (cord[2] - position[methodinstance][2]) / dev) / 10000;
				//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - position[methodinstance][0]) / dev);
				inif = 1;
			}

			if (inif == 0)
			{
				/*if (flag2 != 1)
				{
				std::cout << asctime(timeinfo);
				flag2 = 1;
				}*/
				//isFirsttime[methodinstance] = 1;
				isEnd[methodinstance] = 1;
				printf("\nThe method %d has ended", methodinstance);
				positionflag = 0;

			}




			return 3;
		}
		else
		{
			return 3;
		}
	}
	else
	{
		return 3;
	}


}





///////////////////

int OrientTo(lua_State *L)
{
	inif = 0;

	methodinstance = lua_tonumber(L, 1);
	if (isEnd[methodinstance] != 1)
	{
		isEnd[afterinstance] = 0;
		float cord[3];
		int obj;
		methodinstance = lua_tonumber(L, 1);
		obj = lua_tonumber(L, 2);
		cord[0] = lua_tonumber(L, 3)/90;
		cord[1] = lua_tonumber(L, 4)/90;
		cord[2] = lua_tonumber(L, 5)/90;
		float seconds = 100*lua_tonumber(L, 6);
		easein = lua_tonumber(L, 7);
		easeout = lua_tonumber(L, 8);
		float dev = seconds;



		if (isFirsttime[methodinstance] == 1)
		{
			//First Time
			orientation[methodinstance][0] =  g_vecGameObjects[obj]->orientation2.x;
			orientation[methodinstance][1] = g_vecGameObjects[obj]->orientation2.y;
			orientation[methodinstance][2] = g_vecGameObjects[obj]->orientation2.z;
			printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds\n", obj, orientation[methodinstance][0], orientation[methodinstance][1], orientation[methodinstance][2], cord[0], cord[1], cord[2], seconds);
			isFirsttime[methodinstance] = 0;
			i[methodinstance] = 2000;
			j[methodinstance] = 0;
			k = 1;
			time_t timer;
			struct tm * timeinfo;
			time(&timer);
			timeinfo = localtime(&timer);

			std::cout << asctime(timeinfo) << "\n";
		}

		//std::cout << g_vecGameObjects[obj]->orientation2.x - (orientation[methodinstance][0] + cord[0])<<"\n";
		
		if (   abs ( g_vecGameObjects[obj]->orientation2.x - ( orientation[methodinstance][0] + cord[0] )) >= 0.0001   ||   abs  (g_vecGameObjects[obj]->orientation2.y - (orientation[methodinstance][1] + cord[1])) >= 0.0001 || abs(g_vecGameObjects[obj]->orientation2.z - (orientation[methodinstance][2] + cord[2]) >=0.0001))
		{
			g_vecGameObjects[obj]->orientation2.x += (cord[0] )/ dev ;
			g_vecGameObjects[obj]->orientation2.y +=  (cord[1]) / dev ;
			g_vecGameObjects[obj]->orientation2.z += (cord[2]) / dev ;
			//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - orientation[methodinstance][0]) / dev);
			inif = 1;
			std::cout << g_vecGameObjects[obj]->orientation2.x<<",";
			std::cout << g_vecGameObjects[obj]->orientation2.y<<",";
			std::cout << g_vecGameObjects[obj]->orientation2.z<<"\n";
		}

		if(inif==0)
		{

			isEnd[methodinstance] = 1;
			printf("\nThe method %d has ended", methodinstance);
			positionflag = 0;
			//For the last time
			time_t timer;
			struct tm * timeinfo;
			time(&timer);
			timeinfo = localtime(&timer);
			std::cout << asctime(timeinfo) << "\n";
		
		}


		return 3;
	}
	else
	{
	
		return 3;
	}
	

}



int OrientToAfter(lua_State *L)
{
	afterinstance = lua_tonumber(L, 1);
	methodinstance = lua_tonumber(L, 2);

	inif = 0;
	if(isEnd[methodinstance]!=1)
	{
		if (isEnd[afterinstance] == 1)
		{
			isEnd[methodinstance] = 0;
			float cord[3];
			int obj;

			obj = lua_tonumber(L, 3);
			cord[0] = lua_tonumber(L, 4) / 90;
			cord[1] = lua_tonumber(L, 5) / 90;
			cord[2] = lua_tonumber(L, 6) / 90;
			float seconds = 100 * lua_tonumber(L, 7);
			easein = lua_tonumber(L, 8);
			easeout = lua_tonumber(L, 9);
			float dev = seconds;

			if (abs(g_vecGameObjects[obj]->orientation2.x - (orientation[methodinstance][0] + cord[0])) >= 0.0001 || abs(g_vecGameObjects[obj]->orientation2.y - (orientation[methodinstance][1] + cord[1])) >= 0.0001 || abs(g_vecGameObjects[obj]->orientation2.z - (orientation[methodinstance][2] + cord[2]) >= 0.0001))
			{
				g_vecGameObjects[obj]->orientation2.x += (cord[0]) / dev;
				g_vecGameObjects[obj]->orientation2.y += (cord[1]) / dev;
				g_vecGameObjects[obj]->orientation2.z += (cord[2]) / dev;
				//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - orientation[methodinstance][0]) / dev);
				inif = 1;
				std::cout << g_vecGameObjects[obj]->orientation2.x << ",";
				std::cout << g_vecGameObjects[obj]->orientation2.y << ",";
				std::cout << g_vecGameObjects[obj]->orientation2.z << "\n";
			}

			if (inif == 0)
			{
				/*if (flag2 != 1)
				{
				std::cout << asctime(timeinfo);
				flag2 = 1;
				}*/
				//isFirsttime[methodinstance] = 1;
				isEnd[methodinstance] = 1;
				printf("\nThe method %d has ended", methodinstance);
				positionflag = 0;

			}
		  }

		else
		{
			return 3;
		}

	
	}
	else
	{
		return 3;
	}


}



///////////////////




int withinstance;

int MoveToWith(lua_State *L)
{
	afterinstance = lua_tonumber(L, 1);
	methodinstance = lua_tonumber(L, 2);

	inif = 0;
	if (isEnd[methodinstance] != 1)
	{
		isEnd[methodinstance] = 0;
		if (isEnd[afterinstance] == 1)
		{
			//printf("\nMethod 2 start");
			float cord[3];
			int obj;

			obj = lua_tonumber(L, 3);
			cord[0] = lua_tonumber(L, 4);
			cord[1] = lua_tonumber(L, 5);
			cord[2] = lua_tonumber(L, 6);

			float seconds = 100 * lua_tonumber(L, 7);
			easein = lua_tonumber(L, 8);
			easeout = lua_tonumber(L, 9);
			dist = lua_tonumber(L, 10);
			float dev = seconds;
			if (isFirsttime[methodinstance] == 1)
			{
				i[methodinstance] = 2000;
				j[methodinstance] = 0;
				k = 1;
				position[methodinstance][0] = g_vecGameObjects[obj]->position.x;
				position[methodinstance][1] = g_vecGameObjects[obj]->position.y;
				position[methodinstance][2] = g_vecGameObjects[obj]->position.z;
				printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds", obj, position[methodinstance][0], position[methodinstance][1], position[methodinstance][2], cord[0], cord[1], cord[2], seconds);
				isFirsttime[methodinstance] = 0;
			}
			if ((abs(position[methodinstance][0] - g_vecGameObjects[obj]->position.x) <= abs(cord[0] - position[methodinstance][0])*dist / 100 && abs(abs(cord[0] - position[methodinstance][0])*dist / 100 - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(position[methodinstance][1] - g_vecGameObjects[obj]->position.y) <= abs(cord[1] - position[methodinstance][1])*dist / 100 && abs(abs(cord[1] - position[methodinstance][1])*dist / 100 - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(position[methodinstance][2] - g_vecGameObjects[obj]->position.z) <= abs(cord[2] - position[methodinstance][2])*dist / 100 && abs(abs(cord[2] - position[methodinstance][2])*dist / 100 - g_vecGameObjects[obj]->position.z) >= 0.01) && i[methodinstance] >= 0)
			{
				dev = dev + i[methodinstance];
				i[methodinstance] = i[methodinstance] - ((2000 - seconds) / abs(cord[0] - position[methodinstance][0])*dist / 100) / easein * 12;
				//k = k +k*1.1;
				//	printf("this is i[methodinstance] yo:%d", i[methodinstance]);

			}
			else
			{
				if (abs(cord[0] - g_vecGameObjects[obj]->position.x) <= (cord[0] - position[methodinstance][0])*0.15&&abs(cord[0] - g_vecGameObjects[obj]->position.x) >= 0.01 || abs(cord[1] - g_vecGameObjects[obj]->position.y) <= (cord[1] - position[methodinstance][1])*0.15&&abs(cord[1] - g_vecGameObjects[obj]->position.y) >= 0.01 || abs(cord[2] - g_vecGameObjects[obj]->position.z) <= (cord[2] - position[methodinstance][2])*0.15&&abs(cord[2] - g_vecGameObjects[obj]->position.z) >= 0.01)
				{


					dev = dev + j[methodinstance];
					j[methodinstance] = j[methodinstance] + 6 * easeout;
					k = k + 2;
				}
				else
				{
					dev = seconds;
				}

			}



			/*time_t timer;
			struct tm * timeinfo;
			time(&timer);
			timeinfo = localtime(&timer);
			*/
			/*if (flag1 != 1)
			{
			std::cout << asctime(timeinfo);
			flag1 = 1;
			}
			*/



			if (abs(ceil(g_vecGameObjects[obj]->position.x * 100) / 100 - cord[0]) >= 0.010 || abs(ceil(g_vecGameObjects[obj]->position.y * 100) / 100 - cord[1]) >= 0.010 || abs(ceil(g_vecGameObjects[obj]->position.z * 100) / 100 - cord[2]) >= 0.010)
			{
				g_vecGameObjects[obj]->position.x += ceil(10000 * (cord[0] - position[methodinstance][0]) / dev) / 10000;
				g_vecGameObjects[obj]->position.y += ceil(10000 * (cord[1] - position[methodinstance][1]) / dev) / 10000;
				g_vecGameObjects[obj]->position.z += ceil(10000 * (cord[2] - position[methodinstance][2]) / dev) / 10000;
				//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - position[methodinstance][0]) / dev);
				inif = 1;
			}

			if (inif == 0)
			{
				/*if (flag2 != 1)
				{
				std::cout << asctime(timeinfo);
				flag2 = 1;
				}*/
				//isFirsttime[methodinstance] = 1;
				isEnd[methodinstance] = 1;
				printf("\nThe method %d has ended", methodinstance);
				positionflag = 0;

			}




			return 3;
		}
		else
		{
			return 3;
		}
	}
	else
	{
		return 3;
	}


}



int followobj;


int MoveCameraTo(lua_State *L)
{
	withinstance = lua_tonumber(L, 1);
	methodinstance = lua_tonumber(L, 2);
	followobj = lua_tonumber(L, 3);
	inif = 0;
	if (isEnd[methodinstance] != 1)
	{
		isEnd[methodinstance] = 0;
		if (isEnd[afterinstance] == 1)
		{
			//printf("\nMethod 2 start");
			glm::vec3 g_cameraXYZ = { g_vecGameObjects[followobj]->position.x,g_vecGameObjects[followobj]->position.y ,g_vecGameObjects[followobj]->position.z + 4 };	// 5 units "down" z
			glm::vec3 g_cameraTarget_XYZ = { g_vecGameObjects[followobj]->position.x,g_vecGameObjects[followobj]->position.y ,g_vecGameObjects[followobj]->position.z };
			glm::mat4 v = glm::mat4(1.0f);	// identity

							//glm::vec3 cameraXYZ = glm::vec3( 0.0f, 0.0f, 5.0f );	// 5 units "down" z
			v = glm::lookAt(g_cameraXYZ,						// "eye" or "camera" position
				g_cameraTarget_XYZ,		// "At" or "target" 
				glm::vec3(0.0f, 1.0f, 0.0f));
			printf("Camera changed");
			return 3;
		}
		else
		{
	
			/*isEnd[methodinstance] = 1;
			printf("\nThe method %d has ended", methodinstance);
			positionflag = 0;*/
			return 3;
		}
	}
	else
	{
		return 3;
	}


}




int OrientToWith(lua_State *L)
{
	withinstance = lua_tonumber(L, 1);
	methodinstance = lua_tonumber(L, 2);

	inif = 0;
	if (isEnd[methodinstance] != 1)
	{
		isEnd[methodinstance] = 0;
		if (isEnd[withinstance] == 0 || isFirsttime[methodinstance] == 0)
		{

			printf("\nMethod 2 start");
			float cord[3];
			int obj;

			obj = lua_tonumber(L, 3);
			cord[0] = lua_tonumber(L, 4)/90;
			cord[1] = lua_tonumber(L, 5)/90;
			cord[2] = lua_tonumber(L, 6)/90;

			float seconds = 100 * lua_tonumber(L, 7);
			easein = lua_tonumber(L, 8);
			easeout = lua_tonumber(L, 9);
			float dev = seconds;
			if (isFirsttime[methodinstance] == 1)
			{
				i[methodinstance] = 2000;
				j[methodinstance] = 0;
				k = 1;
				orientation[methodinstance][0] = g_vecGameObjects[obj]->orientation.x;
				orientation[methodinstance][1] = g_vecGameObjects[obj]->orientation.y;
				orientation[methodinstance][2] = g_vecGameObjects[obj]->orientation.z;
				printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds", obj, orientation[methodinstance][0], orientation[methodinstance][1], orientation[methodinstance][2], cord[0], cord[1], cord[2], seconds);
				isFirsttime[methodinstance] = 0;
			}
			if (abs(g_vecGameObjects[obj]->orientation2.x - (orientation[methodinstance][0] + cord[0])) >= 0.0001 || abs(g_vecGameObjects[obj]->orientation2.y - (orientation[methodinstance][1] + cord[1])) >= 0.0001 || abs(g_vecGameObjects[obj]->orientation2.z - (orientation[methodinstance][2] + cord[2]) >= 0.0001))
			{
				g_vecGameObjects[obj]->orientation2.x += (cord[0]) / dev;
				g_vecGameObjects[obj]->orientation2.y += (cord[1]) / dev;
				g_vecGameObjects[obj]->orientation2.z += (cord[2]) / dev;
				//printf("i[methodinstance] am here in instance %d for object %d to %f units\n", methodinstance, obj, (cord[0] - orientation[methodinstance][0]) / dev);
				inif = 1;
				std::cout << g_vecGameObjects[obj]->orientation2.x << ",";
				std::cout << g_vecGameObjects[obj]->orientation2.y << ",";
				std::cout << g_vecGameObjects[obj]->orientation2.z << "\n";
			}


			if (inif == 0)
			{
				/*if (flag2 != 1)
				{
				std::cout << asctime(timeinfo);
				flag2 = 1;
				}*/
				//isFirsttime[methodinstance] = 1;
				isEnd[methodinstance] = 1;
				printf("\nThe method %d has ended", methodinstance);
				positionflag = 0;

			}




			return 3;
		}
		else
		{
			return 3;
		}
	}

	else
	{
		return 3;
	}


}

///////////////////////////////


//
//
//int MoveTo(lua_State *L)
//{
//
//	float cord[3];
//	int obj;
//	obj = lua_tonumber(L, 1);
//	float position[3] = { position[0] = g_vecGameObjects[obj]->position.x,position[0] = g_vecGameObjects[obj]->position.y,position[0] = g_vecGameObjects[obj]->position.z };
//
//
//
//
//	cord[0] = lua_tonumber(L, 2);
//	cord[1] = lua_tonumber(L, 3);
//	cord[2] = lua_tonumber(L, 4);
//
//	float seconds = lua_tonumber(L, 5);
//	float dev = seconds * (cord[0] - position[0]) * 525 / (7 * (cord[0] - position[0]));
//	/*time_t timer;
//	struct tm * timeinfo;
//	time(&timer);
//	timeinfo = localtime(&timer);
//	*/
//	/*if (flag1 != 1)
//	{
//	std::cout << asctime(timeinfo);
//	flag1 = 1;
//	}
//	*/
//
//	if (position[0] == g_vecGameObjects[obj]->position.x&&position[1] == g_vecGameObjects[obj]->position.y&&position[2] == g_vecGameObjects[obj]->position.z)
//	{
//		printf("\nMoving Object:%d (%f,%f,%f) -> (%f,%f,%f) | %f seconds", obj, position[0], position[1], position[2], cord[0], cord[1], cord[2], seconds);
//	}
//
//	if (abs((g_vecGameObjects[obj]->position.x - cord[obj])<0.01) || abs((g_vecGameObjects[obj]->position.y - cord[1])<0.01) || abs((g_vecGameObjects[obj]->position.z - cord[2])<0.01))
//	{
//		g_vecGameObjects[obj]->position.x += (cord[0] - position[0]) * 3 / dev;
//		g_vecGameObjects[obj]->position.y += (cord[1] - position[1]) * 3 / dev;
//		g_vecGameObjects[obj]->position.z += (cord[2] - position[2]) * 3 / dev;
//	}
//
//	else
//	{
//		/*if (flag2 != 1)
//		{
//		std::cout << asctime(timeinfo);
//		flag2 = 1;
//		}*/
//		positionflag = 0;
//
//	}
//
//
//
//
//	return 3;
//
//
//}
//





//////////////////

int main(void)
{
	
	for (int i = 0; i <= 49; i++)
	{
		isFirsttime[i] = 1;
		isFirsttime2[i] = 1;
		isEnd[i] = 2;
	}

	
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);




	int height = 480;	/* default */
	int width = 640;	// default
	std::string title = "OpenGL Rocks";

	std::ifstream infoFile("config.txt");
	if ( ! infoFile.is_open() )
	{	// File didn't open...
		std::cout << "Can't find config file" << std::endl;
		std::cout << "Using defaults" << std::endl;
	}   
	else
	{	// File DID open, so read it... 
		std::string a;	
		
		infoFile >> a;	// "Game"	//std::cin >> a;
		infoFile >> a;	// "Config"
		infoFile >> a;	// "width"

		infoFile >> width;	// 1080

		infoFile >> a;	// "height"

		infoFile >> height;	// 768

		infoFile >> a;		// Title_Start

		std::stringstream ssTitle;		// Inside "sstream"
		bool bKeepReading = true;
		do
		{
			infoFile >> a;		// Title_End??
			if ( a != "Title_End" )
			{
				ssTitle << a << " ";
			}
			else
			{	// it IS the end! 
				bKeepReading  = false;
				title = ssTitle.str();
			}
		}while( bKeepReading );


	}//if ( ! infoFile.is_open() )


//	std::vector< cGameObject* >  g_vecGameObjects;
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 28;
		pTempGO->position.y = 30;
		pTempGO->position.z = 34;
		pTempGO->orientation.z  = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
	//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 1.0f;
		pTempGO->diffuseColour = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
		pTempGO->meshName = "gun";
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
	}

	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 28;
		pTempGO->position.y = 30.1;
		pTempGO->position.z = 34;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(180.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.2f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "bullet";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.7f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "table";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.7f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "eagle";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.7f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "eagle";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.7f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "eagle";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.5f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "eagle";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 29.5;
		pTempGO->position.z = 35;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//	pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees
		pTempGO->scale = 0.4f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		pTempGO->meshName = "eagle";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 29;
		pTempGO->position.y = 30;
		pTempGO->position.z = 34;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//pTempGO->orientation2.x = glm::radians(90.0f);// Degrees
		pTempGO->scale = 0.4f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pTempGO->meshName = "bullet";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 30;
		pTempGO->position.y = 30;
		pTempGO->position.z = 34;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//pTempGO->orientation2.x = glm::radians(90.0f);// Degrees
		pTempGO->scale = 0.4f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pTempGO->meshName = "bullet";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 31;
		pTempGO->position.y = 30;
		pTempGO->position.z = 30;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//pTempGO->orientation2.x = glm::radians(90.0f);// Degrees
		pTempGO->scale = 0.4f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pTempGO->meshName = "bullet";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 32;
		pTempGO->position.y = 30;
		pTempGO->position.z = 34;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
														//pTempGO->orientation2.x = glm::radians(90.0f);// Degrees
		pTempGO->scale = 0.4f;
		pTempGO->diffuseColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pTempGO->meshName = "bullet";
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	//{
	//	cGameObject* pTempGO = new cGameObject();
	//	pTempGO->position.x = -0.5f;
	//	pTempGO->position.y = -2.0f;
	//	pTempGO->orientation.z = glm::degrees(0.0f);	// Degrees
	//	pTempGO->orientation2.z = glm::degrees(0.0f);	// Degrees
	//	pTempGO->scale = 1.0f;
	//	pTempGO->diffuseColour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
	//	pTempGO->meshName = "bunny";
	//	//
	//	//pTempGO->vel.y = 1.0f;
	//	//
	//	::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
	//}	

	{
		cGameObject* pTempGO = new cGameObject();
		pTempGO->position.x = 30;
		pTempGO->position.y = 30.1;
		pTempGO->position.z = 30;
		pTempGO->orientation.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.z = glm::radians(0.0f);	// Degrees
		pTempGO->orientation2.x = glm::radians(270.0f);	// Degrees
		pTempGO->orientation2.y = glm::radians(180.0f);	// Degrees
		//pTempGO->orientation2.x = glm::radians(90.0f);// Degrees
		pTempGO->scale = 1.0f;
		pTempGO->diffuseColour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		pTempGO->meshName = "plane";
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
	}



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// C++ string
	// C no strings. Sorry. char    char name[7] = "Michael\0";
    window = glfwCreateWindow( width, height, 
							   title.c_str(), 
							   NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

	std::cout << glGetString(GL_VENDOR) << " " 
		<< glGetString(GL_RENDERER) << ", " 
		<< glGetString(GL_VERSION) << std::endl;
	std::cout << "Shader language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Read the ply file...
//	if ( ! LoadPlyObject( "bun_zipper_res4.ply" ) )
//	if ( ! LoadPlyObject( "bun_zipper_res3.ply" ) )
//	{
//		std::cout << "Could not read the ply model file" << std::endl;
//	}



	//

	::g_pShaderManager = new cShaderManager();

	cShaderManager::cShader vertShader;
	cShaderManager::cShader fragShader;

	vertShader.fileName = "simpleVert.glsl";	
	fragShader.fileName = "simpleFrag.glsl"; 

	::g_pShaderManager->setBasePath( "assets//shaders//" );

	// Shader objects are passed by reference so that
	//	we can look at the results if we wanted to. 
	if ( ! ::g_pShaderManager->createProgramFromFile(
		        "mySexyShader", vertShader, fragShader ) )
	{
		std::cout << "Oh no! All is lost!!! Blame Loki!!!" << std::endl;
		std::cout << ::g_pShaderManager->getLastError() << std::endl;
		// Should we exit?? 
		return -1;	
//		exit(
	}
	std::cout << "The shaders comipled and linked OK" << std::endl;


	// Load models
	::g_pVAOManager = new cVAOMeshManager();

	GLint sexyShaderID = ::g_pShaderManager->getIDFromFriendlyName("mySexyShader");

	{
		cMesh testMesh;
		testMesh.name = "table";
		if ( ! LoadPlyFileIntoMesh( "Table.ply", testMesh ) )
		{ 
			std::cout << "Didn't load model" << std::endl;
			// do something??
		}
		if ( ! ::g_pVAOManager->loadMeshIntoVAO( testMesh, sexyShaderID ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}
	}
	{
		cMesh testMesh;
		testMesh.name = "eagle";
		if (!LoadPlyFileIntoMesh("eagle.ply", testMesh))
		{
			std::cout << "Didn't load model" << std::endl;
			// do something??
		}
		if (!::g_pVAOManager->loadMeshIntoVAO(testMesh, sexyShaderID))
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}
	}
	{
		cMesh testMesh;
		testMesh.name = "gun";
		if ( ! LoadPlyFileIntoMesh( "Rifle.ply", testMesh ) )
		{ 
			std::cout << "Didn't load model" << std::endl;
			// do something??
		}
		if ( ! ::g_pVAOManager->loadMeshIntoVAO( testMesh, sexyShaderID ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}
	}	
	{
		cMesh testMesh;
		testMesh.name = "bullet";
		if ( ! LoadPlyFileIntoMesh( "Bullet.ply", testMesh ) )
		{ 
			std::cout << "Didn't load model" << std::endl;
			// do something??
		}
		if ( ! ::g_pVAOManager->loadMeshIntoVAO( testMesh, sexyShaderID ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}
	}	// ENDOF: load models


	GLint currentProgID = ::g_pShaderManager->getIDFromFriendlyName( "mySexyShader" );

	mvp_location = glGetUniformLocation(currentProgID, "MVP");		// program, "MVP");

//    vpos_location = glGetAttribLocation(currentProgID, "vPos");		// program, "vPos");	// 6
//    vcol_location = glGetAttribLocation(currentProgID, "vCol");		// program, "vCol");	// 13
//
////	vec3 vPos,		x = 0th location in this class
////	vec3 vCol       r = 3rd location in this class
//    glEnableVertexAttribArray(vpos_location);
//	const int offsetOf_x_into_cVertex = 0;	// X is 0th location in cVertex
//    glVertexAttribPointer(vpos_location, 
//						  3,				// now vec3, not vec2   
//						  GL_FLOAT, 
//						  GL_FALSE,
//                          sizeof(float) * 6,	// cVertex is 6 floats in size
//					//	  (void*) (sizeof(float) * offsetOf_x_into_cVertex) );		
//						  (void*) offsetof( cVertex, x ) );
//
//
//    glEnableVertexAttribArray(vcol_location);
//	const int offsetOf_r_into_cVertex = 3;	// "r" is 3rd float into cVertex
//    glVertexAttribPointer(vcol_location, 
//						  3, 
//						  GL_FLOAT, 
//						  GL_FALSE,
//                          sizeof(float) * 6,		// (  sizeof(cVertex)  );
//				      //  (void*) (sizeof(float) * offsetOf_r_into_cVertex));
//						  (void*) offsetof( cVertex, r ) );

	glEnable( GL_DEPTH );

	// Gets the "current" time "tick" or "step"
	double lastTimeStep = glfwGetTime();

	// Main game or application loop
	while ( ! glfwWindowShouldClose(window) )
    {
        float ratio;
        int width, height;
        glm::mat4x4 m, p, mvp;			//  mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT );



		// "Draw scene" loop
//		for ( int index = 0; index != MAXNUMBEROFGAMEOBJECTS; index++ )
		// std::vector< cGameObject* > g_vecGameObjects;

		unsigned int sizeOfVector = ::g_vecGameObjects.size();	//*****//
		for ( int index = 0; index != sizeOfVector; index++ )
		{
			// Is there a game object? 
			if ( ::g_vecGameObjects[index] == 0 )	//if ( ::g_GameObjects[index] == 0 )
			{	// Nothing to draw
				continue;		// Skip all for loop code and go to next
			}

			// Was near the draw call, but we need the mesh name
			std::string meshToDraw = ::g_vecGameObjects[index]->meshName;		//::g_GameObjects[index]->meshName;

			sVAOInfo VAODrawInfo;
			if ( ::g_pVAOManager->lookupVAOFromName( meshToDraw, VAODrawInfo ) == false )
			{	// Didn't find mesh
				continue;
			}



			// There IS something to draw

			m = glm::mat4x4(1.0f);	//		mat4x4_identity(m);

			//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	//		float curTime = (float) glfwGetTime();
	//		glm::rotate( m, curTime, glm::vec3(0.0f, 0.0f, 1.0f) );
	//		glm::rotate( m, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f) );	// Stop bunny

			glm::mat4 matRreRotZ = glm::mat4x4(1.0f);
			matRreRotZ = glm::rotate( matRreRotZ, ::g_vecGameObjects[index]->orientation.z, 
								     glm::vec3(0.0f, 0.0f, 1.0f) );
			m = m * matRreRotZ;

			glm::mat4 trans = glm::mat4x4(1.0f);
			trans = glm::translate( trans, 
								    ::g_vecGameObjects[index]->position );
			m = m * trans; 

			glm::mat4 matPostRotZ = glm::mat4x4(1.0f);
			matPostRotZ = glm::rotate( matPostRotZ, ::g_vecGameObjects[index]->orientation2.z, 
						     glm::vec3(0.0f, 0.0f, 1.0f) );
			m = m * matPostRotZ;

		
			glm::mat4 matPostRotY = glm::mat4x4(1.0f);
			matPostRotY = glm::rotate( matPostRotY, ::g_vecGameObjects[index]->orientation2.y, 
							     glm::vec3(0.0f, 1.0f, 0.0f) );
			m = m * matPostRotY;


			glm::mat4 matPostRotX = glm::mat4x4(1.0f);
			matPostRotX = glm::rotate( matPostRotX, ::g_vecGameObjects[index]->orientation2.x, 
								     glm::vec3(1.0f, 0.0f, 0.0f) );
			m = m * matPostRotX;
			// TODO: add the other rotation matrix (i.e. duplicate code above)

			// assume that scale to unit bounding box
			// ************* BEWARE *****************
			float finalScale = VAODrawInfo.scaleForUnitBBox * ::g_vecGameObjects[index]->scale;

			glm::mat4 matScale = glm::mat4x4(1.0f);
			matScale = glm::scale( matScale, 
								   glm::vec3( finalScale,
								              finalScale,
								              finalScale ) );
			m = m * matScale;


			//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//			p = glm::ortho( -1.0f, 1.0f, -1.0f, 1.0f );
			p = glm::perspective( 0.6f,			// FOV
								  ratio,		// Aspect ratio
								  0.1f,			// Near (as big as possible)
								  1000.0f );	// Far (as small as possible)

			// View or "camera" matrix
			glm::mat4 v = glm::mat4(1.0f);	// identity

			//glm::vec3 cameraXYZ = glm::vec3( 0.0f, 0.0f, 5.0f );	// 5 units "down" z
			v = glm::lookAt( g_cameraXYZ,						// "eye" or "camera" position
							 g_cameraTarget_XYZ,		// "At" or "target" 
							 glm::vec3( 0.0f, 1.0f, 0.0f ) );	// "up" vector

			//mat4x4_mul(mvp, p, m);
//			mvp = p * m;
//			mvp = m * v * p;			// <---- this way
			mvp = p * v * m;			// This way (sort of backwards)

			GLint shaderID = ::g_pShaderManager->getIDFromFriendlyName("mySexyShader");
			GLint diffuseColour_loc = glGetUniformLocation( shaderID, "diffuseColour" );

			glUniform4f( diffuseColour_loc, 
						::g_vecGameObjects[index]->diffuseColour.r, 
						::g_vecGameObjects[index]->diffuseColour.g, 
						::g_vecGameObjects[index]->diffuseColour.b, 
						::g_vecGameObjects[index]->diffuseColour.a );


	//        glUseProgram(program);
			::g_pShaderManager->useShaderProgram( "mySexyShader" );

			//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, 
			//                 (const GLfloat*) mvp);
			glUniformMatrix4fv(mvp_location, 1, GL_FALSE, 
							   (const GLfloat*) glm::value_ptr(mvp) );

	//		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );	// Default

			//glDrawArrays(GL_TRIANGLES, 
			//			 0,			// Start at vertex #0
			//			 testMesh.numberOfVertices );	// g_numberOfVertices);		//453	// 3);		// Draw 3 vertices

//			// Lookup the mesh we are supposed to draw...
//			std::string meshToDraw = ::g_GameObjects[index]->meshName;
//
//			sVAOInfo VAODrawInfo;
//			if ( ::g_pVAOManager->lookupVAOFromName( meshToDraw, VAODrawInfo ) )
//			{	// We found one!!!

				glBindVertexArray( VAODrawInfo.VAO_ID );

				glDrawElements( GL_TRIANGLES, 
								VAODrawInfo.numberOfIndices,		// testMesh.numberOfTriangles * 3,	// How many vertex indices
								GL_UNSIGNED_INT,					// 32 bit int 
								0 );

				glBindVertexArray( 0 );

//			}// if ( ::g_pVAOManager->lookupVAOFromName(

		}//for ( int index = 0...


		std::stringstream ssTitle;
		ssTitle << "Camera (xyz): " 
			<< g_cameraXYZ.x << ", " 
			<< g_cameraXYZ.y << ", " 
			<< g_cameraXYZ.z;
		glfwSetWindowTitle( window, ssTitle.str().c_str() );

        glfwSwapBuffers(window);
        glfwPollEvents();

		
		// Essentially the "frame time"
		// Now many seconds that have elapsed since we last checked
		double curTime = glfwGetTime();
		double deltaTime =  curTime - lastTimeStep;

		//PhysicsStep( deltaTime );

		//g_vecGameObjects[0]->position.x = 0.0f;
		
		float x1=13, y1=13, z1=13;
		
			
		
	//	g_vecGameObjects[0]->position.y += 0.01;
		
		//pTempGO->position.x = 0.0f;
		//pTempGO->orientation.z = glm::degrees(0.0f);	// Degrees
		//pTempGO->orientation2.z = glm::degrees(45.0f);	// Degrees










		L = lua_open();

		/* load Lua base libraries */
		luaL_openlibs(L);

		/* register our function */
		lua_register(L, "MoveTo", MoveTo);
		lua_register(L, "MoveToGrouped", MoveToAfter);
		lua_register(L, "OrientTo", OrientTo);
		lua_register(L, "OrientToWith", OrientToWith);
		lua_register(L, "OrientToGrouped", OrientToAfter);
		lua_register(L, "MoveToWith", MoveToWith);


		lua_register(L, "MoveCameraTo", MoveCameraTo);
		//lua_register(L, "FollowToAfter", FollowToAfter);
		luaL_dofile(L, "avg.lua");




		lastTimeStep = curTime;

		// floating point example
		//::g_cameraXYZ.z += 10.0f;

		//::g_vecGameObjects[1]->position = ::g_cameraXYZ;
		//::g_vecGameObjects[1]->position.z -= 3.0f; 
		//::g_vecGameObjects[1]->position.y = -0.5f;



    }// while ( ! glfwWindowShouldClose(window) )


    glfwDestroyWindow(window);
    glfwTerminate();

	// 
	delete ::g_pShaderManager;
	delete ::g_pVAOManager;

//    exit(EXIT_SUCCESS);
	return 0;
}

// Update the world 1 "step" in time
void PhysicsStep( double deltaTime )
{
	// Distance                          m
	// Velocity = distance / time		 m/s
	// Accleration = velocity / time     m/s/s

	// Distance = time * velocity
	// velocity = time * acceleration

	const glm::vec3 GRAVITY = glm::vec3(0.0f, -1.0f, 0.0f);

	// Identical to the 'render' (drawing) loop
	for ( int index = 0; index != ::g_vecGameObjects.size(); index++ )
	{
		cGameObject* pCurGO = ::g_vecGameObjects[index];

		// New position is based on velocity over time
		glm::vec3 deltaPosition = (float)deltaTime * pCurGO->vel;
		pCurGO->position += deltaPosition;

		// New velocity is based on acceleration over time
		glm::vec3 deltaVelocity =  ( (float)deltaTime * pCurGO->accel )
			                     + ( (float)deltaTime * GRAVITY );

		pCurGO->vel += deltaVelocity;


		// HACK: Collision step
		// Assume the "ground" is -2.0f from the origin in the y
		if ( pCurGO->position.y <= -2.0f )
		{	// Object has "hit" the ground
			pCurGO->vel.y = -pCurGO->vel.y;
		}




	}//for ( int index...



	return;
}
