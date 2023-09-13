#pragma once
#include "SceneNode.h"
#include "DirectXFramework.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"

class MeshNode : public SceneNode
{
public:
public:
	MeshNode(wstring name, wstring modelName) : SceneNode(name) { _modelName = modelName; }
	~MeshNode();

	bool Initialise();
	void Render();
	void Shutdown();
	void Update();

	void SetLeftRight(float leftRight);
	void SetForwardBack(float forwardBack);
	void SetPlanePosition(float x, float y, float z);

private:
	shared_ptr<MeshRenderer>		_renderer;

	wstring							_modelName;
	shared_ptr<ResourceManager>		_resourceManager;
	shared_ptr<Mesh>				_mesh;

	XMFLOAT4    _planePosition;

	XMFLOAT4X4  _viewMatrix;

	float _moveLeftRight;
	float _moveForwardBack;

	float       _planeYaw;
	float       _planePitch;
	float       _planeRoll;
};

