#pragma once
#include "DirectXFramework.h"
#include "SceneNode.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct terrainVertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
	XMFLOAT2 BlendMapTexCoord;
};

class TerrainNode : public SceneNode
{
public:
	TerrainNode(wstring name);
	~TerrainNode();

	bool Initialise();
	void Render();
	void Shutdown() {};

private:
	unsigned int _numberOfXPoints;
	unsigned int _numberOfZPoints;
	unsigned int _numberOfPolygons;
	unsigned int _numberOfVertices;
	unsigned int _numberOfIndices;
	int NUMBER_OF_ROWS = 1023;
	int NUMBER_OF_COLUMNS = 1023;
	int heightIndexOne;
	int heightIndexTwo;
	terrainVertex temp;

	float _terrainStartX;
	float _terrainStartZ;
	float _terrainEndX;
	float _terrainEndZ;

	vector<terrainVertex> _vertices;
	vector<UINT> _indices;
	vector<float> _heightValues;

	XMFLOAT4 _ambientLight;
	XMFLOAT4 _directionalLightVector;
	XMFLOAT4 _directionalLightColour;
	XMFLOAT4 _cameraPosition;

	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;

	ComPtr<ID3D11Buffer>			_vertexBuffer;
	ComPtr<ID3D11Buffer>			_indexBuffer;

	ComPtr<ID3DBlob> _vertexShaderByteCode = nullptr;
	ComPtr<ID3DBlob> _pixelShaderByteCode = nullptr;
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3D11PixelShader> _pixelShader;
	ComPtr<ID3D11InputLayout> _layout;
	ComPtr<ID3D11Buffer> _constantBuffer;

	ComPtr<ID3D11RasterizerState> _defaultRasteriserState;
	ComPtr<ID3D11RasterizerState> _wireframeRasteriserState;

	ComPtr<ID3D11ShaderResourceView> _texturesResourceView;
	ComPtr<ID3D11ShaderResourceView> _blendMapResourceView;

	void GenerateVerticesAndIndices();
	void GenerateBuffers();
	void BuildShaders();
	void BuildVertexLayout();
	void BuildConstantBuffer();
	void BuildRendererStates();
	bool LoadHeightMap();
	void LoadTerrainTextures();
	void GenerateBlendMap();
	void AddToVertexNormal(int z, int x, unsigned int vertexNumber, FXMVECTOR faceNormal);

};



