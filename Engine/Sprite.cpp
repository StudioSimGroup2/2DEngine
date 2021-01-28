#include "Sprite.h"
#include "vendor/DDSTextureLoader.h"

#include <d3dcompiler.h>

using namespace DirectX;

Sprite::Sprite(ID3D11Device* device, const wchar_t* name)
{
	auto hr = S_OK;

	mScreenHeight = 720;
	mScreenWidth = 1280;

	mWidth = 32;
	mHeight = 32;

	// TODO: Error checking

	hr = CreateDDSTextureFromFile(device, name, nullptr, &mTexture);

	ID3DBlob* pVSBlob = nullptr;

	hr = CompileShaderFromFile(L"quadshader.fx", "VS", "vs_4_0", &pVSBlob);

	hr = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr,
		&mVertexShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &mInputLayout);

	pVSBlob->Release();

	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"quadshader.fx", "PS", "ps_4_0", &pPSBlob);

	hr = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr,
		&mPixelShader);

	pPSBlob->Release();

	// Create a texture sampler state description.

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

	// Create the texture sampler state.
	device->CreateSamplerState(&samplerDesc, &mSampleState);

	CreateBuffers(device);
}

Sprite::~Sprite()
{
	mTexture->Release();
}

void Sprite::Render(ID3D11DeviceContext* devCon)
{
	XMFLOAT4 mEyePosition = XMFLOAT4(0.0f, 0.0f, -5.0f, 1.0f);
	
	XMVECTOR Eye = XMLoadFloat4(&mEyePosition);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	
	

	//mWorldMatrix = XMMatrixIdentity();
	mViewMatrix = XMMatrixLookAtLH(Eye, At, Up);

	// 16 & 12 derived from 16:9 aspect ratio, tweeked slightly
	// the higher values = smaller texture size. Lower value = bigger texture size.
	mProjectionMatrix = XMMatrixOrthographicLH(16, 12, 0.1, 100);


	// Temp translation
	static float posX, posY;
	posX = posY = 0;
	XMMATRIX translation = XMMatrixTranslation(posX, posY, 0);
	XMMATRIX rotation = XMMatrixRotationZ(0.0f);
	XMMATRIX scale = XMMatrixScaling(1.0f * mWidth, 1.0f * mHeight, 1.0f);
	XMMATRIX WVP = scale * rotation * translation;
	XMMATRIX worldMatrix = XMMatrixMultiply(mViewMatrix, mProjectionMatrix);
	mWorldMatrix = XMMatrixMultiply(WVP, worldMatrix);


	ConstantBuffer cb;
	cb.mProjection = XMMatrixTranspose(mProjectionMatrix);
	cb.mView = XMMatrixTranspose(mViewMatrix);
	cb.mWorld = XMMatrixTranspose(mWorldMatrix);
	mWorldMatrix = XMMatrixTranspose(mWorldMatrix);

	devCon->UpdateSubresource(mConstantBuffer, 0, nullptr, &cb, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	devCon->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	
	UINT stride = sizeof(VertexType);
	UINT offset = 0;
	
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devCon->IASetInputLayout(mInputLayout);
	devCon->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	
	devCon->VSSetShader(mVertexShader, NULL, 0);
	devCon->PSSetShader(mPixelShader, NULL, 0);
	devCon->VSSetSamplers(0, 1, &mSampleState);
	devCon->PSSetSamplers(0, 1, &mSampleState);
	devCon->VSSetShaderResources(0, 1, &mTexture);
	devCon->PSSetShaderResources(0, 1, &mTexture);


	devCon->Draw(6, 0);
}

void Sprite::CreateBuffers(ID3D11Device* dev)
{
	VertexType vertices[6];
	float left, right, top, bottom;

	// Calculate the screen coordinates of the left side of the bitmap.
	left = (float)((1280 / 2) * -1) + (float)0;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)32;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (float)(1280 / 2) - (float)0;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)32;

	// Swaped over to unit quad from 2 unit quad
	vertices[0].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left.
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	vertices[1].texture = XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

	// Second triangle.
	vertices[3].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left.
	vertices[3].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[4].position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	vertices[4].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	vertices[5].texture = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexType) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = vertices;
	dev->CreateBuffer(&bd, &InitData, &mVertexBuffer);

	WORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	dev->CreateBuffer(&bd, &InitData, &mIndexBuffer);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	dev->CreateBuffer(&bd, nullptr, &mConstantBuffer);
}

HRESULT Sprite::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut)
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
