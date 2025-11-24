#include "pch.h"
#include "ConstantContainer.h"

void Minty::ConstantContainer::clear()
{
	memset(mp_data, 0, m_size);
}
