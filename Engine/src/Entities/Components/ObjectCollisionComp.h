#pragma once

#include "../Component.h"
#include "Common.h"
#include "../Box2D.h"
#include <vector>

namespace Engine
{
	class ENGINE_API ObjectCollisionComp : public Component
	{
	public:
		ObjectCollisionComp();
		ObjectCollisionComp(GameObject* parent);
		~ObjectCollisionComp();

		void Init();

		Box2D GetColBox() { return colBox; }
	private:
		Box2D colBox;

		//Inherited from Component
		virtual void Update() override;
		virtual void Render() override;
	};
}
