#pragma once
#include "Sprite.h"
#include "Physics.h"
class PhysicsObject : public Sprite
{
public:
    PhysicsObject(Device* dev, vec2f* position, char* name, Texture* tex);
    ~PhysicsObject();
    void Update(float deltaTime);
    void Render();
protected:
    Physics* mPhysics;  
private:
};

