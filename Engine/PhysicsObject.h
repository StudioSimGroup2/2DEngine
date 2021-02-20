#pragma once
#include "Sprite.h"
#include "Physics.h"
class PhysicsObject : public Sprite
{
public:
    PhysicsObject(ID3D11Device* device, const wchar_t* name, Vector2D Position);
    ~PhysicsObject();
    void Update(float deltaTime);
    void Render(ID3D11DeviceContext* devCon);
    void SetPosition(Vector2D Pos);
private:
    Physics* mPhysics;  
};

