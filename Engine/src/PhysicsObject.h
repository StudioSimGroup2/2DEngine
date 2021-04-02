#pragma once
#include "Sprite.h"
#include "Physics.h"
#include "AI.h"

class PhysicsObject : public Sprite
{
public:
    PhysicsObject(Device* dev, const std::string& name, const std::string& path, vec2f* position);
    ~PhysicsObject();
    void Update(float deltaTime);
    void Render();
protected:
    Physics* mPhysics;
    AI* mAI;
private:
};

