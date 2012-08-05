#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

struct Vertex
{
    float x, y, z;
    Vertex(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Color
{
    float r, g, b;
    Color(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif
