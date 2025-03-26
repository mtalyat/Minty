#include "pch.h"
#include "WindowManager.h"

using namespace Minty;

void Minty::WindowManager::set_main(UUID const id)
{
	MINTY_ASSERT(m_windows.contains(id), "Window does not exist with the given id.");

	m_main = get_window(id);
}

Ref<Window> Minty::WindowManager::create_window(WindowBuilder const& builder)
{
    // create the window
    Owner<Window> window = Window::create(builder);
	Ref<Window> windowRef = window.create_ref();

	// add it to the list
	MINTY_ASSERT(!m_windows.contains(builder.id), "Window already exists with the same id.");
	m_windows.add(builder.id, std::move(window));

	return windowRef;
}

void Minty::WindowManager::destroy_window(UUID const id)
{
	MINTY_ASSERT(m_windows.contains(id), "Window does not exist with the given id.");

	m_windows.remove(id);
}

Ref<Window> Minty::WindowManager::get_window(UUID const id)
{
	auto it = m_windows.find(id);

	if (it == m_windows.end())
	{
		return nullptr;
	}

	return it->second;
}
