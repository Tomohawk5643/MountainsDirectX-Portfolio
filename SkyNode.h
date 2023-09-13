#pragma once
#include "DirectXFramework.h"
#include "Core.h"
#include "DirectXCore.h"
#include "DDSTextureLoader.h"

using namespace std;

struct Vertex
{
	XMFLOAT3 Position;
};

class SkyNode : public SceneNode
{
public:
	SkyNode(wstring name, wstring skyMapFilename, float skySphereRadius);
	~SkyNode();

	bool Initialise();
	void Render();
	void Shutdown();

private:
	wstring _skyCubeFilename;
	float _skySphereRadius;

	unsigned int _numberOfVertices;
	unsigned int _numberOfIndices;

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	ComPtr<ID3D11Buffer> _vertexBuffer;
	ComPtr<ID3D11Buffer> _indexBuffer;

	ComPtr<ID3DBlob> _vertexShaderByteCode;
	ComPtr<ID3DBlob> _pixelShaderByteCode;
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3D11PixelShader> _pixelShader;
	ComPtr<ID3D11InputLayout> _layout;
	ComPtr<ID3D11Buffer> _constantBuffer;

	ComPtr<ID3D11RasterizerState> _defaultRasteriserState;
	ComPtr<ID3D11RasterizerState> _noCullRasteriserState;

	ComPtr<ID3D11ShaderResourceView> _skyBoxResourceView;

	ComPtr<ID3D11DepthStencilState> _stencilState;

	vector<Vertex> _vertices;
	vector<UINT> _indices;

	void CreateSphere(float radius, size_t tesselation);
	void GenerateBuffers();
	void BuildShaders();
	void BuildVertexLayout();
	void BuildConstantBuffer();
	void BuildRendererStates();
	void BuildDepthStencilState();
	void LoadSkyBox();
};

