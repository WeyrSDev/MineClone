#include <stdexcept>
#include <sstream>
#include <fstream>

#include "Files.hpp"

std::string getFileSrc(std::string sf)
{
	std::ifstream file(sf);
	std::stringstream strStream;

	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file " + sf);
	}

	strStream << file.rdbuf();

	return strStream.str().c_str();
}
