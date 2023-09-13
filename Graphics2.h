#pragma once
#include "DirectXFramework.h"
#include "TexturedCubeNode.h"
#include "MeshNode.h"
#include "TerrainNode.h"
#include "SkyNode.h"
#include "ObjectNode.h"

class Graphics2 : public DirectXFramework
{
public:
	void CreateSceneGraph();
	void UpdateSceneGraph();

private:
	shared_ptr<MeshNode> plane;
};

