#pragma once
#include "MeshNode.h"
#include "DirectXFramework.h"

class ObjectNode: public MeshNode
{
public:
	ObjectNode(wstring name, wstring modelName);

	bool Initialise();
	void Update(FXMMATRIX& currentWorldTransformation);
	void Render();

	XMVECTOR GetPosition();
	void SetPosition(float x, float y, float z);

	void SetPitch(float pitch);
	void SetTotalPitch(float pitch);
	float GetPitch() const;
	void SetYaw(float yaw);
	void SetTotalYaw(float yaw);
	float GetYaw() const;
	void SetRoll(float roll);
	void SetTotalRoll(float roll);
	float GetRoll() const;
	void SetLeftRight(float leftRight);
	void SetForwardBack(float forwardBack);
	void SetStartOrientation(XMMATRIX startOrientation);
	XMMATRIX GetWorldTransformation() const;

private:
	float _yaw;
	float _roll;
	float _pitch;

	XMFLOAT4 _position;

	float _moveLeftRight;
	float _moveForwardBack;

	XMFLOAT4X4 _originalOrientation;
};

