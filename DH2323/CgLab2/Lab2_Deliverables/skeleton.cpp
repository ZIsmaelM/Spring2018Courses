#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

#include <unistd.h>

using namespace std;
using glm::vec3;
using glm::mat3;

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
SDL_Surface* screen;
int t;

vector<Triangle> triangles;
float focalLength;
float alpha = 2 * atan(((float)SCREEN_HEIGHT/2) / (float)SCREEN_WIDTH);

//camera
float speed = 0.1;
float yaw = M_PI/8;
int axis = 0;
float degreeH = 0;
float degreeV = 0;
vec3 rotRight = vec3(cos(yaw),0,sin(yaw));
vec3 rotDown = vec3(0,1,0);
vec3 rotForward = vec3(-sin(yaw),0,cos(yaw));
float camX = 0;
float camY = 0;
float camZ = -3;
vec3 camOrig = vec3(camX,camY,camZ);
vec3 cameraPos = vec3(camX,camY,camZ);	// -1 to 1 in x,y,z coords

//light
vec3 lightPos(0,-0.5,-0.7);
vec3 lightColor = 14.f * vec3(1,1,1);
vec3 indirectLight = 0.5f*vec3( 1, 1, 1 );
// ----------------------------------------------------------------------------
// STRUCTS

struct Ray {
	vec3 orig;
	vec3 dir;
};

struct Intersection {
	vec3 pos;
	float dist;
	int index;
};

// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();
bool ClosestIntersection(Ray ray, const vector<Triangle>& triangles, Intersection& closestIntersection);
vec3 DirectLight(const Intersection& i);
vec3 DirectLightOther(const Intersection& i);

float ComputeDistance(vec3 v, vec3 u) {
	float a = pow(u[0]-v[0],2);
	float b = pow(u[1]-v[1],2);
	float c = pow(u[2]-v[2],2);

	return float(sqrt(a + b + c));
}

void Rotate(vec3& v) {

	// calculate rotation around x-axis
	rotRight = vec3(1, 0, 0);
	rotDown = vec3(0, cos(degreeV), -sin(degreeV));
	rotForward = vec3(0, sin(degreeV), cos(degreeV));

	float rotX = glm::dot(rotRight, v);
	float rotY = glm::dot(rotDown, v);
	float rotZ = glm::dot(rotForward, v);

	v = vec3(rotX, rotY, rotZ);

	// calculate rotation around y-axis
	rotRight = vec3(cos(degreeH), 0, sin(degreeH));
	rotDown = vec3(0, 1, 0);
	rotForward = vec3(-sin(degreeH), 0, cos(degreeH));

	rotX = glm::dot(rotRight, v);
	rotY = glm::dot(rotDown, v);
	rotZ = glm::dot(rotForward, v);

	v = vec3(rotX, rotY, rotZ);
}

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	LoadTestModel (triangles);
	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
		// usleep(51000000);	// delay for 51s between frames
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;

	Uint8* keystate = SDL_GetKeyState( 0 );

//Camera movement

	// reset view
	if( keystate[SDLK_r] ) {
		degreeV = 0;
		degreeH = 0;
		cameraPos = camOrig;
	}

	// rotate along x-axis
	if( keystate[SDLK_UP] ) {
		degreeV += yaw;
		cameraPos = camOrig;
		Rotate(cameraPos);
	}
	if( keystate[SDLK_DOWN] ) {
		degreeV -= yaw;
		cameraPos = camOrig;
		Rotate(cameraPos);
	}

	// rotate along y-axis
	if( keystate[SDLK_LEFT] ) {
		degreeH -= yaw;
		cameraPos = camOrig;
		Rotate(cameraPos);
	}
	if( keystate[SDLK_RIGHT] ) {
		degreeH += yaw;
		cameraPos = camOrig;
		Rotate(cameraPos);
	}

//Light source movement
	float lightSpeed = 0.1;

	// move along z-axis
	if( keystate[SDLK_w] ) {
		lightPos.z += lightSpeed;
	}
	if( keystate[SDLK_s] ) {
		lightPos.z -= lightSpeed;
	}

	// move along x-axis
	if( keystate[SDLK_a] ) {
		lightPos.x -= lightSpeed;
	}
	if( keystate[SDLK_d] ) {
		lightPos.x += lightSpeed;
	}

	// move along y-axis
	if( keystate[SDLK_q] ) {
		lightPos.y -= lightSpeed;
	}
	if( keystate[SDLK_e] ) {
		lightPos.y += lightSpeed;
	}
}

void Draw()
{
	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);

	Intersection pixel;
	Ray ray;

	focalLength = SCREEN_HEIGHT / (2 * tan(alpha/2));
	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			// create the ray
			ray.orig = cameraPos;
			ray.dir = vec3(x-SCREEN_WIDTH/2, (y-SCREEN_HEIGHT/2), focalLength);
			ray.dir = glm::normalize(ray.dir);
			Rotate(ray.dir);

			vec3 color = vec3(0,0,0);

			// set the color to the color of the closest intersecting triangle
			if(ClosestIntersection(ray, triangles, pixel)) {
				Triangle tri = triangles[pixel.index];
				vec3 light = DirectLight(pixel);
				color = (light+indirectLight)*tri.color;//tri.color;
			}

			PutPixelSDL( screen, x, y, color );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

bool ClosestIntersection(Ray ray, const vector<Triangle>& triangles, Intersection& closestIntersection) {

	float closestDist = std::numeric_limits<float>::max();
	bool intersectDetected = false;

	for(int i = 0; i < triangles.size(); i++) {
		vec3 v0 = triangles[i].v0;
		vec3 v1 = triangles[i].v1;
		vec3 v2 = triangles[i].v2;
		vec3 e1 = v1 - v0;
		vec3 e2 = v2 - v0;
		vec3 b = ray.orig - v0;
		mat3 A( -ray.dir, e1, e2 );
		vec3 x = glm::inverse( A ) * b;

		// check if the ray intersects the triangle
		if(x[0] >= 0 && x[1] >= 0 && x[2] >= 0 && x[1]+x[2] <= 1) {
			vec3 intersect = ray.orig + x[0]*ray.dir;
			float dist = ComputeDistance(ray.orig, intersect);

			// update the intersection data if a closer intersection was found
			if (dist < closestDist) {
				closestDist = dist;
				closestIntersection.pos = intersect;
				closestIntersection.dist = dist;
				closestIntersection.index = i;
			}
			intersectDetected = true;

		}
	}

	return intersectDetected;
}

vec3 DirectLight(const Intersection& i) {

	// offset value to prevent false shadow detections
	float tShadow = 0.001f;

	Triangle t = triangles[i.index];
	float r = ComputeDistance(i.pos,lightPos);
	float A = 4*M_PI*pow(r,2);
	
	vec3 B = lightColor / A;
	
	// initialize the shadowRay
	Ray shadowRay;
	if (i.pos[0] - tShadow <= -1 || i.pos[1] - tShadow <= -1)
		shadowRay.orig = i.pos + tShadow;
	else
		shadowRay.orig = i.pos - tShadow;

	shadowRay.dir = lightPos - shadowRay.orig;
	shadowRay.dir = glm::normalize(shadowRay.dir);	
	float rayNormMax = std::max(0.f,glm::dot(t.normal,shadowRay.dir));

	// check if our shadowRay is indeed a shadow (if it is blocked from the light)
	Intersection objectIntersect;
	if (ClosestIntersection(shadowRay, triangles, objectIntersect)) {
		if(objectIntersect.dist < r)
			return vec3(0,0,0);
	}
	vec3 D = B*rayNormMax;

	return D;
}

void InterpolateVec3( vec3 a, vec3 b, vector<vec3>& result) {
	int numSamples = result.size();
	int numPoints = 3;

	int dist;
	for (int i = 0; i < numSamples; ++i) {
		for (int j = 0; j < numPoints; ++j) {
			float dist = b[j] - a[j];
			float t = ((float)i/(numSamples-1)) * dist;
			result[i][j] = a[j] + t;
		}
	}
}
