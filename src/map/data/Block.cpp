#include "Block.hpp"

#include "BlockDataBase.hpp"

const BlockData& Block::getData()
{
	return BlockDataBase::get().getBlockData(m_id);
}
