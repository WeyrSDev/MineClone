#pragma once

#include <array>
#include <memory>

#include "map/data/Block.hpp"
#include "Mesh.hpp"
#include "map/Constants.hpp"
#include "util/Vector.hpp"

class MapBase;
class ChunkBuilder;

class ChunkSection
{
public:
	ChunkSection(Vec3 position, const MapBase* const map);

	Vec3 toWorldPosition(int x, int y, int z) const;

	void setBlock(int x, int y, int z, Block Block);
	Block getBlock(int x, int y, int z) const;
	const Vec3& getPosition() const { return m_position; };

	void update();
	void modify() { m_modified = true; };
	void regenerateMeshData();


	const Mesh* getMesh() const { return &m_mesh; };

private:
	bool outOfBound(int x, int y, int z) const;

	bool m_modified;
	const Vec3 m_position;
	std::array<Block, ChunkVolume> m_blocks;
	Mesh m_mesh;
	MeshData m_solidMeshData;
	bool m_modifyMesh;
	const MapBase* const m_map;
};
