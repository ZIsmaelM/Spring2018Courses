// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL/SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

void foo( vec3 a, vector<vec3>& vectArray, int index) {
	vectArray[index].x = a.x;
	vectArray[index].y = a.y;
	vectArray[index].z = a.z;
}
void Interpolate( float a, float b, vector<float>& result) {
	int samples = result.size();
	float dist = b - a;
	result[0] = a;
	result[samples-1] = b;

	for (int i = 1; i <= samples; ++i) {
		float mag = i/samples;
		int L = (samples-mag)*a;
		int R = mag*b;
		result[i] = (int)(i*(dist/samples)+a);
		cout << result[i] << " ";
	}
	cout << "" << endl;
}

void InterpolateVec3( vec3 a, vec3 b, vector<vec3>& result) {
	int numSamples = result.size();
	int numPoints = 3;
	

	foo(a,result,0);
	foo(b,result,numSamples-1);

	int dist;
	for (int i = 0; i < numSamples; ++i) {
		for (int j = 0; j < numPoints; ++j) {
			float dist = b[j] - a[j];
			float t = ((float)i/(numSamples-1)) * dist;
			result[i][j] = a[j] + t;
		}
	}
}

int main( int argc, char* argv[] )
{

	std::vector<vec3> result(4);
	vec3 a(1,4,9.2);
	vec3 b(4,1,9.8);
	InterpolateVec3(a,b,result);
	for (int i=0; i<result.size(); ++i) {
		cout << "( "
		<< result[i].x << ", "
		<< result[i].y << ", "
		<< result[i].z << " ) ";
	}
	cout << "" << endl;

	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{
	vec3 topLeft(1,0,0); // red
	vec3 topRight(0,0,1); // blue
	vec3 bottomLeft(0,1,0); // green
	vec3 bottomRight(1,1,0); // yellow

	vector<vec3> leftSide( SCREEN_HEIGHT );
	vector<vec3> rightSide( SCREEN_HEIGHT );
	InterpolateVec3( topLeft, bottomLeft, leftSide );
	InterpolateVec3( topRight, bottomRight, rightSide );
	
	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{

		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			vector<vec3> interpolated(SCREEN_WIDTH);
			InterpolateVec3(leftSide[y],rightSide[y],interpolated);
			PutPixelSDL( screen, x, y, interpolated[x] );

			// vec3 color(0,0,1);
			// PutPixelSDL( screen, x, y, color );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}