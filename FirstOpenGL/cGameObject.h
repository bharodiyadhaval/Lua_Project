#ifndef _cGameObject_HG_
#define _cGameObject_HG_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>

class cGameObject
{
public:
	cGameObject();		// constructor
	~cGameObject();		// destructor
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 orientation2;		// HACK (will elimiate this with)
	float scale;

	// Add some physics things
	glm::vec3 vel;			// Velocity
	glm::vec3 accel;		// Acceleration

	glm::vec4 diffuseColour;	// 

	std::string meshName;		// mesh I'd like to draw
};

#endif
