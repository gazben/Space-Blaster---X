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

/// @file
/// @brief Class template thor::ActionMap

#ifndef THOR_ACTIONMAP_HPP
#define THOR_ACTIONMAP_HPP

#include <Thor/Events/Action.hpp>
#include <Thor/Events/ActionContext.hpp>
#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Tools/ForEach.hpp>
#include <Thor/Detail/ActionOperations.hpp>

#include <map>


namespace thor
{

template <typename Event, typename EventIdentifier>
class EventSystem;


/// @addtogroup Events
/// @{

/// @brief Class template that associates identifiers with dynamic actions
/// @details You can use this template to map identifiers like strings or enumerators to a specific combination of SFML events
///  (sf::Event) and real time input states (sf::Mouse, sf::Keyboard, sf::Joystick). After the initialization, IsActive() provides
///  an easy way to check whether a specified identifier is associated with an active action. Furthermore, it is possible to map
///  the actions to callbacks, which can be achieved with InvokeCallbacks().
/// @tparam ActionIdentifier The type of ID you want to map to actions. This can be a string, an enum, or anything with a < operator
///  and value semantics.
template <typename ActionIdentifier>
class ActionMap : private NonCopyable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public types
	public:
		/// @brief EventSystem to connect ActionMap with event listeners.
		/// 
		typedef EventSystem< ActionContext<ActionIdentifier>, ActionIdentifier > CallbackSystem;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param window The SFML window used for event generation and referenced in ActionContext objects. 
		explicit					ActionMap(sf::Window& window);

		/// @brief Clears old events and polls the window for new ones.
		/// @details When you invoke this method, you should not call sf::Window::PollEvent() in the same frame, since Update()
		///  already does that. The following code
		/// @code
		/// map.Update();
		/// @endcode
		/// is equivalent to
		/// @code
		/// map.ClearEvents();
		///
		/// sf::Event event;
		/// while (window.PollEvent(event))
		///     map.PushEvent(event);
		/// @endcode
		void						Update();

		/// @brief Feeds the action map with a SFML event, that can be used during the current frame.
		/// @details When you use the Update() method, you needn't invoke PushEvent(). This method exists for more flexibility:
		///  You can push user-defined events, and you can do something else with the polled events before calling PushEvent().
		void						PushEvent(const sf::Event& event);

		/// @brief Removes the events that have been temporarily stored.
		/// @details You only need this function in combination with PushEvent(), if you want to feed the action map manually with events.
		///  Otherwise, you can just call Update().
		void						ClearEvents();

		/// @brief Returns the action associated with a given action identifier.
		/// @details Use this function to create new associations. If the action id hasn't been stored yet, it is inserted and
		///  an empty action is returned. Assign an object of type thor::Action to it. Example:
		/// @code
		/// thor::ActionMap<std::string> map(...);
		/// map["run"] = thor::Action(sf::Keyboard::R);
		/// @endcode
		Action&						operator[] (const ActionIdentifier& id);

		/// @brief Remove the action associated with the specified @a id.
		///
		void						RemoveAction(const ActionIdentifier& id);

		/// @brief Removes all actions associated with this map.
		///
		void						ClearActions();

		/// @brief Returns whether the action associated with the specified identifier is currently in effect.
		/// @details To be in effect, the boolean operation of the assigned action must yield true. Note that in contrast
		///  to registered callbacks, IsActive() doesn't take into account the situation where multiple events of the same
		///  type occur in a single frame.
		/// @code
		/// // If LCtrl+A or B is pressed, the action is active.
		/// thor::Action(sf::Keyboard::A) && thor::Action(sf::Keyboard::LCtrl) || thor::Action(sf::Keyboard::B);
		/// @endcode
		bool						IsActive(const ActionIdentifier& id) const;

		/// @brief Forwards active actions to a callback system.
		/// @param system Callback system of type EventSystem< ActionContext<ActionIdentifier>, ActionIdentifier >
		/// @details For every action that is currently active, the action ID is passed to @a system, where all listener
		///  functions associated with the ID are invoked.
		/// @code
		/// // Listener function for "run" actions
		/// void Callback(const thor::ActionContext<std::string>& context);
		///
		/// // Map to register "run" action
		/// thor::ActionMap<std::string> map(...);
		/// map["run"] = thor::Action(sf::Keyboard::R);
		///
		/// // Create EventSystem object, connect "run" action to callback
		/// thor::ActionMap<std::string>::CallbackSystem system;
		/// system.Connect("run", &Callback);
		///
		/// // In the main loop: Forward actions to the callback system
		/// map.InvokeCallbacks(system);
		/// @endcode
		void						InvokeCallbacks(CallbackSystem& system) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		typedef std::map<ActionIdentifier, Action> Map;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		Map							mActionMap;
		detail::EventBuffer			mEventBuffer;
};

/// @}

} // namespace thor

#include <Thor/Detail/ActionMap.inl>
#endif // THOR_ACTIONMAP_HPP
