#pragma once

constexpr int AtlasCount = 16;
constexpr float AtlasUnit = 1 / float(AtlasCount);

constexpr int ChunkLength = 16;
constexpr int ChunkArea = ChunkLength * ChunkLength;
constexpr int ChunkVolume = ChunkArea * ChunkLength;

constexpr int ChunkHeight = 16;
constexpr int BlockHeight = ChunkHeight * ChunkLength;
