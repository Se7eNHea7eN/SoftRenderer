#pragma once

struct Vector2f
{
    union {
        struct {
            float x;
            float y;
        };
        float data[2];
    };

    Vector2f() :
        x(0),
        y(0)
    {

    }
    Vector2f(float x, float y):
        x(x),
        y(y)
    {
    }
};

struct Vector3f
{
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float data[3];
    };

    Vector3f():
        x(0),
        y(0),
        z(0)
    {

    }
    Vector3f(float x, float y, float z) :
        x(x),
        y(y),
        z(z)
    {
  
    }
};


struct Vector4f
{
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4];
    };

    Vector4f() :
        x(0),
        y(0),
        z(0),
        w(0)
    {

    }
    Vector4f(float x, float y, float z,float w) :
        x(x),
        y(y),
        z(z),
        w(w)
    {

    }
};

struct Matrix4x4
{

};