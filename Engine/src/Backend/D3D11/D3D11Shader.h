#pragma once

#include "Utils/Shader.h"

#include "Backend/D3D11/D3D11Device.h"
#include <d3d11.h>

namespace Engine
{
	class D3D11Shader : public Shader
	{
	public:
		D3D11Shader(D3D11Device* device, const std::string& name, const std::string path);
		~D3D11Shader();
		
		virtual void Load() const override;
		virtual void Unload() const override;

		virtual const std::string& GetName() const override { return mName; }

	private:
		HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
			ID3DBlob** ppBlobOut);

		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
		ID3D11SamplerState* mSamplerState = nullptr;

		ID3D11DeviceContext* mDeviceContext = nullptr;
	};
}

