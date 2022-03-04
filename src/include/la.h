
#ifndef LA_H
#define LA_H

#include "data.h"


Vec2f vec2f(float x, float y);
Vec2f vec2fs(float x);

Vec2f vec2fAdd(Vec2f a, Vec2f b);
Vec2f vec2fSub(Vec2f a, Vec2f b);
Vec2f vec2fMul(Vec2f a, Vec2f b);
Vec2f vec2fDiv(Vec2f a, Vec2f b);

#endif // LA_H