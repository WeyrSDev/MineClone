#pragma once

#include "renderer/MasterRenderer.hpp"
#include "chunk/Chunk.hpp"

class MapBase {
public:
	virtual Block getBlock(int x, int y, int z) const  = 0;
	virtual void setBlock(int x, int y, int z, Block block) = 0;
	virtual void update(MasterRenderer& renderer) = 0;
};
