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
//int axis = 0;
float yaw = 0;
float pitch = 0;
float roll = 0;
int axis = 0;
int numAxis = 3;
mat3 axisX(0,0,0,0,0,0,0,0,0);
mat3 axisY(0,0,0,0,0,0,0,0,0);
mat3 axisZ(0,0,0,0,0,0,0,0,0);

vec3 currentColor(0.2,0.2,0.2);

float depthBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

vec3 lightPos(0,-0.5,-0.7);
vec3 newLight; 
vec3 lightPower = 1.1f*vec3( 1, 1, 1 ); 
vec3 indirectLightPowerPerArea = 0.5f*vec3( 1, 1, 1 );

vec3 currentNormal;
vec3 currentReflectance;
// ----------------------------------------------------------------------------
// FUNCTIONS

struct Pixel { 
	int x; 
	int y; 
	float zinv;
	vec3 illumination;
	vec3 pos3D;
};

struct Vertex {
	vec3 position;
	vec3 normal;
	vec3 reflectance;
	vec3 origin3D;
};

void Update();
void Draw();
void DrawTest();
void ClearZBuff();
void UpdateRotationMatrices();
void DrawPolygonEdges(const vector<vec3>&);
void DrawPolygon(const vector<Vertex>&);
void VertexShader(const Vertex&, ivec2&);

int main( int argc, char* argv[] ) {
	LoadTestModel( triangles );
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	while( NoQuitMessageSDL() )
	{
		Update();
		//ClearZBuff();
		Draw();
		//usleep(51000000); // sleep for 51s
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void RotateWorld(vec3& v) {

	vector<mat3> rotMatrices(numAxis);
	rotMatrices[0] = axisX;
	rotMatrices[1] = axisY;
	rotMatrices[2] = axisZ;

	for(int i=0; i<numAxis; ++i) {
		float newX = glm::dot(rotMatrices[i][0], v);
		float newY = glm::dot(rotMatrices[i][1], v);
		float newZ = glm::dot(rotMatrices[i][2], v);

		v.x = newX;
		v.y = newY;
		v.z = newZ;
	}
}

vec3 RotateCamera(vec3& v) {
	
	vec3 rotRight;
	vec3 rotDown;
	vec3 rotForward;

	// testAngle += angle;
	if (axis == 0) {
		rotRight = vec3(1, 0, 0);
		rotDown = vec3(0, cos(pitch), -sin(pitch));
		rotForward = vec3(0, sin(pitch), cos(pitch));
		//axisV = mat3(rotRight,rotDown,rotForward);
	} else {
		rotRight = vec3(cos(yaw), 0, sin(yaw));
		rotDown = vec3(0, 1, 0);
		rotForward = vec3(-sin(yaw), 0, cos(yaw));
		//axisH = mat3(rotRight,rotDown,rotForward);
	}

	mat3 rot = mat3(rotRight, rotDown, rotForward);	//axisV + axisH;
	float rotX = glm::dot(rot[0], v);
	float rotY = glm::dot(rot[1], v);
	float rotZ = glm::dot(rot[2], v);

	return vec3(rotX, rotY, rotZ);
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
		axis = 0;
		pitch += angle;
		cameraPos = RotateCamera(cameraOrig);
	}
	if( keystate[SDLK_DOWN] ) {
		axis = 0;
		pitch -= angle;
		cameraPos = cameraOrig;
		cameraPos = RotateCamera(cameraOrig);
	}

	if( keystate[SDLK_RIGHT] ) {
		axis = 1;
		yaw += angle;
		cameraPos = cameraOrig;
		cameraPos = RotateCamera(cameraOrig);
	}

	if( keystate[SDLK_LEFT] ) {
		axis = 1;
		yaw -= angle;
		cameraPos = cameraOrig;
		cameraPos = RotateCamera(cameraOrig);
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
	UpdateRotationMatrices();
}

void UpdateRotationMatrices() {

	// update X rotation matrix
	vec3 rotRight = vec3(1, 0, 0);
	vec3 rotDown = vec3(0, cos(pitch), -sin(pitch));
	vec3 rotForward = vec3(0, sin(pitch), cos(pitch));
	axisX = mat3(rotRight,rotDown,rotForward);

	// update Y rotation matrix
	rotRight = vec3(cos(yaw), 0, sin(yaw));
	rotDown = vec3(0, 1, 0);
	rotForward = vec3(-sin(yaw), 0, cos(yaw));
	axisY = mat3(rotRight,rotDown,rotForward);

	// update Z rotation matrix
	rotRight = vec3(cos(roll), -sin(roll), 0);
	rotDown = vec3(sin(roll), cos(roll), 0);
	rotForward = vec3(0, 0, 1);
	axisZ = mat3(rotRight,rotDown,rotForward);
}

void Draw() {
	ClearZBuff();
	SDL_FillRect( screen, 0, 0 );

	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
	
	focalLength = 500;//SCREEN_HEIGHT / (2 * tan(alpha/2));
	for( int i=0; i<triangles.size(); ++i )
	{
		vector<Vertex> vertices(3);

		float constantRef = 15.f;
		vertices[0].position = RotateCamera(triangles[i].v0);
		vertices[1].position = RotateCamera(triangles[i].v1);
		vertices[2].position = RotateCamera(triangles[i].v2);
		vertices[0].origin3D = triangles[i].v0;
		vertices[1].origin3D = triangles[i].v1;
		vertices[2].origin3D = triangles[i].v2;

		currentNormal = RotateCamera(triangles[i].normal);
		currentReflectance = vec3(1, 1, 1)*constantRef;

		// // Vertex illumination
		// vertices[0].normal = RotateCamera(triangles[i].normal);
		// vertices[1].normal = RotateCamera(triangles[i].normal);
		// vertices[2].normal = RotateCamera(triangles[i].normal);

		// vertices[0].reflectance = vec3(1, 1, 1)*constantRef;
		// vertices[1].reflectance = vec3(1, 1, 1)*constantRef;
		// vertices[2].reflectance = vec3(1, 1, 1)*constantRef;

		// newLight = RotateCamera(lightPos);

		currentColor = triangles[i].color;
		DrawPolygon(vertices);

	}
	
	if ( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

vec3 ComputeLight(vec3 orig, vec3 currentLightPos, vec3 ref, vec3 norm) {

	float r = glm::length(orig - currentLightPos);
	float A = 4*M_PI*r*r;
	vec3 ray = glm::normalize(currentLightPos - orig);
	vec3 D = (lightPower * max(glm::dot(ray, norm), 0.f)) / A;
	vec3 R = ref * D + indirectLightPowerPerArea;

	return R * currentColor;
}
void VertexShader(const Vertex& v, Pixel& p) {
	
	// Calculate points
	vec3 ray = v.position - cameraOrig;
	p.x = (int)(focalLength * (ray.x / ray.z) + (SCREEN_WIDTH/2));
	p.y = (int)(focalLength * (ray.y / ray.z) + (SCREEN_HEIGHT/2));
	p.zinv = 1.f/ray.z;
	p.pos3D = v.origin3D;

	//ComputeLight();
	// // Calculate vertex light
	// float r = glm::length(ray);
	// float A = 4*M_PI*r*r;
	// ray = glm::normalize(lightPos - v.position);
	// vec3 D = (lightPower * max(glm::dot(ray, v.normal), 0.f)) / A;
	// vec3 R = v.reflectance * D + indirectLightPowerPerArea;

	// p.illumination = R * currentColor;

}

void PixelShader( const Pixel& p) {
	int x = p.x;
	int y = p.y;
	if( p.zinv >= depthBuffer[x][y]) {

		vec3 color = ComputeLight(p.pos3D, lightPos, currentReflectance, currentNormal);
		// float r = glm::length(p.pos3D - lightPos);
		// float A = 4*M_PI*r*r;
		// ray = glm::normalize(lightPos - v.position);
		// vec3 D = (lightPower * max(glm::dot(ray, currentNormal), 0.f)) / A;
		// vec3 R = currentReflectance * D + indirectLightPowerPerArea;

		depthBuffer[x][y] = p.zinv;
		PutPixelSDL(screen, x, y, color);
	}
}
void Interpolate( Pixel a, Pixel b, vector<Pixel>& result) {

	int numSamples = result.size();	
	float stepX = float(b.x - a.x) / float(glm::max(numSamples - 1, 1));
	float stepY = float(b.y - a.y) / float(glm::max(numSamples - 1, 1));
	float stepZinv = float(b.zinv - a.zinv) / float(glm::max(numSamples - 1, 1));
	
	//vec3 stepIllumination = (b.illumination - a.illumination) / float(glm::max(numSamples - 1, 1));
	vec3 step3D = (b.pos3D - a.pos3D) / float(glm::max(numSamples - 1, 1));

	Pixel current(a);
	for (int i = 0; i<numSamples; ++i) {
		current.x = a.x + i*stepX;
		current.y = a.y + i*stepY;
		current.zinv = a.zinv + i*stepZinv;
		result[i] = current;
		//current.illumination += stepIllumination;
		current.pos3D += step3D;
	}
}

void DrawLineSDL(SDL_Surface* surface, Pixel a, Pixel b, vec3 color) {
	
	int numPixels = glm::abs(a.y-b.y) + 1;
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
		Vertex v;
		v.position = vertices[i];
		VertexShader(v, projectedVertices[i]);
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
	for(int i=0; i<vertexPixels.size(); ++i) {

		int j = (i+1)%vertexPixels.size(); // The next vertex
		int delta = glm::abs(vertexPixels[i].y-vertexPixels[j].y);
		int pixels = delta + 1;
		vector<Pixel> edge(pixels);

		Interpolate(vertexPixels[i], vertexPixels[j], edge);
		//edges[i] = result;

		for(int k=0; k<edge.size(); ++k) {
			int index = edge[k].y - minY;

			if(leftPixels[index].x > edge[k].x)
				leftPixels[index] = edge[k];

			if(rightPixels[index].x < edge[k].x)
				rightPixels[index] = edge[k];
		}
	}

}

void DrawPolygonRows(const vector<Pixel>& leftPixels, const vector<Pixel>& rightPixels) {
	// for each row
	for(int i=0; i<leftPixels.size(); ++i) {
		float a = glm::abs(leftPixels[i].x - rightPixels[i].x);
		float b = glm::abs(leftPixels[i].y - rightPixels[i].y);
		int numPixels = glm::max(a,b) + 1;

		vector<Pixel> row(numPixels);
		Interpolate(leftPixels[i],rightPixels[i],row);

		for(int j=0; j<row.size(); ++j) {
			// check if the pixel is within the scene view
			if (row[j].x >= 0 && row[j].x < SCREEN_WIDTH 
				&& row[j].y >= 0 && row[j].y < SCREEN_HEIGHT) {

				if( row[j].zinv >= depthBuffer[row[j].x][row[j].y]) {
					PixelShader(row[j]);
					//PutPixelSDL(screen, row[j].x, row[j].y, currentColor);
					//depthBuffer[row[j].x][row[j].y] = row[j].zinv;
				}
			}
		}





		// //DrawLineSDL(screen, leftPixels[i], rightPixels[i], currentColor);
		// int offset = 0;
		// int pixelX = leftPixels[i].x + offset;
		// int pixelY = leftPixels[i].y;
		// float pixelZ = leftPixels[i].zinv;
		
		// // for each column
		// while(pixelX <= rightPixels[i].x) {
		// 	PutPixelSDL(screen, pixelX, pixelY, currentColor);
		// 	offset++;
		// 	pixelX = leftPixels[i].x + offset;
		// }
	}
}

void DrawPolygon(const vector<Vertex>& vertices) {
	int V = vertices.size();
	vector<Pixel> vertexPixels(V);

	for(int i=0; i<V; ++i)
		VertexShader(vertices[i], vertexPixels[i]);

	vector<Pixel> leftPixels;
	vector<Pixel> rightPixels;
	ComputePolygonRows(vertexPixels, leftPixels, rightPixels);
	DrawPolygonRows(leftPixels, rightPixels);
}