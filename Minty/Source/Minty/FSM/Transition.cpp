#include "pch.h"
#include "Transition.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Transition::add_condition(Condition const& condition)
{
	m_conditions.add(condition);
}

Bool Minty::Transition::evaluate(BasicScope const& scope) const
{
	for (auto const& condition : m_conditions)
	{
		if (!condition.evaluate(scope))
		{
			return false;
		}
	}
	return true;
}

void Minty::Transition::serialize(Writer& writer) const
{

}

Bool Minty::Transition::deserialize(Reader& reader)
{
	return Bool();
}
