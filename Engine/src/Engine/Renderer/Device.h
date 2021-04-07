#pragma once
#include <string>
#include "Engine/Core.h"
#include "Engine/Defines.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Device.h"
#include "Backend/D3D11/D3D11Renderer2D.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend/OGL/OGLDevice.h"
#include "Backend/OGL/OGLRenderer2D.h"
#endif


namespace Engine
{
	class ENGINE_API Device
	{
	public:

#if GRAPHICS_LIBRARY == 0
		static D3D11Device* GetDevice() { return D3D11Device::GetInstance(); }
		static D3D11Renderer2D* CreateRenderer(Shader* shader) { return new D3D11Renderer2D(static_cast<D3D11Shader*>(shader), D3D11Device::GetInstance()); }
#elif GRAPHICS_LIBRARY == 1
		static OGLDevice* GetDevice() { return OGLDevice::GetInstance(); }
		static OGLRenderer2D* CreateRenderer(Shader* shader) { return new OGLRenderer2D(static_cast<OGLShader*>(shader)); }
#endif

	};


}