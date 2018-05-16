#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

#include <unistd.h>

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

float angle = M_PI/256;
int axis = 0;
float yaw = 0;
float pitch = 0;
vec3 rotRight;
vec3 rotDown;
vec3 rotForward;
mat3 axisV(0,0,0,0,0,0,0,0,0);
mat3 axisH(0,0,0,0,0,0,0,0,0);

vec3 currentColor(0.2,0.2,0.2);

float depthBuffer[SCREEN_HEIGHT][SCREEN_WIDTH]; 
// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();
void DrawTest();
void DrawPolygonEdges(const vector<vec3>&);
void DrawPolygon(const vector<vec3>&);
void VertexShader(const vec3&, ivec2&);

struct Pixel { 
	int x; 
	int y; 
	float zinv; 
}; 

int main( int argc, char* argv[] ) {
	LoadTestModel( triangles );
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
		//usleep(51000000); // sleep for 51s
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Rotate(vec3& v) {
	// testAngle += angle;
	if (axis == 0) {
		rotRight = vec3(1, 0, 0);
		rotDown = vec3(0, cos(pitch), -sin(pitch));
		rotForward = vec3(0, sin(pitch), cos(pitch));
		axisV = mat3(rotRight,rotDown,rotForward);
	} else {
		rotRight = vec3(cos(yaw), 0, sin(yaw));
		rotDown = vec3(0, 1, 0);
		rotForward = vec3(-sin(yaw), 0, cos(yaw));
		axisH = mat3(rotRight,rotDown,rotForward);
	}

	mat3 rot = mat3(rotRight, rotDown, rotForward);	//axisV + axisH;
	float rotX = glm::dot(rot[0], v);
	float rotY = glm::dot(rot[1], v);
	float rotZ = glm::dot(rot[2], v);

	v = vec3(rotX, rotY, rotZ);
}

void ClearZBuff() {
	for(int y=0; y<SCREEN_HEIGHT; ++y) {
		for(int x=0; x<SCREEN_WIDTH; ++x) {
			depthBuffer[y][x] = 0;
		}
	}
}
void Update() {
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;

	Uint8* keystate = SDL_GetKeyState(0);
	if( keystate[SDLK_r] ) {
		yaw = 0;
		pitch = 0;
		cameraPos = cameraOrig;
	}
	if( keystate[SDLK_UP] ) {
		pitch += angle;
		axis = 0;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}
	if( keystate[SDLK_DOWN] ) {
		pitch -= angle;
		axis = 0;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}

	if( keystate[SDLK_RIGHT] ) {
		yaw += angle;
		axis = 1;
		cameraPos = cameraOrig;
		Rotate(cameraPos);
	}

	if( keystate[SDLK_LEFT] ) {
		yaw -= angle;
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

void Draw() {
	SDL_FillRect( screen, 0, 0 );

	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
	
	focalLength = SCREEN_HEIGHT / (2 * tan(alpha/2));
	for( int i=0; i<triangles.size(); ++i )
	{
		vector<vec3> vertices(3);

		vertices[0] = triangles[i].v0;
		vertices[1] = triangles[i].v1;
		vertices[2] = triangles[i].v2;

		currentColor = triangles[i].color;

		//DrawPolygonEdges(vertices);
		//DrawTest();

		ClearZBuff();
		DrawPolygon(vertices);

	}
	
	if ( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void VertexShader(const vec3& v, Pixel& p) {

	vec3 picturePlane = v;
	Rotate(picturePlane);

	picturePlane.x = picturePlane.x - cameraOrig.x;
	picturePlane.y = picturePlane.y - cameraOrig.y;
	picturePlane.z = picturePlane.z - cameraOrig.z;

	p.x = focalLength * (picturePlane.x / picturePlane.z) + (SCREEN_WIDTH/2);
	p.y = focalLength * (picturePlane.y / picturePlane.z) + (SCREEN_HEIGHT/2);
	p.zinv = -(picturePlane.z); // get inverse of z
}

void Interpolate( Pixel a, Pixel b, vector<Pixel>& result) {
	// int numSamples = result.size();
	// int numPoints = 2;

	// for (int i = 0; i < numSamples; ++i) {
	// 		float dist = b[0] - a[0];
	// 		float t = ((float)i/(numSamples-1)) * dist;
	// 		result[i][0] = a[0] + t;

	// 		float dist = b[1] - a[1];
	// 		float t = ((float)i/(numSamples-1)) * dist;
	// 		result[i][1] = a[1] + t;
	// }

	int N = result.size();	
	float stepX = float(b.x - a.x) / float(glm::max(N - 1, 1));
	float stepY = float(b.y - a.y) / float(glm::max(N - 1, 1));
	float stepZinv = float(b.zinv - a.zinv) / float(glm::max(N - 1, 1));
	Pixel current(a);
	for (int i = 0; i<N; ++i) {
		current.x = a.x + i*stepX;
		current.y = a.y + i*stepY;
		current.zinv = a.zinv + i*stepZinv;
		result[i] = current;
	}
}

void DrawLineSDL(SDL_Surface* surface, Pixel a, Pixel b, vec3 color) {
	
	//Pixel delta = glm::abs(a-b);
	int numPixels = glm::abs(a.y-b.y); + 1;
	vector<Pixel> line(numPixels);
	Interpolate(a,b,line);
	for(int i=0; i<line.size(); ++i) {
		PutPixelSDL(surface, line[i].x, line[i].y, color);
	}
}

void DrawPolygonEdges(const vector<vec3>& vertices) {
	int V = vertices.size();
	// Transform each vertex from 3D world position to 2D image position
	vector<Pixel> projectedVertices(V);
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

void ComputePolygonRows(const vector<Pixel>& vertexPixels,
	vector<Pixel>& leftPixels,
	vector<Pixel>& rightPixels ) {

	// 1. Find max and min y-value of the polygon 
	// and compute the number of rows it occupies.
	int minY = min(vertexPixels[0].y, min(vertexPixels[1].y, vertexPixels[2].y));
	int maxY = max(vertexPixels[0].y, max(vertexPixels[1].y, vertexPixels[2].y));

	// 2. Resize leftPixels and rightPixels 
	// so that they have an element for each row.
	int numRows = maxY - minY + 1;
	leftPixels.resize(numRows);
	rightPixels.resize(numRows);

	// 3. Initialize the x-coordinates in leftPixels 
	// to some really large value and the x-coordinates
	// in rightPixels to some really small value.
	for(int i=0; i<numRows; ++i) {
		leftPixels[i].x = +numeric_limits<int>::max(); 
		rightPixels[i].x = -numeric_limits<int>::max();
		leftPixels[i].y = minY;
		rightPixels[i].y = minY;
	}
	// 4. Loop through all edges of the polygon and use
	// linear interpolation to find the x-coordinate for 
	// each row it occupies. Update the corresponding 
	// values in rightPixels and leftPixels.

	// Triangle outlines

	// Loop over all vertices and draw the edge from it to the next vertex
	vector<vector<Pixel>> edges(vertexPixels.size());
	for(int i=0; i<vertexPixels.size(); ++i) {

		int j = (i+1)%vertexPixels.size(); // The next vertex
		int delta = glm::abs(vertexPixels[i].y-vertexPixels[j].y);
		int pixels = delta + 1;
		vector<Pixel> result(pixels);

		Interpolate(vertexPixels[i], vertexPixels[j], result);
		edges[i] = result;
	}

	// Check each edge
	for(int i=0; i<edges.size(); ++i) {
		// Check each pixel on the edge
		int oldIndex = edges[i][0].y - minY;
		for(int j=0; j<edges[i].size(); ++j) {
			
			int index = edges[i][j].y - minY;
			// if(glm::abs(index - oldIndex) > 1) {
			// 	int index2 = (index+oldIndex) / 2;
			// 	leftPixels[index2] = edges[i][j];
			// 	rightPixels[index2] = edges[i][j];
			// }
			if(leftPixels[index].x > edges[i][j].x)
				leftPixels[index] = edges[i][j];
			if(rightPixels[index].x < edges[i][j].x)
				rightPixels[index] = edges[i][j];

			if(glm::abs(index - oldIndex) > 1) {
				leftPixels[(index+oldIndex)/2] = edges[i][j];
				rightPixels[(index+oldIndex)/2] = edges[i][j];
				cout << "you fucked up: " 
				<< edges[i][j].y << " "
				<< minY << " "
				<< index << " "
				<< oldIndex << endl;
			}
			
			oldIndex = index;
		}
	}
}

void DrawPolygonRows(const vector<Pixel>& leftPixels, const vector<Pixel>& rightPixels) {
	// for each row
	for(int i=0; i<leftPixels.size(); ++i) {
		int offset = 0;
		int pixelX = leftPixels[i].x + offset;
		int pixelY = leftPixels[i].y;
		float pixelZ = leftPixels[i].zinv;
		
		// for each column
		while(pixelX <= rightPixels[i].x) {
			PutPixelSDL(screen, pixelX, pixelY, currentColor);
			offset++;
			pixelX = leftPixels[i].x + offset;
		}
	}
}

void DrawPolygon(const vector<vec3>& vertices) {
	int V = vertices.size();
	vector<Pixel> vertexPixels(V);

	for(int i=0; i<V; ++i)
		VertexShader(vertices[i], vertexPixels[i]);

	vector<Pixel> leftPixels;
	vector<Pixel> rightPixels;
	ComputePolygonRows(vertexPixels, leftPixels, rightPixels);
	DrawPolygonRows(leftPixels, rightPixels);
}
// void DrawTest() {
	
// 	vector<ivec2> vertexPixels(3); 
// 	vertexPixels[0] = ivec2(10, 5); 
// 	vertexPixels[1] = ivec2( 5,10); 
// 	vertexPixels[2] = ivec2(15,15); 
// 	vector<ivec2> leftPixels; 
// 	vector<ivec2> rightPixels; 
	
// 	ComputePolygonRows( vertexPixels, leftPixels, rightPixels ); 
	
// 	for( int row=0; row<leftPixels.size(); ++row ) 
// 	{ 
// 		cout << "Start: (" 
// 		<< leftPixels[row].x << "," 
// 		<< leftPixels[row].y << "). " 
// 		<< "End: (" 
// 		<< rightPixels[row].x << "," 
// 		<< rightPixels[row].y << "). " << endl; 
// 	} 
// }