#pragma once
#include "Color.h"
#include "Math.h"
struct VertexAttributes
{
	Vector3f Position;
	Vector4f Color;
	Vector3f Normal;
	Vector2f UV;
};

struct VertexOutput
{

};

class IVertexShader
{
public:
	virtual VertexOutput VertexShade(VertexAttributes input) = 0;
};

class IPixelShader
{
public:
	virtual Color PixelShade(VertexOutput input) = 0;
};