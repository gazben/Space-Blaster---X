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

#include <Thor/Detail/ActionOperations.hpp>

#include <SFML/Window/Window.hpp>

#include THOR_TR1_HEADER(functional)
#include <iterator>
#include <algorithm>

using namespace std::tr1::placeholders;


namespace thor
{
namespace detail
{

	bool CompareEvents::operator() (const sf::Event& lhs, const sf::Event& rhs) const
	{
		// Note: Events with the same Type member are equivalent.
		// They are differentiated by the FilterOut() functions if necessary.
		return lhs.Type < rhs.Type;
	}
	
	// ---------------------------------------------------------------------------------------------------------------------------


	EventBuffer::EventBuffer(sf::Window& window)
	: mEventSet()
	, mWindow(window)
	, mRealtimeEnabled(true)
	{
	}

	void EventBuffer::PushEvent(const sf::Event& event)
	{
		// Generate realtime actions only if window has the focus. For example, key presses don't invoke callbacks when the
		// window is not focussed.
		switch (event.Type)
		{
			case sf::Event::GainedFocus:
				mRealtimeEnabled = true;
				break;

			case sf::Event::LostFocus:
				mRealtimeEnabled = false;
				break;
		}

		// Store event
		mEventSet.insert(event);
	}

	void EventBuffer::ClearEvents()
	{
		mEventSet.clear();
	}

	bool EventBuffer::ContainsEvent(const sf::Event& event) const
	{
		return mEventSet.find(event) != mEventSet.end();
	}

	bool EventBuffer::ContainsEvent(const sf::Event& event, const ActionNode& filterNode) const
	{
		std::vector<sf::Event> unused;
		return GetEvents(event.Type, unused, filterNode);
	}

	bool EventBuffer::GetEvents(sf::Event::EventType eventType, std::vector<sf::Event>& out) const
	{
		// Create event object acting as key in the multiset
		sf::Event key = {};
		key.Type = eventType;

		// Copy found range to output vector
		std::pair<EventSet::const_iterator, EventSet::const_iterator> range = mEventSet.equal_range(key);
		out.insert(out.end(), range.first, range.second);
		return range.first != range.second;
	}

	bool EventBuffer::GetEvents(sf::Event::EventType eventType, std::vector<sf::Event>& out, const ActionNode& filterNode) const
	{
		// Collect all events with event.Type == eventType
		std::vector<sf::Event> newEvents;
		GetEvents(eventType, newEvents);

		// Copy events that are really equal (e.g. same key) to the end of the output vector
		std::size_t oldSize = out.size();
		std::remove_copy_if(newEvents.begin(), newEvents.end(), std::back_inserter(out), std::tr1::bind(&ActionNode::FilterOut, &filterNode, _1));
		return oldSize != out.size();
	}

	sf::Window& EventBuffer::GetWindow() const
	{
		return mWindow;
	}

	bool EventBuffer::IsRealtimeInputEnabled() const
	{
		return mRealtimeEnabled;
	}

	void EventBuffer::PollEvents()
	{
		sf::Event event;

		while (mWindow.PollEvent(event))
			PushEvent(event);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	ActionNode::~ActionNode()
	{
	}

	bool ActionNode::FilterOut(const sf::Event&) const
	{
		return false;
	}
	
	// ---------------------------------------------------------------------------------------------------------------------------
	

	bool RealtimeNode::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Increase counter if derived class (Realtime leaf) returns true
		bool active = IsActionActive(buffer);
		out.nbRealtimeTriggers += static_cast<unsigned int>(active);
		return active;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeKeyLeaf::RealtimeKeyLeaf(sf::Keyboard::Key key)
	: RealtimeNode()
	, mKey(key)
	{
	}

	bool RealtimeKeyLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.IsRealtimeInputEnabled() && sf::Keyboard::IsKeyPressed(mKey);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventKeyLeaf::EventKeyLeaf(sf::Keyboard::Key key, bool pressed)
	: ActionNode()
	, mKeyEvent()
	{
		mKeyEvent.Type = pressed ? sf::Event::KeyPressed : sf::Event::KeyReleased;
		mKeyEvent.Key.Code = key;
	}

	bool EventKeyLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.ContainsEvent(mKeyEvent, *this);
	}

	bool EventKeyLeaf::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return buffer.GetEvents(mKeyEvent.Type, out.eventContainer, *this);
	}

	bool EventKeyLeaf::FilterOut(const sf::Event& event) const
	{
		return event.Type != mKeyEvent.Type || event.Key.Code != mKeyEvent.Key.Code;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeMouseLeaf::RealtimeMouseLeaf(sf::Mouse::Button mouseButton)
	: RealtimeNode()
	, mMouseButton(mouseButton)
	{
	}

	bool RealtimeMouseLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.IsRealtimeInputEnabled() && sf::Mouse::IsButtonPressed(mMouseButton);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventMouseLeaf::EventMouseLeaf(sf::Mouse::Button mouseButton, bool pressed)
	: ActionNode()
	, mMouseEvent()
	{
		mMouseEvent.Type = pressed ? sf::Event::MouseButtonPressed : sf::Event::MouseButtonReleased;
		mMouseEvent.MouseButton.Button = mouseButton;
	}

	bool EventMouseLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.ContainsEvent(mMouseEvent, *this);
	}

	bool EventMouseLeaf::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return buffer.GetEvents(mMouseEvent.Type, out.eventContainer, *this);
	}

	bool EventMouseLeaf::FilterOut(const sf::Event& event) const
	{
		return event.Type != mMouseEvent.Type || event.MouseButton.Button != mMouseEvent.MouseButton.Button;
	}


	// ---------------------------------------------------------------------------------------------------------------------------
	

	RealtimeJoystickLeaf::RealtimeJoystickLeaf(Joystick joystick)
	: RealtimeNode()
	, mJoystick(joystick)
	{
	}

	bool RealtimeJoystickLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.IsRealtimeInputEnabled() && sf::Joystick::IsButtonPressed(mJoystick.Id, mJoystick.Button);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventJoystickLeaf::EventJoystickLeaf(Joystick joystick, bool pressed)
	: ActionNode()
	, mJoystickEvent()
	{
		mJoystickEvent.Type = pressed ? sf::Event::JoystickButtonPressed : sf::Event::JoystickButtonReleased;
		mJoystickEvent.JoystickButton.JoystickId = joystick.Id;
		mJoystickEvent.JoystickButton.Button = joystick.Button;
	}

	bool EventJoystickLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.ContainsEvent(mJoystickEvent, *this);
	}

	bool EventJoystickLeaf::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return buffer.GetEvents(mJoystickEvent.Type, out.eventContainer, *this);
	}

	bool EventJoystickLeaf::FilterOut(const sf::Event& event) const
	{
		return event.Type != mJoystickEvent.Type || event.JoystickButton.Button != mJoystickEvent.JoystickButton.Button;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	MiscEventLeaf::MiscEventLeaf(sf::Event::EventType eventType)
	: mEvent()
	{
		mEvent.Type = eventType;
	}

	bool MiscEventLeaf::IsActionActive(const EventBuffer& buffer) const
	{
		return buffer.ContainsEvent(mEvent);
	}

	bool MiscEventLeaf::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return buffer.GetEvents(mEvent.Type, out.eventContainer);
	}

	// ---------------------------------------------------------------------------------------------------------------------------
	
	
	OrNode::OrNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs)
	: ActionNode()
	, mLhs()
	, mRhs()
	{
		mLhs.Swap(lhs);
		mRhs.Swap(rhs);
	}

	bool OrNode::IsActionActive(const EventBuffer& buffer) const
	{
		return mLhs->IsActionActive(buffer) || mRhs->IsActionActive(buffer);
	}

	bool OrNode::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Prevent shortcut semantics of logical OR: If first operand is true, the second's vector isn't filled.
		bool lhsValue = mLhs->IsActionActive(buffer, out);
		bool rhsValue = mRhs->IsActionActive(buffer, out);

		return lhsValue || rhsValue;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	AndNode::AndNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs)
	: ActionNode()
	, mLhs()
	, mRhs()
	{
		mLhs.Swap(lhs);
		mRhs.Swap(rhs);
	}

	bool AndNode::IsActionActive(const EventBuffer& buffer) const
	{
		return mLhs->IsActionActive(buffer) && mRhs->IsActionActive(buffer);
	}

	bool AndNode::IsActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Don't modify out if whole logical AND expression is false -> use temporary result state
		ActionResult tmpResult;

		// If both calls return true, copy events and realtime counter
		if (mLhs->IsActionActive(buffer, tmpResult) && mRhs->IsActionActive(buffer, tmpResult))
		{
			out.eventContainer.insert(out.eventContainer.end(), tmpResult.eventContainer.begin(), tmpResult.eventContainer.end());
			out.nbRealtimeTriggers += tmpResult.nbRealtimeTriggers;
			return true;
		}
		else
		{
			return false;
		}
	}

} // namespace detail
} // namespace thor
