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
int focalLength = 1;//(SCREEN_WIDTH/2) / tan(45/2);
vec3 cameraPos(0,0,-focalLength);
float maxFloat = std::numeric_limits<float>::max();

// ----------------------------------------------------------------------------
// FUNCTIONS

// Object that stores intersection data
struct IntersectInfo
{
	vec3 position;
	float distance = maxFloat;
	int triangleIndex;
};

void Update();
void Draw();
void TriangleIntersect();
bool IsEqual(vec3 A, vec3 B);
bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, IntersectInfo& ClosestIntersection);

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
		cout << "render finished" << endl;
		usleep(25000000);	// delay for 25s
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

	// generate triangles
	LoadTestModel(triangles);
	for( int y=0; y<SCREEN_HEIGHT; ++y ) {
		for( int x=0; x<SCREEN_WIDTH; ++x ) {

			// set ray direction and origin
			vec3 rayOrig = cameraPos;
			vec3 rayDir = vec3(x-(SCREEN_WIDTH/2), y-(SCREEN_HEIGHT/2), focalLength);
			IntersectInfo intersect;

			// check if an intersection was found
			bool foo = ClosestIntersection(rayOrig, rayDir, triangles, intersect);
			vec3 color(0,0,0);
			if (foo) {
				// cout << "rayOrig: (" << rayOrig.x << "," << rayOrig.y << "," << rayOrig.z << ")" << endl;
				// cout << "rayDir: (" << rayDir.x << "," << rayDir.y << "," << rayDir.z << ")" << endl;	
				// cout << "index: " << intersect.triangleIndex << endl;	
				color = triangles[intersect.triangleIndex].color;
			}

			//vec3 color( 1, 0.5, 0.5 );
			PutPixelSDL( screen, x, y, color );
		}
		//cout << "Finished row: " << y << endl;
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

IntersectInfo TriangleIntersect(const vector<Triangle>& triangles, 
	int index, 
	vec3 rayOrig, 
	vec3 rayDir) {

	// points on a ray: r = s + td
	// s = ray orig
	// d = ray dir
	// t = pos on line (t >= 0)

	// points on a triangle: r = v0 + u*e1 + v*e2
	// v0 = coordinate system origin
	// e1 & e2 = vectors parallel to triangle edges
	// u & v = scalar values between 0 and 1, and u + v < 1

	Triangle t = triangles[index];
	IntersectInfo rayTri;

	// calculate vectors parallel to triangle edges
	vec3 e1 = t.v1 - t.v0;
	vec3 e2 = t.v2 - t.v0;

	// s + td = v0 + u*e1 + v*e2
	// s - v0 = u*e1 + v*e2 - td
	vec3 b = rayOrig - t.v0;
	//cout << b[0] << "	" << b[1] << "	" << b[2] << endl;
	mat3 A( -rayDir, e1, e2);
	vec3 x = glm::inverse(A) * b; // (t u v)

	// do not update intersection if ray does not intersect triangle
	if (x[0] < 0 || x[1] < 0 || x[2] < 0 || x[1] + x[2] > 1)
		return rayTri;

	rayTri.position = x;
	rayTri.distance = abs(x[0]);
	rayTri.triangleIndex = index;
	return rayTri;

}

bool ClosestIntersection(
	vec3 start,
	vec3 dir,
	const vector<Triangle>& triangles,
	IntersectInfo& ClosestIntersection) {

	// set default intersect data
	ClosestIntersection.distance = maxFloat;
	ClosestIntersection.triangleIndex = -1;

	bool foo = false;

	// check if ray intersects any of the triangles
	for (int i = 0; i < triangles.size(); i++) {
		IntersectInfo newIntersection = TriangleIntersect(triangles, i, start, dir);

		//cout << triangles[i].color << endl;
		//cout << triangles[i].color[0] << "	" << triangles[i].color[1] << "	" << triangles[i].color[2] << endl;

		// set new closest intersection if this triangle is closer than the previous closest
		if (newIntersection.distance < ClosestIntersection.distance) {
			vec3 gray = vec3(0.75,0.7385,0.75);
			bool test = IsEqual(triangles[i].color, gray);
			ClosestIntersection = newIntersection;
			foo = true;
		}
	}

	if (foo) {
		//cout << "Intersect" << endl;	
		return true;

	}

	return false;
}

bool IsEqual(vec3 A, vec3 B) {
	if (A[0] == B[0] && A[1] == B[1] && A[2] == B[2])
		return true;

	return false;
}