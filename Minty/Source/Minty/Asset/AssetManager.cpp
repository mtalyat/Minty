#include "pch.h"
#include "AssetManager.h"
#include "Minty/Core/Format.h"

using namespace Minty;

Bool Minty::AssetManager::load_wrap(Path const& path)
{
	if (!Path::exists(path))
	{
		MINTY_ERROR(F("Cannot load Wrap file. Path does not exist: {}", path));
		return false;
	}

	m_wrapper.add(path);

	return true;
}
