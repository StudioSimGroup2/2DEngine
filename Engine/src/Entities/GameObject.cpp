#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject()
	{
		InitTransformComponent();

	}

	GameObject::~GameObject()
	{
		for (Component* c : mComponents)
		{
			delete c;
			c = nullptr;
		}
		
		mComponents.clear();
		mComponents.shrink_to_fit();
	}

	void GameObject::Start()
	{
		for (Component* c : mComponents)
			c->Start();
	}

	void GameObject::Update()
	{
		if (!mStatus)
			return;

		for (Component* c : mComponents)
			c->Update();
	}

	void GameObject::Render()
	{
		if (!mStatus)
			return;

		for (Component* c : mComponents)
			c->Render();
	}

	void GameObject::InternalUpdate()
	{
		for (Component* c : mComponents)
			c->InternalUpdate();
	}

	void GameObject::InternalRender()
	{
		for (Component* c : mComponents)
			c->InternalRender();
	}

	void GameObject::Attach(GameObject* parent)
	{
		mParent = parent;
		mParent->AddChild(this);
	}

	void GameObject::RemoveParent()
	{
		mParent->GetChildren();
		mParent = nullptr;
	}

	void GameObject::RemoveChild(GameObject* go)
	{
		if (mChildren.empty())
			return;

		auto index = std::find_if(mChildren.begin(), mChildren.end(),
			[&](const GameObject* object) {return go == object; });

		if (index != mChildren.end())
		{
			GameObject* objectToDelete = mChildren.at(std::distance(mChildren.begin(), index));
			mChildren.erase(index);
		}
	}

	void GameObject::InitTransformComponent()
	{
		AddComponent<TransformComp>(new TransformComp);
	}
}
