#include "SceneGraph.h"

using std::vector;

bool SceneGraph::Initialise()
{
	// This is using recursive programming to Intialise all of the child nodes.
	bool init_status = true;
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
	// Using vector<DsceneNodePointer>::iterator shows that we are going to iterate through the _children collection
	vectorIterator != end(_children) && init_status;
	vectorIterator++)
	{
	init_status = (*vectorIterator)->Initialise();
	}
	return init_status;
}

void SceneGraph::Update(FXMMATRIX& currentWorldTransformation)
{
	// Calls upon the SceneNode Update method to change the current WorldTransformation
	SceneNode::Update(currentWorldTransformation);
	XMMATRIX updatedWorldTransformation = XMLoadFloat4x4(&_combinedWorldTransformation);
	// same loop structure to go through a recursive function
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
		vectorIterator != end(_children);
		vectorIterator++)
	{
		// This passes through with the updatedWorld Transformation meaning it is always being updated each loop through
		(*vectorIterator)->Update(updatedWorldTransformation);
	}
}

void SceneGraph::Render(void)
{
	// Sends each child node through the rendering method
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
		vectorIterator != end(_children);
		vectorIterator++)
	{
		(*vectorIterator)->Render();
	}
}

void SceneGraph::Shutdown(void)
{
	// each child node within the collection will be shut down within the collection
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
		vectorIterator != end(_children);
		vectorIterator++)
	{
		(*vectorIterator)->Shutdown();
	}
}

void SceneGraph::Add(SceneNodePointer node)
{
	// This is adding the node that has been passed to this method into the collection of child nodes 
	_children.push_back(node);
}

void SceneGraph::Remove(SceneNodePointer node)
{
	// This will go through the collection and look for the specific node and remove it from the collection
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
		vectorIterator != end(_children);
		vectorIterator++)
	{
		// Removes it from further down the collection if it occurs there
		(*vectorIterator)->Remove(node);
		// If this is the node to remove then you can take it out of the collection
		if (*vectorIterator == node)
		{
			_children.erase(vectorIterator);
		}
	}
}

SceneNodePointer SceneGraph::Find(wstring name)
{
	if (_name == name)
	{
		return shared_from_this();
	}
	SceneNodePointer returnValue = nullptr;
	for (vector<SceneNodePointer>::iterator vectorIterator = begin(_children);
		vectorIterator != end(_children);
		vectorIterator++)
	{
		returnValue = (*vectorIterator)->Find(name);
	}
	return returnValue;
}
