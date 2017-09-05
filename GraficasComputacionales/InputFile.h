//GABRIELA AGUILAR LUGO A01373890
//GRAFICAS COMPUTACIONALES
//PRIMER PARCIAL

#pragma once

#include <string>

class InputFile
{
public:
	bool Read(const std::string& filename);
	const std::string GetContents() const;

private:
	std::string _contents;
};

