#include "BlockDataBase.hpp"

const BlockDataBase& BlockDataBase::get()
{
	static BlockDataBase obj;
	return obj;
}

const BlockData& BlockDataBase::getBlockData(BlockId id) const {
	if (id >= (BlockId) BlocksIds::count)
	{
		return *m_blocks[static_cast<BlockId>(BlocksIds::air)];
	}
	return *m_blocks[id];
}

BlockDataBase::BlockDataBase()
{
	m_blocks[static_cast<BlockId>(BlocksIds::air)] = std::make_unique<BlockData>(Vec2(0, 0), Vec2(0, 0), Vec2(0, 0));
	m_blocks[static_cast<BlockId>(BlocksIds::grass)] = std::make_unique<BlockData>(Vec2(0, 0), Vec2(2, 0), Vec2(1, 0));
	m_blocks[static_cast<BlockId>(BlocksIds::dirt)] = std::make_unique<BlockData>(Vec2(2, 0), Vec2(2, 0), Vec2(2, 0));
	m_blocks[static_cast<BlockId>(BlocksIds::stone)] = std::make_unique<BlockData>(Vec2(12, 0), Vec2(12, 0), Vec2(12, 0));
}
