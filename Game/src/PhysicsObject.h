#pragma once
#include "Sprite.h"
#include "..\src\Entities\Components\PhysicsComp.h"
class PhysicsObject : public Sprite
{
public:
    PhysicsObject(Device* dev, vec2f* position, char* name, Texture* tex);
    ~PhysicsObject();
    void Update(float deltaTime);
    void Render();
protected:
    PhysicsComp* mPhysics;
private:
};

