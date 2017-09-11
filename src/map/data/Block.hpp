#pragma once
#pragma once

#include "BlockData.hpp"

typedef unsigned char BlockId;

class Block {
	BlockId m_id;
public:
	Block() : m_id(0) {};
	Block(BlockId id) : m_id(id) {};
	operator BlockId() { return m_id; };
	Block& operator=(BlockId id) { m_id = id; return *this; };
	bool operator==(BlockId id)  {return m_id == id;};
	bool operator!=(BlockId id)  {return m_id != id;};

	const BlockData& getData();
};
