#pragma once

#include "geometry.h"

// [-1,1]
float PerlinNoise3D( float x, float y, float z );
float calcNoise( int x, int y, int z, float seed = 1.3f );

inline float pnoise( float x, float y, float z, int depth )
{
	return PerlinNoise3D( x * .25f, ( y + depth * 32 ) * .25f, z * .25f ) * .5f + .5f;
}

inline float pnoise( int x, int y, int z, int depth )
{
	return PerlinNoise3D( x * .25f, ( y + depth * 32 ) * .25f, z * .25f ) * .5f + .5f;
}

inline float pnoise( Vector &v, int depth )
{
	return PerlinNoise3D( v.x * .25f, ( v.y + depth * 32 ) * .25f, v.z * .25f ) * .5f + .5f;
}
