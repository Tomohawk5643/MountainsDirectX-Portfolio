#include "Graphics2.h"


Graphics2 app;

void Graphics2::CreateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();
	
	// This is where you add nodes to the scene graph

	shared_ptr<MeshNode> node = make_shared<MeshNode>(L"LandedPlane", L"Bonanza.3DS");
	node->SetWorldTransform(XMMatrixScaling(20, 20, 20) * XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 0.5 * XM_PI) * XMMatrixTranslation(0.0f, 500.0f, 100.0f));
	sceneGraph->Add(node);

	plane = make_shared<MeshNode>(L"Plane", L"Bonanza.3DS");
	plane->SetWorldTransform(XMMatrixScaling(20, 20, 20) * XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 0.5 * XM_PI) * XMMatrixTranslation(0.0f, 1000.0f, 1400.0f));
	plane->SetPlanePosition(0.0f, 1000.0f, 1400.0f);
	sceneGraph->Add(plane);

	shared_ptr<TerrainNode> terrain_node = make_shared<TerrainNode>(L"FlatPlain");
	sceneGraph->Add(terrain_node);

	shared_ptr<SkyNode> sky_node = make_shared<SkyNode>(L"Sky", L"skymap.dds", 6000.0f);
	sceneGraph->Add(sky_node);

	//_planeNode = make_shared<ObjectNode>(L"Plane1", L"Bonanza.3DS");
	//_planeNode->SetStartOrientation(XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XM_PI) * XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 0.5 * XM_PI));
	//_planeNode->SetPosition(0.0f, 1000.0f, -1500.0f);
	//sceneGraph->Add(_planeNode);

	GetCamera()->SetCameraPosition(0.0f, 1000.0f, 1500.0f);
	// GetCamera()->SetFollowObject(_planeNode, XMFLOAT3(0.0f, 20.0f, -50.0f), true);
	// This is also where you can add the terrain node to the scene graph
}

void Graphics2::UpdateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();

	plane->SetForwardBack(2);
	plane->SetLeftRight(2);

	GetCamera()->SetForwardBack(2);
	//GetCamera()->SetTotalRoll(0);

	if (GetAsyncKeyState(VK_UP) < 0)
	{
		GetCamera()->SetPitch(-1);
	}

	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		GetCamera()->SetPitch(0.5);
	}

	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		GetCamera()->SetYaw(-0.5);
		GetCamera()->SetTotalRoll(1);
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0)
	{
		GetCamera()->SetYaw(0.5);
		GetCamera()->SetTotalRoll(-1);
	}
}
