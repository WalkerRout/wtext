
#include "la.h"



Vec2f vec2f(float x, float y){
    return (Vec2f) {
        .x = x,
        .y = y
    };
}



Vec2f vec2fs(float x){
    return vec2f(x, x);
}


// ---------------------------------------------


Vec2f vec2fAdd(Vec2f a, Vec2f b){
    return vec2f(a.x + b.x, a.y + b.y);
}



Vec2f vec2fSub(Vec2f a, Vec2f b){
    return vec2f(a.x - b.x, a.y - b.y);
}



Vec2f vec2fMul(Vec2f a, Vec2f b){
    return vec2f(a.x * b.x, a.y * b.y);
}



Vec2f vec2fDiv(Vec2f a, Vec2f b){
    return vec2f(a.x / b.x, a.y / b.y);
}
