#include "stdafx.h"
#include "PerlinNoise.h"
#include <math.h>

static const int p[512] =
{
	0x97, 0xA0, 0x89, 0x5B, 0x5A, 0x0F, 0x83, 0x0D, 0xC9, 0x5F, 0x60, 0x35, 0xC2, 0xE9, 0x07, 0xE1,
	0x8C, 0x24, 0x67, 0x1E, 0x45, 0x8E, 0x08, 0x63, 0x25, 0xF0, 0x15, 0x0A, 0x17, 0xBE, 0x06, 0x94,
	0xF7, 0x78, 0xEA, 0x4B, 0x00, 0x1A, 0xC5, 0x3E, 0x5E, 0xFC, 0xDB, 0xCB, 0x75, 0x23, 0x0B, 0x20,
	0x39, 0xB1, 0x21, 0x58, 0xED, 0x95, 0x38, 0x57, 0xAE, 0x14, 0x7D, 0x88, 0xAB, 0xA8, 0x44, 0xAF,
	0x4A, 0xA5, 0x47, 0x86, 0x8B, 0x30, 0x1B, 0xA6, 0x4D, 0x92, 0x9E, 0xE7, 0x53, 0x6F, 0xE5, 0x7A,
	0x3C, 0xD3, 0x85, 0xE6, 0xDC, 0x69, 0x5C, 0x29, 0x37, 0x2E, 0xF5, 0x28, 0xF4, 0x66, 0x8F, 0x36,
	0x41, 0x19, 0x3F, 0xA1, 0x01, 0xD8, 0x50, 0x49, 0xD1, 0x4C, 0x84, 0xBB, 0xD0, 0x59, 0x12, 0xA9,
	0xC8, 0xC4, 0x87, 0x82, 0x74, 0xBC, 0x9F, 0x56, 0xA4, 0x64, 0x6D, 0xC6, 0xAD, 0xBA, 0x03, 0x40,
	0x34, 0xD9, 0xE2, 0xFA, 0x7C, 0x7B, 0x05, 0xCA, 0x26, 0x93, 0x76, 0x7E, 0xFF, 0x52, 0x55, 0xD4,
	0xCF, 0xCE, 0x3B, 0xE3, 0x2F, 0x10, 0x3A, 0x11, 0xB6, 0xBD, 0x1C, 0x2A, 0xDF, 0xB7, 0xAA, 0xD5,
	0x77, 0xF8, 0x98, 0x02, 0x2C, 0x9A, 0xA3, 0x46, 0xDD, 0x99, 0x65, 0x9B, 0xA7, 0x2B, 0xAC, 0x09,
	0x81, 0x16, 0x27, 0xFD, 0x13, 0x62, 0x6C, 0x6E, 0x4F, 0x71, 0xE0, 0xE8, 0xB2, 0xB9, 0x70, 0x68,
	0xDA, 0xF6, 0x61, 0xE4, 0xFB, 0x22, 0xF2, 0xC1, 0xEE, 0xD2, 0x90, 0x0C, 0xBF, 0xB3, 0xA2, 0xF1,
	0x51, 0x33, 0x91, 0xEB, 0xF9, 0x0E, 0xEF, 0x6B, 0x31, 0xC0, 0xD6, 0x1F, 0xB5, 0xC7, 0x6A, 0x9D,
	0xB8, 0x54, 0xCC, 0xB0, 0x73, 0x79, 0x32, 0x2D, 0x7F, 0x04, 0x96, 0xFE, 0x8A, 0xEC, 0xCD, 0x5D,
	0xDE, 0x72, 0x43, 0x1D, 0x18, 0x48, 0xF3, 0x8D, 0x80, 0xC3, 0x4E, 0x42, 0xD7, 0x3D, 0x9C, 0xB4,

	0x97, 0xA0, 0x89, 0x5B, 0x5A, 0x0F, 0x83, 0x0D, 0xC9, 0x5F, 0x60, 0x35, 0xC2, 0xE9, 0x07, 0xE1,
	0x8C, 0x24, 0x67, 0x1E, 0x45, 0x8E, 0x08, 0x63, 0x25, 0xF0, 0x15, 0x0A, 0x17, 0xBE, 0x06, 0x94,
	0xF7, 0x78, 0xEA, 0x4B, 0x00, 0x1A, 0xC5, 0x3E, 0x5E, 0xFC, 0xDB, 0xCB, 0x75, 0x23, 0x0B, 0x20,
	0x39, 0xB1, 0x21, 0x58, 0xED, 0x95, 0x38, 0x57, 0xAE, 0x14, 0x7D, 0x88, 0xAB, 0xA8, 0x44, 0xAF,
	0x4A, 0xA5, 0x47, 0x86, 0x8B, 0x30, 0x1B, 0xA6, 0x4D, 0x92, 0x9E, 0xE7, 0x53, 0x6F, 0xE5, 0x7A,
	0x3C, 0xD3, 0x85, 0xE6, 0xDC, 0x69, 0x5C, 0x29, 0x37, 0x2E, 0xF5, 0x28, 0xF4, 0x66, 0x8F, 0x36,
	0x41, 0x19, 0x3F, 0xA1, 0x01, 0xD8, 0x50, 0x49, 0xD1, 0x4C, 0x84, 0xBB, 0xD0, 0x59, 0x12, 0xA9,
	0xC8, 0xC4, 0x87, 0x82, 0x74, 0xBC, 0x9F, 0x56, 0xA4, 0x64, 0x6D, 0xC6, 0xAD, 0xBA, 0x03, 0x40,
	0x34, 0xD9, 0xE2, 0xFA, 0x7C, 0x7B, 0x05, 0xCA, 0x26, 0x93, 0x76, 0x7E, 0xFF, 0x52, 0x55, 0xD4,
	0xCF, 0xCE, 0x3B, 0xE3, 0x2F, 0x10, 0x3A, 0x11, 0xB6, 0xBD, 0x1C, 0x2A, 0xDF, 0xB7, 0xAA, 0xD5,
	0x77, 0xF8, 0x98, 0x02, 0x2C, 0x9A, 0xA3, 0x46, 0xDD, 0x99, 0x65, 0x9B, 0xA7, 0x2B, 0xAC, 0x09,
	0x81, 0x16, 0x27, 0xFD, 0x13, 0x62, 0x6C, 0x6E, 0x4F, 0x71, 0xE0, 0xE8, 0xB2, 0xB9, 0x70, 0x68,
	0xDA, 0xF6, 0x61, 0xE4, 0xFB, 0x22, 0xF2, 0xC1, 0xEE, 0xD2, 0x90, 0x0C, 0xBF, 0xB3, 0xA2, 0xF1,
	0x51, 0x33, 0x91, 0xEB, 0xF9, 0x0E, 0xEF, 0x6B, 0x31, 0xC0, 0xD6, 0x1F, 0xB5, 0xC7, 0x6A, 0x9D,
	0xB8, 0x54, 0xCC, 0xB0, 0x73, 0x79, 0x32, 0x2D, 0x7F, 0x04, 0x96, 0xFE, 0x8A, 0xEC, 0xCD, 0x5D,
	0xDE, 0x72, 0x43, 0x1D, 0x18, 0x48, 0xF3, 0x8D, 0x80, 0xC3, 0x4E, 0x42, 0xD7, 0x3D, 0x9C, 0xB4
};

#define fade( t ) ( (t) * (t) * (t) * ( (t) * ( (t) * 6 - 15 ) + 10 ) )
//#define fade( t ) (t)
#define lerp( t, a, b ) ( (a) + (t) * ( (b) - (a) ) )

inline float
grad( int hash, float x, float y, float z )
{
	switch( hash & 0xF )
	{
	case  0:	return   x + y;
	case  1:	return - x + y;
	case  2:	return   x - y;
	case  3:	return - x - y;
	case  4:	return   x + z;
	case  5:	return - x + z;
	case  6:	return   x - z;
	case  7:	return - x - z;
	case  8:	return   y + z;
	case  9:	return - y + z;
	case 10:	return   y - z;
	case 11:	return - y - z;
	case 12:	return   x + y;
	case 13:	return - y + z;
	case 14:	return - x + y;
	case 15:	return - y - z;
	}
	return .0f;
}

float
PerlinNoise3D( float x, float y, float z )
{
	int X, Y, Z;

#if 0
	float f;
	f = floorf( x );	X = (int)f & 0xFF;	x -= f;
	f = floorf( y );	Y = (int)f & 0xFF;	y -= f;
	f = floorf( z );	Z = (int)f & 0xFF;	z -= f;
#else
	// x, y, zが負数値を取らない場合のみ かなり軽い
	int i;
	i = (int)x;	X = i & 0xFF;	x -= i;
	i = (int)y;	Y = i & 0xFF;	y -= i;
	i = (int)z;	Z = i & 0xFF;	z -= i;
#endif

	float u = fade( x ), v = fade( y ), w = fade( z );
	int A = p[X]+Y, AA = p[A]+Z, AB = p[A+1]+Z, B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;

	return lerp( w,	lerp( v,	lerp( u,	grad( p[AA  ], x  , y  , z   ),
											grad( p[BA  ], x-1, y  , z   ) ),
								lerp( u,	grad( p[AB  ], x  , y-1, z   ),
											grad( p[BB  ], x-1, y-1, z   ) ) ),
					lerp( v,	lerp( u,	grad( p[AA+1], x  , y  , z-1 ),
											grad( p[BA+1], x-1, y  , z-1 ) ),
								lerp( u,	grad( p[AB+1], x  , y-1, z-1 ),
											grad( p[BB+1], x-1, y-1, z-1 ) ) ) );
}

///////////////////////////////////////////////////////////////////////////

float
calcNoise( int x, int y, int z, float seed )
{
//	float freq = .03f;
	float freq = .05f;
	float amp = 1.0f;
	int o;
	float f, sum = 0;
	for( o = 0; o < 3; o++ )
	{
//		f = PerlinNoise3D( (x+seed) * freq, (y+seed) * freq, (z+seed) * freq );
		f = PerlinNoise3D( x * freq, (y+seed) * freq, z * freq );
		sum += f * amp;
		freq *= 2.0f;
		amp *= 0.5f;
	}
	return __min( 1.5f, __max( 0.0f, sum * .5f + .5f ) );
}

#if 0
float
perlinNoiseV( Vector &v, float rad, float *sea )
{
	float freq = BASE_FREQ;
	float amp = 1.0f;

	int o;
	float f;
	float sum = 0;
	for( o = 0; o <= NEST_MAX + 4; o++ )
	{
//		if( o == NEST_MAX )
//			freq *= 8.0f;
//		sum += PerlinNoise3D( (v.x+1.3f) * freq, (v.y+1.3f) * freq, (v.z+1.3f) * freq ) * amp;
//		sum += f;

		f = PerlinNoise3D( (v.x+1.3f) * freq, (v.y+1.3f) * freq, (v.z+1.3f) * freq );
		sum += f * amp;
//		sum += tanf( f + FPI_2 ) * amp;
//		sum += powf( f, 4.0f ) * amp;
//		f *= 1.5f;
//		sum += f * f * f * f * f * amp;
		freq *= 1.65f;
//		freq *= 2.0f;
		amp *= AMP;

//		freq *= ( 0.60f + powf( 1.01f, o ) );
//		amp *= ( powf( 1.01f, o ) - 0.40f );
	}

//	sum *= 1.1f;

/*	if( sum >= 0 )
		f = powf( sum, 4.0f ) + sum;
	else
		f = -powf( -sum, 4.0f ) + sum;*/

//sum -= .5f;
//	f = sum;
//	f = tanf( sum * 1.3f );
	f = tanf( sum * 1.3f );

	if( sea )
	{
		float g;
		g = __max( 0.0f, __min( 1.0f, ( f - SEA_HEIGHT + .04f ) * 20.0f ) );	// [0,1]
		g *= g;
		*sea = .0f + ( 1.0f - g ) * 12.0f;	// 12.5 〜 .5
	}

	f = __max( f, SEA_HEIGHT );
	v.SetLength( rad + f * rad * .04f );

	return sum;
}
#endif
