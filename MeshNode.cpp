#include "MeshNode.h"

XMVECTOR defaultForwardPlane = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
XMVECTOR defaultRightPlane = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
XMVECTOR defaultUpPlane = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

MeshNode::~MeshNode()
{
}

bool MeshNode::Initialise()
{
	_resourceManager = DirectXFramework::GetDXFramework()->GetResourceManager();
	_renderer = dynamic_pointer_cast<MeshRenderer>(_resourceManager->GetRenderer(L"PNT"));
	_mesh = _resourceManager->GetMesh(_modelName);
	if (_mesh == nullptr)
	{
		return false;
	}
	return _renderer->Initialise();
}

void MeshNode::Shutdown()
{
	_resourceManager->ReleaseMesh(_modelName);
}

void MeshNode::Render()
{
	_renderer->SetMesh(_mesh);
	_renderer->SetWorldTransformation(XMLoadFloat4x4(&_combinedWorldTransformation));
	_renderer->SetCameraPosition(XMFLOAT4(0.0f, 0.0f, -100.0f, 1.0f));
	_renderer->SetAmbientLight(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	_renderer->SetDirectionalLight(XMVectorSet(0.0f, -1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	_renderer->Render();
}

void MeshNode::Update(void)
{
	XMVECTOR planePosition;
	XMVECTOR planeTarget;
	XMVECTOR planeRight;
	XMVECTOR planeForward;
	XMVECTOR planeUp;

	// Yaw (rotation around the Y axis) will have an impact on the forward and right vectors
	XMMATRIX planeRotationYaw = XMMatrixRotationAxis(defaultUpPlane, _planeYaw);
	planeRight = XMVector3TransformCoord(defaultRightPlane, planeRotationYaw);
	planeForward = XMVector3TransformCoord(defaultForwardPlane, planeRotationYaw);

	// Pitch (rotation around the X axis) impact the up and forward vectors
	XMMATRIX planeRotationPitch = XMMatrixRotationAxis(planeRight, _planePitch);
	planeUp = XMVector3TransformCoord(defaultUpPlane, planeRotationPitch);
	planeForward = XMVector3TransformCoord(planeForward, planeRotationPitch);

	// Roll (rotation around the Z axis) will impact the Up and Right vectors
	XMMATRIX planeRotationRoll = XMMatrixRotationAxis(planeForward, _planeRoll);
	planeUp = XMVector3TransformCoord(planeUp, planeRotationRoll);
	planeRight = XMVector3TransformCoord(planeRight, planeRotationRoll);

	// Adjust the camera position by the appropriate amount forward/back and left/right
	planePosition = XMLoadFloat4(&_planePosition) + _moveLeftRight * planeRight + _moveForwardBack * planeForward;
	XMStoreFloat4(&_planePosition, planePosition);

	// Reset the amount we are moving
	_moveLeftRight = 0.0f;
	_moveForwardBack = 0.0f;

	// Calculate a vector that tells us the direction the camera is looking in
	planeTarget = planePosition + XMVector3Normalize(planeForward);

	// and calculate our view matrix
	XMStoreFloat4x4(&_viewMatrix, XMMatrixLookAtLH(planePosition, planeTarget, planeUp));
}

void MeshNode::SetLeftRight(float leftRight)
{
	_moveLeftRight = leftRight;
}

void MeshNode::SetForwardBack(float forwardBack)
{
	_moveForwardBack = forwardBack;
}

void MeshNode::SetPlanePosition(float x, float y, float z)
{
	_planePosition = XMFLOAT4(x, y, z, 0.0f);
}


