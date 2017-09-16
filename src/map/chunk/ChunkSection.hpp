#pragma once

#include <array>
#include <memory>

#include "map/data/Block.hpp"
#include "Mesh.hpp"
#include "map/Constants.hpp"
#include "util/Vector.hpp"

class MapBase;
class ChunkBuilder;

struct ChunkMeshes {
	Mesh solid, liquid;
	MeshData solidData, liquidData;
};

class ChunkSection
{
public:
	ChunkSection() = default;
	ChunkSection(Vec3 position, const MapBase* const map);

	ChunkSection(ChunkSection&&);
	ChunkSection& operator=(ChunkSection&&);

	Vec3 toWorldPosition(int x, int y, int z) const;

	void setBlock(int x, int y, int z, Block Block);
	Block getBlock(int x, int y, int z) const;
	const Vec3& getPosition() const { return m_position; };

	void update();
	void modify() { m_modified = true; };
	void regenerateMeshData();


	const ChunkMeshes& getMeshes() const { return m_meshes; };

private:
	bool outOfBound(int x, int y, int z) const;

	bool m_modified;
	Vec3 m_position;
	std::array<Block, ChunkVolume> m_blocks;
	
	ChunkMeshes m_meshes;
	bool m_modifyMeshes;

	const MapBase* m_map;
};
