#pragma once
#include "string"

__interface IPersistent
{
	void save_to_file(std::string file_name) const;

	void load_from_file(std::string file_name);
};