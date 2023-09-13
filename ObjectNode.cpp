#include "ObjectNode.h"


ObjectNode::ObjectNode(wstring name, wstring modelName) : MeshNode(name, modelName)
{
	_position = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_moveLeftRight = 0.0f;
	_moveForwardBack = 0.0f;
	_yaw = 0.0f;
	_roll = 0.0f;
	_pitch = 0.0f;
	XMStoreFloat4x4(&_originalOrientation, XMMatrixIdentity());
}

bool ObjectNode::Initialise()
{
	if (MeshNode::Initialise())
	{
		return false;
	}
	return true;
}

void ObjectNode::Update(FXMMATRIX& currentWorldTransformation)
{
	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR position;
	XMVECTOR right;
	XMVECTOR forward;
	XMVECTOR up;


	// Yaw (rotation around the Y axis) will have an impact on the forward and right vectors
	XMMATRIX rotationYaw = XMMatrixRotationAxis(defaultUp, _yaw);
	right = XMVector3TransformCoord(defaultRight, rotationYaw);
	forward = XMVector3TransformCoord(defaultForward, rotationYaw);

	// Pitch (rotation around the X axis) impact the up and forward vectors
	XMMATRIX rotationPitch = XMMatrixRotationAxis(right, _pitch);
	up = XMVector3TransformCoord(defaultUp, rotationPitch);
	forward = XMVector3TransformCoord(forward, rotationPitch);

	// Roll (rotation around the Z axis) will impact the Up and Right vectors
	XMMATRIX rotationRoll = XMMatrixRotationAxis(forward, _roll);
	up = XMVector3TransformCoord(up, rotationRoll);
	right = XMVector3TransformCoord(right, rotationRoll);

	// Adjust the camera position by the appropriate amount forward/back and left/right
	position = XMLoadFloat4(&_position) + _moveLeftRight * right + _moveForwardBack * forward;
	XMStoreFloat4(&_position, position);

	// Reset the amount we are moving
	_moveLeftRight = 0.0f;
	_moveForwardBack = 0.0f;

	XMMATRIX worldTransform = XMLoadFloat4x4(&_originalOrientation) * rotationYaw * rotationPitch * rotationRoll * XMMatrixTranslation(_position.x, _position.y, _position.z);
	XMStoreFloat4x4(&_worldTransformation, worldTransform);
	SceneNode::Update(currentWorldTransformation);

}

void ObjectNode::Render()
{
	MeshNode::Render();
}

void ObjectNode::SetTotalRoll(float roll)
{
	_roll = XMConvertToRadians(roll);
}

float ObjectNode::GetRoll() const
{
	return XMConvertToDegrees(_roll);
}

void ObjectNode::SetLeftRight(float leftRight)
{
	_moveLeftRight = leftRight;
}

void ObjectNode::SetForwardBack(float forwardBack)
{
	_moveForwardBack = forwardBack;
}

void ObjectNode::SetStartOrientation(XMMATRIX originalOrientation)
{
	XMStoreFloat4x4(&_originalOrientation, originalOrientation);
}

XMMATRIX ObjectNode::GetWorldTransformation() const
{
	return XMLoadFloat4x4(&_combinedWorldTransformation);
}

XMVECTOR ObjectNode::GetPosition(void)
{
	return XMLoadFloat4(&_position);
}

void ObjectNode::SetPosition(float x, float y, float z)
{
	_position = XMFLOAT4(x, y, z, 0.0f);
}

void ObjectNode::SetPitch(float pitch)
{
	_pitch += XMConvertToRadians(pitch);
}

void ObjectNode::SetTotalPitch(float pitch)
{
	_pitch += XMConvertToRadians(pitch);
}

float ObjectNode::GetPitch() const
{
	return XMConvertToDegrees(_pitch);
}

void ObjectNode::SetYaw(float yaw)
{
	_yaw += XMConvertToRadians(yaw);
}

void ObjectNode::SetTotalYaw(float yaw)
{
	_yaw += XMConvertToRadians(yaw);
}

float ObjectNode::GetYaw() const
{
	return XMConvertToDegrees(_yaw);
}

void ObjectNode::SetRoll(float roll)
{
	_roll += XMConvertToRadians(roll);
}
