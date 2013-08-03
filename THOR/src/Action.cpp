/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <Thor/Events/Action.hpp>

#include <algorithm>
#include <cassert>


namespace thor
{

Action::Action()
: mOperation()
{
}

Action::Action(sf::Keyboard::Key key, ActionType action)
: mOperation()
{
	switch (action)
	{
		case Realtime:
			mOperation.Reset(new detail::RealtimeKeyLeaf(key));
			break;

		case PressOnce:
		case ReleaseOnce:
			mOperation.Reset(new detail::EventKeyLeaf(key, action == PressOnce));
			break;

		case Once:
			*this = Action(key, PressOnce) || Action(key, ReleaseOnce);
			break;
	}
}

Action::Action(sf::Mouse::Button mouseButton, ActionType action)
: mOperation()
{
	switch (action)
	{
		case Realtime:
			mOperation.Reset(new detail::RealtimeMouseLeaf(mouseButton));
			break;

		case PressOnce:
		case ReleaseOnce:
			mOperation.Reset(new detail::EventMouseLeaf(mouseButton, action == PressOnce));
			break;

		case Once:
			*this = Action(mouseButton, PressOnce) || Action(mouseButton, ReleaseOnce);
			break;
	}
}

Action::Action(Joystick joystick, ActionType action)
: mOperation()
{
	switch (action)
	{
		case Realtime:
			mOperation.Reset(new detail::RealtimeJoystickLeaf(joystick));
			break;

		case PressOnce:
		case ReleaseOnce:
			mOperation.Reset(new detail::EventJoystickLeaf(joystick, action == PressOnce));
			break;

		case Once:
			*this = Action(joystick, PressOnce) || Action(joystick, ReleaseOnce);
			break;
	}
}

Action::Action(sf::Event::EventType eventType)
: mOperation(new detail::MiscEventLeaf(eventType))
{
}

bool Action::IsActive(const detail::EventBuffer& buffer) const
{
	return mOperation->IsActionActive(buffer);
}

bool Action::IsActive(const detail::EventBuffer& buffer, detail::ActionResult& out) const
{
	return mOperation->IsActionActive(buffer, out);
}

Action::Action(detail::ActionNode::MovedPtr newOperation)
: mOperation(newOperation)
{
}

Action operator|| (const Action& lhs, const Action& rhs)
{
	detail::ActionNode::MovedPtr result( new detail::OrNode(lhs.mOperation, rhs.mOperation) );
	return Action(result);
}

Action operator&& (const Action& lhs, const Action& rhs)
{
	detail::ActionNode::MovedPtr result( new detail::AndNode(lhs.mOperation, rhs.mOperation) );
	return Action(result);
}

} // namespace thor
