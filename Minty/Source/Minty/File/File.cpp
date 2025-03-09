#include "pch.h"
#include "File.h"

using namespace Minty;

void Minty::File::copy(Path const& from, Path const& to)
{
	std::filesystem::copy_file(from.get_string().get_data(), to.get_string().get_data(), std::filesystem::copy_options::overwrite_existing);
}

void Minty::File::move(Path const& from, Path const& to)
{
	std::filesystem::rename(from.get_string().get_data(), to.get_string().get_data());
}

void Minty::File::create(Path const& path)
{
	std::ofstream file(path.get_string().get_data());
	file.close();
}

void Minty::File::destroy(Path const& path)
{
	std::filesystem::remove(path.get_string().get_data());
}
