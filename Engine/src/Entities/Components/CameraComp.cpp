#include "CameraComp.h"
#include "..\GameObject.h"

#if GRAPHICS_LIBRARY == 0
	#include "Backend\D3D11\D3D11Camera.h"
#elif GRAPHICS_LIBRARY == 1
	#include "Backend\OGL\OpenGLCamera.h"
#endif

namespace Engine
{
	CameraComp::CameraComp()
	{
	}

	CameraComp::~CameraComp()
	{
	}

	void CameraComp::Start()
	{
	}

	void CameraComp::Update()
	{
#if GRAPHICS_LIBRARY == 0
		dynamic_cast<D3DCamera*>(mCamera)->Update(mParent->GetComponent<TransformComp>()->GetPosition());
#elif GRAPHICS_LIBRARY == 1
		dynamic_cast<OGLCamera*>(mCamera)->Update(mParent->GetComponent<TransformComp>()->GetPosition());
#endif
	}

	void CameraComp::Render()
	{
	}

	void CameraComp::InternalUpdate()
	{
#if GRAPHICS_LIBRARY == 0
		dynamic_cast<D3DCamera*>(mCamera)->Update(mParent->GetComponent<TransformComp>()->GetPosition());
#elif GRAPHICS_LIBRARY == 1
		dynamic_cast<OGLCamera*>(mCamera)->Update(mParent->GetComponent<TransformComp>()->GetPosition());
#endif
	}

	void CameraComp::InternalRender()
	{
	}

	void CameraComp::Init()
	{
		mType = COMPONENT_CAMERA;

		mCamera = CameraManager::Get()->Add(mParent->GetComponent<TransformComp>()->GetPosition());
	}
}
