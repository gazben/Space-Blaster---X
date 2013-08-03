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

#include <Thor/Multimedia/BigSprite.hpp>
#include <Thor/Multimedia/BigTexture.hpp>
#include <Thor/Tools/ForEach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cassert>


namespace thor
{
	
BigSprite::BigSprite()
: sf::Drawable()
, sf::Transformable()
, mSize(0.f, 0.f)
, mSplitSprites()
, mColor(sf::Color::White)
{
}

BigSprite::BigSprite(const BigTexture& texture)
: sf::Drawable()
, sf::Transformable()
, mSize()
, mSplitSprites()
, mColor(sf::Color::White)
{
	SetTexture(texture);
}

void BigSprite::SetTexture(const BigTexture& texture)
{
	mSize = texture.FillSprites(mColor, mSplitSprites);
}

void BigSprite::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.Transform *= GetTransform();

	THOR_CONST_FOREACH(std::vector<sf::Sprite>, mSplitSprites, itr)
		target.Draw(*itr, states);
}

void BigSprite::SetColor(const sf::Color& color)
{
	mColor = color;
	THOR_FOREACH(std::vector<sf::Sprite>, mSplitSprites, itr)
		itr->SetColor(color);
}

sf::Color BigSprite::GetColor() const
{
	return mColor;
}

sf::FloatRect BigSprite::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mSize.x, mSize.y);
}

sf::FloatRect BigSprite::GetGlobalBounds() const
{
	return GetTransform().TransformRect(GetLocalBounds());
}

} // namespace thor
