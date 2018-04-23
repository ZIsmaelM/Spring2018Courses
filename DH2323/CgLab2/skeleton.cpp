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
float focalLength = 1;	//SCREEN_HEIGHT/2;
float alpha = 2 * atan(((float)SCREEN_HEIGHT/2) / (float)SCREEN_WIDTH);	//
vec3 cameraPos = vec3(0,0,-3);	// -1 to 1 in x,y,z coords

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

float ComputeDistance(vec3 v, vec3 u) {
	float a = pow(u[0]-v[0],2);
	float b = pow(u[1]-v[1],2);
	float c = pow(u[2]-v[2],2);

	return float(sqrt(a + b + c));
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
		cout << "Finished Rendering" << endl;
		usleep(51000000);	// delay for 51s
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
}

void Draw()
{
	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);

	Intersection pixel;
	Ray ray;

	focalLength = SCREEN_HEIGHT / (2 * tan(alpha/2));
	cout << alpha << endl;
	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			// float dirX = (2 * ((x + 0.5) * (1/SCREEN_WIDTH)) - 1) * angle;
			// float dirY = (1 - 2 * ((y + 0.5) * (1/SCREEN_HEIGHT))) * angle; 
			ray.orig = cameraPos;
			ray.dir = vec3(x-SCREEN_WIDTH/2, (y-SCREEN_HEIGHT/2), focalLength);

			vec3 color = vec3(0,0,0);
			if(ClosestIntersection(ray, triangles, pixel)) {
				Triangle tri = triangles[pixel.index];
				color = tri.color;

				// broken af
				// x = focalLength * (tri.normal.x/tri.normal.z) + (SCREEN_WIDTH/2);
				// y = focalLength * (tri.normal.y/tri.normal.z) + (SCREEN_HEIGHT/2);
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

		if(x[0] >= 0 && x[1] >= 0 && x[2] >= 0 && x[1]+x[2] <= 1) {
			vec3 intersect = ray.orig + x[0]*ray.dir;
			float dist = ComputeDistance(ray.orig, intersect);

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
