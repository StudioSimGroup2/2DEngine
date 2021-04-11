#include "D3D11Shader.h"

#include <d3dcompiler.h>
#include <Utils/StringHelper.h>

namespace Engine
{
	D3D11Shader::D3D11Shader(D3D11Device* device, const std::string& name, const std::string& path)
	{
		mName = name;
		mDeviceContext = device->GetDeviceContext();
		ID3D11Device* dev = device->GetDevice();

		auto hr = S_OK;
		ID3DBlob* blobVS = nullptr;
		ID3DBlob* blobPS = nullptr;

		hr = CompileShaderFromFile(StringHelper::StringToWide(path).c_str(), "VS", "vs_4_0", &blobVS);
		hr = dev->CreateVertexShader(blobVS->GetBufferPointer(), blobVS->GetBufferSize(), nullptr, &mVertexShader);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		hr = dev->CreateInputLayout(layout, numElements, blobVS->GetBufferPointer(),
			blobVS->GetBufferSize(), &mInputLayout);

		blobVS->Release();

		hr = CompileShaderFromFile(StringHelper::StringToWide(path).c_str(), "PS", "ps_4_0", &blobPS);
		hr = dev->CreatePixelShader(blobPS->GetBufferPointer(), blobPS->GetBufferSize(), nullptr, &mPixelShader);

		blobPS->Release();

		if (mSamplerState == nullptr)
		{
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			dev->CreateSamplerState(&samplerDesc, &mSamplerState);
		}
	}

	D3D11Shader::~D3D11Shader()
	{
		if (mInputLayout)
		{
			mInputLayout->Release();
			mInputLayout = nullptr;
		}

		if (mVertexShader)
		{
			mVertexShader->Release();
			mVertexShader = nullptr;
		}

		if (mPixelShader)
		{
			mPixelShader->Release();
			mPixelShader = nullptr;
		}

		if (mSamplerState)
		{
			mSamplerState->Release();
			mSamplerState = nullptr;
		}

		mDeviceContext = nullptr;
	}

	void D3D11Shader::Load() const
	{
		mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mDeviceContext->IASetInputLayout(mInputLayout);
		
		mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
		mDeviceContext->PSSetShader(mPixelShader, NULL, 0);

		mDeviceContext->VSSetSamplers(0, 1, &mSamplerState);
		mDeviceContext->PSSetSamplers(0, 1, &mSamplerState);
	}

	void D3D11Shader::Unload() const
	{
		mDeviceContext->VSSetShader(NULL, NULL, 0);
		mDeviceContext->PSSetShader(NULL, NULL, 0);
	}

	HRESULT D3D11Shader::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		return S_OK;
	}
}