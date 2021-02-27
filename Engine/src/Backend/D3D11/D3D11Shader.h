#pragma once

#include "Utils/Shader.h"

#include "Backend/D3D11/D3D11Device.h"
#include <d3d11.h>

namespace Engine
{
	class D3D11Shader : public Shader
	{
	public:
		D3D11Shader(D3D11Device* device, const std::string& path, const std::string name);
		~D3D11Shader();
		
		virtual void Load() const override;
		virtual void Unload() const override;

	private:
		HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
			ID3DBlob** ppBlobOut);

		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11InputLayout* mInputLayout;
		ID3D11SamplerState* mSamplerState;

		ID3D11DeviceContext* mDeviceContext;
	};
}

