#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::ivec2;
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
vec3 cameraPos(0,0,-3.001);
vec3 cameraOrig = cameraPos;

mat3 R;
float yaw = M_PI/256;
int axis = 0;
float degreeH = 0;
float degreeV = 0;
vec3 rotRight = vec3(cos(degreeH), 0, sin(degreeH));
vec3 rotDown = vec3(0, 1, 0);
vec3 rotForward = vec3(-sin(degreeH), 0, cos(degreeH));
// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();
void VertexShader(const vec3&, ivec2&);
void DrawPolygonEdges(const vector<vec3>&);

int main( int argc, char* argv[] )
{
	LoadTestModel( triangles );
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Rotate(vec3& v) {
	// testAngle += yaw;
	if (axis == 0) {
		rotRight = vec3(1, 0, 0);
		rotDown = vec3(0, cos(degreeV), -sin(degreeV));
		rotForward = vec3(0, sin(degreeV), cos(degreeV));
	} else {
		rotRight = vec3(cos(degreeH), 0, sin(degreeH));
		rotDown = vec3(0, 1, 0);
		rotForward = vec3(-sin(degreeH), 0, cos(degreeH));
	}

	float rotX = glm::dot(rotRight, v);
	float rotY = glm::dot(rotDown, v);
	float rotZ = glm::dot(rotForward, v);

	v = vec3(rotX, rotY, rotZ);
}

void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;

	Uint8* keystate = SDL_GetKeyState(0);

	if( keystate[SDLK_UP] ) {
		degreeV += yaw;
		axis = 0;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}
	if( keystate[SDLK_DOWN] ) {
		degreeV -= yaw;
		axis = 0;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}

	if( keystate[SDLK_RIGHT] ) {
		degreeH += yaw;
		axis = 1;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}

	if( keystate[SDLK_LEFT] ) {
		degreeH -= yaw;
		axis = 1;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}

	if( keystate[SDLK_RSHIFT] )
		;

	if( keystate[SDLK_RCTRL] )
		;

	// //Light source movement
	// float lightSpeed = 0.1;
	// if( keystate[SDLK_w] ) {
	// 	lightPos.z += lightSpeed;
	// }
	// if( keystate[SDLK_s] ) {
	// 	lightPos.z -= lightSpeed;
	// }
	// if( keystate[SDLK_a] ) {
	// 	lightPos.x -= lightSpeed;
	// }
	// if( keystate[SDLK_d] ) {
	// 	lightPos.x += lightSpeed;
	// }
	// if( keystate[SDLK_q] ) {
	// 	lightPos.y -= lightSpeed;
	// }
	// if( keystate[SDLK_e] ) {
	// 	lightPos.y += lightSpeed;
	// }
	// cameraPos = cameraOrig;
	// Rotate(cameraPos);
}

void Draw()
{
	SDL_FillRect( screen, 0, 0 );

	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
	
	focalLength = SCREEN_HEIGHT / (2 * tan(alpha/2));
	for( int i=0; i<triangles.size(); ++i )
	{
		vector<vec3> vertices(3);

		// Rotate(triangles[i].v0);
		// Rotate(triangles[i].v1);
		// Rotate(triangles[i].v2);

		vertices[0] = triangles[i].v0;
		vertices[1] = triangles[i].v1;
		vertices[2] = triangles[i].v2;

		// Draw edges
		DrawPolygonEdges(vertices);

		// // Draw vertices
		// for(int v = 0; v < 3; ++v) {
		// 	ivec2 projPos;
		// 	VertexShader(vertices[v], projPos);
		// 	vec3 color(1,1,1);
		// 	PutPixelSDL(screen, projPos.x, projPos.y, color);
		// }
	}
	
	if ( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void VertexShader(const vec3& v, ivec2& p) {

	vec3 picturePlane = v;
	Rotate(picturePlane);

	picturePlane.x = picturePlane.x - cameraOrig.x;
	picturePlane.y = picturePlane.y - cameraOrig.y;
	picturePlane.z = picturePlane.z - cameraOrig.z;

	p.x = focalLength * (picturePlane.x / picturePlane.z) + (SCREEN_WIDTH/2);
	p.y = focalLength * (picturePlane.y / picturePlane.z) + (SCREEN_HEIGHT/2);
}

void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result) {
	int numSamples = result.size();
	int numPoints = 2;

	int dist;
	for (int i = 0; i < numSamples; ++i) {
		for (int j = 0; j < numPoints; ++j) {
			float dist = b[j] - a[j];
			float t = ((float)i/(numSamples-1)) * dist;
			result[i][j] = a[j] + t;
		}
	}
}

void DrawLineSDL(SDL_Surface* surface, ivec2 a, ivec2 b, vec3 color) {
	
	ivec2 delta = glm::abs(a-b);
	int pixels = glm::max(delta.x, delta.y) + 1;
	vector<ivec2> line(pixels);
	Interpolate(a,b,line);
	for(int i=0; i<line.size(); ++i) {
		PutPixelSDL(surface, line[i].x, line[i].y, color);
	}
}

void DrawPolygonEdges(const vector<vec3>& vertices) {
	int V = vertices.size();
	// Transform each vertex from 3D world position to 2D image position
	vector<ivec2> projectedVertices(V);
	for(int i=0; i<V; ++i) {
		VertexShader(vertices[i], projectedVertices[i]);
	}

	// Loop over all vertices and draw the edge from it to the next vertex
	for(int i=0; i<V; ++i) {
		int j = (i+1)%V; // The next vertex
		vec3 color(1,1,1);
		DrawLineSDL(screen, projectedVertices[i], projectedVertices[j], color);

	}
}