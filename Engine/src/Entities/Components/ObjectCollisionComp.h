#pragma once

#include "../Component.h"
#include "Common.h"
#include "Box2D.h"

namespace Engine
{
	class ENGINE_API ObjectCollisionComp : public Component
	{
	public:
		ObjectCollisionComp();
		~ObjectCollisionComp();

		virtual void Init() override;

		Box2D GetColBox() { return colBox; }
	private:
		Box2D colBox;

		//Inherited from Component
		virtual void Update() override;
		virtual void Render() override;
	};
}
