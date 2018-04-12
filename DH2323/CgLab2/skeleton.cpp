#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

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
int focalLength = 0.025;
vec3 cameraPos(0,0,-400);
float maxFloat = std::numeric_limits<float>::max();

// ----------------------------------------------------------------------------
// FUNCTIONS

struct IntersectInfo
{
	vec3 position;
	float distance = maxFloat;
	int triangleIndex;
};

// struct Ray
// {
// 	vec3 orig;
// 	vec3 dir;
// 	float distance;
// };

void Update();
void Draw();
void TriangleIntersect();
bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, IntersectInfo& ClosestIntersection);

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	int i = 5;
	while( NoQuitMessageSDL() )
	{
		if (i > 0) Update();
		Draw();
		i--;
		cout << "render finished" << endl;
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

	//TriangleIntersect();
	LoadTestModel(triangles);
	for( int y=0; y<SCREEN_HEIGHT; ++y ) {
		for( int x=0; x<SCREEN_WIDTH; ++x ) {

			vec3 rayOrig = cameraPos; //vec3(x,y,-focalLength);
			vec3 rayDir = vec3(x-(SCREEN_WIDTH/2), y-(SCREEN_HEIGHT/2), focalLength);
			IntersectInfo intersect;

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
	cout << "waiting for input..." << endl;
	//getchar();
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

	vec3 e1 = t.v1 - t.v0;
	vec3 e2 = t.v2 - t.v0;

	// s + td = v0 + u*e1 + v*e2
	// s - v0 = u*e1 + v*e2 - td
	vec3 b = rayOrig - t.v0;
	//cout << b[0] << "	" << b[1] << "	" << b[2] << endl;
	mat3 A( -rayDir, e1, e2);
	vec3 x = glm::inverse(A) * b; // (t u v)

	//cout << "x: (" << x[0] << "	,	" << x[1] << "	,	" << x[2] << ")" << endl;
	//getchar();
	// do not update intersection if ray does not intersect triangle
	if (x[0] <= 0 || x[1] <= 0 || x[2] <= 0 || x[1] + x[2] >= 1)
		return rayTri;

	rayTri.position = x;
	rayTri.distance = abs(x[0]);
	//cout << x[0] << endl;
	//cout << rayTri.distance << endl;
	rayTri.triangleIndex = index;
	return rayTri;

// ALTERNATE IMPLEMENTATION \\
	// P = O + tR
	// Ax + By + Cz + D = 0
	// for(int i = 0; i < triangles.size(); i++) {
	// 	Ray ray;

	// 	// compute vectors parallel to triangle edges
	// 	vec3 e0 = triangles[i].v1 - triangles[i].v0;
	// 	vec3 e1 = triangles[i].v2 - triangles[i].v0;

	// 	// compute distance from scene origin
	// 	float D = glm::dot(triangles[i].normal, triangles[i].v0);

	// 	float t = - (glm::dot(triangles[i].normal, ray.orig) + D) / glm::dot(triangles[i].normal, ray.dir);
	// }
}

bool ClosestIntersection(
	vec3 start,
	vec3 dir,
	const vector<Triangle>& triangles,
	IntersectInfo& ClosestIntersection) {

	//LoadTestModel(triangles);

	//float maxFloat = std::numeric_limits<float>::max();

	ClosestIntersection.distance = maxFloat;
	ClosestIntersection.triangleIndex = -1;

	bool foo = false;
	for (int i = 0; i < triangles.size(); i++) {
		IntersectInfo newIntersection = TriangleIntersect(triangles, i, start, dir);
		if (newIntersection.distance < ClosestIntersection.distance) {
			ClosestIntersection = newIntersection;
			foo = true;
		}
	}

	if (foo) {
		cout << "Intersect" << endl;	
		return true;

	}

	return false;
}