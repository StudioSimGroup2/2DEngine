#pragma once
#include "CameraManager.h"
#include "Common.h"

//#include "PNGLoader.h"

using namespace DirectX;

class Sprite
{
public:
	Sprite(ID3D11Device* device, const wchar_t* name, int PosX, int PosY);
	~Sprite();

	void Render(ID3D11DeviceContext* devCon);

private:
	void CreateBuffers(ID3D11Device* dev);

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
		ID3DBlob** ppBlobOut);

	ID3D11ShaderResourceView* mTexture;
	ID3D11InputLayout* mInputLayout;
	ID3D11Buffer* mVertexBuffer, *mIndexBuffer;
	ID3D11PixelShader* mPixelShader;
	ID3D11VertexShader* mVertexShader;
	ID3D11SamplerState* mSampleState;

	XMMATRIX mWorldMatrix;
	XMMATRIX mViewMatrix;
	XMMATRIX mProjectionMatrix;

	ID3D11Buffer* mConstantBuffer;

	int mScreenWidth, mScreenHeight;
	int mWidth, mHeight;
	float mPosX, mPosY;
	int mPreviousPosX, mPreviousPosY;

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
	};
};

