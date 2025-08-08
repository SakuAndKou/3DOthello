#include "VECTOR.hpp"

VECTOR operator+(const VECTOR& v1, const VECTOR& v2)
{
    return VAdd(v1, v2);
}
VECTOR operator-(const VECTOR& v1, const VECTOR& v2)
{
    return VSub(v1, v2);
}
VECTOR operator*(const VECTOR& v1, double scale)
{
    return VScale(v1, scale);
}
VECTOR operator*(double scale,const VECTOR& v1)
{
    return VScale(v1, scale);
}