#pragma once
#include "Sprite.h"
#include "Physics.h"

class PhysicsObject : public Sprite
{
public:
    PhysicsObject(char* name, vec2f* position, Texture* tex);
    ~PhysicsObject();
    void Update(float deltaTime);
    void Render();
protected:
    Physics* mPhysics;
private:
};
