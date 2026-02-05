#include "pch.h"
#include "System.h"
#include "Minty/Scene/Scene.h"
#include "Minty/System/SystemInfo.h"

using namespace Minty;

Minty::System::System(SystemInfo const &info)
	: m_scene(info.scene), m_data(info.info), m_priority(info.priority)
{
}