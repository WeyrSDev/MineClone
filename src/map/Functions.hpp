#pragma once

#include "util/Vector.hpp"
#include "chunk/Chunk.hpp"

Vec3 getBlockFromPoint(Vec3 point);

ChunkId getChunkFromBlock(int x, int z);

Vec3 toChunkRelativePosition(int x, int y, int z);
