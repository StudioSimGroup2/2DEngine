#pragma once

#include <Windows.h>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <memory>

// DX11
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>

// ImGui files
#include "../vendor/ImGui/imgui.h"
#include "../vendor/ImGui/imgui_impl_win32.h"
#include "../vendor/ImGui/imgui_impl_dx11.h"

using namespace DirectX;

// Macros
#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

