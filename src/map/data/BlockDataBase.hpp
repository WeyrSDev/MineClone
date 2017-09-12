#pragma once

#include <array>
#include <memory>

#include "util/Singleton.hpp"
#include "Block.hpp"

enum class BlocksIds : BlockId {
	air = 0,
	grass,
	dirt,
	stone,
	water,
	sand,

	count
};

class BlockDataBase : public Singleton
{
public:
	static const BlockDataBase& get();

	const BlockData& getBlockData(BlockId block) const;
private:
	BlockDataBase();
	~BlockDataBase() = default;
	
	std::array<std::unique_ptr<BlockData>, static_cast<unsigned int>(BlocksIds::count)> m_blocks;
};
