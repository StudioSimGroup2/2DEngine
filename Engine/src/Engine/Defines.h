#pragma once

#ifdef ENGINE_DEBUG_OGL
#define GRAPHICS_LIBRARY 1
#endif

#ifdef ENGINE_RELEASE_OGL
#define GRAPHICS_LIBRARY 1
#endif

#ifdef ENGINE_RELEASE_D3D11
#define GRAPHICS_LIBRARY 0
#endif

#ifdef ENGINE_DEBUG_D3D11
#define GRAPHICS_LIBRARY 0
#endif