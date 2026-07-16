#pragma once
#include "structs.h"
#include <math.h>

inline Vec3 Vec3_Create(float x, float y, float z) {
    return (Vec3) { x, y, z };
}

inline Vec3 Vec3_Add(Vec3 a, Vec3 b) {
    return (Vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline float Vec3_Dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 Vec3_Sub(Vec3 a, Vec3 b) {
    return (Vec3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vec3 Vec3_Mul_Scalar(Vec3 vector, float scalar) {
    return (Vec3) { vector.x * scalar, vector.y * scalar, vector.z * scalar };
}

inline float Vec3_Length(Vec3 vector) {
    return sqrtf(Vec3_Dot(vector, vector));
}

inline void Vec3_Normalize(Vec3* vector) {
    const float length = Vec3_Length(*vector);
    vector->x /= length;
    vector->y /= length;
    vector->z /= length;
}

inline Color Color_Mul_Scalar(Color color, float scalar) {
    unsigned r = roundf((float)color.r * scalar), g = roundf((float)color.g * scalar), b = roundf((float)color.b * scalar);
    return (Color) { r > 0xff ? 0xff : r, g > 0xff ? 0xff : g, b > 0xff ? 0xff : b };
}
