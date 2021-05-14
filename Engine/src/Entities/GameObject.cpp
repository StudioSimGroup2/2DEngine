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
		mComponents.shrink_to_fit();

		//TODO Add children back to the scene hierachy 
		for (GameObject* child : mChildren)
		{
			child->RemoveParent();
			delete child;
			child = nullptr;
		}

		mChildren.shrink_to_fit();
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
		mParent = nullptr;
	}

	void GameObject::InitTransformComponent()
	{
		AddComponent<TransformComp>(new TransformComp);
	}
}
