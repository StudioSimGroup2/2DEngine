#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "CameraManager.h"
#include "Common.h"
#include "Utils/AssetManager.h"

//#include "PNGLoader.h"

using namespace DirectX;
using namespace Engine;

class Sprite
{
public:
	Sprite(Device* dev, const wchar_t* name, Vector2D* Position);
	~Sprite();

	void Update(float deltaTime);
	void Render(ID3D11DeviceContext* devCon);
	void SetPosition(Vector2D Pos);

	Vector2D GetPosition() { return *mPosition; };

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

	Vector2D* mPosition;


	AssetManager* mAssetManager;

	int mScreenWidth, mScreenHeight;
	int mWidth, mHeight;
	float mPosX, mPosY;
	int mPreviousPosX = 0, mPreviousPosY = 0;

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

