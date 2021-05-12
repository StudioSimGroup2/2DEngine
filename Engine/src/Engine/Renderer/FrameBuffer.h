#pragma once

#include "Engine/Core.h"
#include "Engine/Defines.h"

#if GRAPHICS_LIBRARY == 0 //d3d11
#include "Backend\D3D11\D3D11FrameBuffer.h"
#elif GRAPHICS_LIBRARY == 1 // ogl
#include "Backend\OGL\OGLFrameBuffer.h"
#endif

namespace Engine
{
	class FrameBuffer
	{
	public:
		FrameBuffer() {}
		~FrameBuffer() { if (mCreated) { delete mFrameBuffer; mFrameBuffer = nullptr; } }

#if GRAPHICS_LIBRARY == 0
		void CreateFrameBuffer(unsigned int width, unsigned int height) { mFrameBuffer = new D3D11FrameBuffer(width, height); mCreated = true; }
#elif GRAPHICS_LIBRARY == 1
		void CreateFrameBuffer(unsigned int width, unsigned int height) { mFrameBuffer = new OGLFrameBuffer(width, height); mCreated = true; }
#endif
		void Load() { if (mCreated) mFrameBuffer->Load(); }
		void Unload() { if (mCreated) mFrameBuffer->Unload(); }

		void* GetTexID() { if (mCreated) return mFrameBuffer->GetTexID(); }

	private:
		bool mCreated = false;

#if GRAPHICS_LIBRARY == 0
		D3D11FrameBuffer* mFrameBuffer = nullptr;
#elif GRAPHICS_LIBRARY == 1
		OGLFrameBuffer* mFrameBuffer = nullptr;
#endif
	};
}
