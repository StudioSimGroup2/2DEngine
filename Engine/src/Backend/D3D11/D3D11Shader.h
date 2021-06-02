#pragma once

#include "Utils/Shader.h"

#include "Backend/D3D11/D3D11Device.h"
#include <d3d11.h>

namespace Engine
{
	class D3D11Shader : public Shader
	{
	public:
		D3D11Shader(D3D11Device* device, const std::string& name, const std::string& path);
		~D3D11Shader();
		
		void Load() const override;
		void Unload() const override;

		void PassTextureToPS(int pos, ID3D11ShaderResourceView* srv);

		const std::string& GetName() const override { return mName; }

	private:
		static HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
			ID3DBlob** ppBlobOut);

		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
		ID3D11SamplerState* mSamplerState = nullptr;

		ID3D11DeviceContext* mDeviceContext = nullptr;
	};
}

