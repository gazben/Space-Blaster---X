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

#include <Thor/Multimedia/ConcaveShape.hpp>
#include <Thor/Multimedia/Shapes.hpp>
#include <Thor/SmartPtr/MovedPtr.hpp>
#include <Thor/Math/Triangulation.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Tools/ForEach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>


namespace thor
{

struct ConcaveShape::TriangleGenerator
{
	TriangleGenerator(ShapeContainer& triangles, const sf::Color& color)
	: triangles(triangles)
	, color(color)
	{
		triangles.clear();
	}

	// Fake dereferencing
	TriangleGenerator& operator* ()
	{
		return *this;
	}
	
	// Fake pre-increment
	TriangleGenerator& operator++ ()
	{
		return *this;
	}
	
	// Fake post-increment
	TriangleGenerator& operator++ (int)
	{
		return *this;
	}
	
	// Assignment from triangle
	TriangleGenerator& operator= (const Triangle<Vertex>& triangle)
	{
		sf::ConvexShape* shape = new sf::ConvexShape();
		shape->SetPointCount(3);
		shape->SetFillColor(color);
		
		for (unsigned int i = 0; i < 3; ++i)
			shape->SetPoint(i, triangle[i].GetPosition());
		
		triangles.push_back( CopiedPtr<sf::Shape>(shape) );
		return *this;
	}

	ShapeContainer&	triangles;
	sf::Color		color;
};

// ---------------------------------------------------------------------------------------------------------------------------


ConcaveShape::ConcaveShape()
: sf::Drawable()
, sf::Transformable()
, mPoints()
, mFillColor()
, mOutlineColor()
, mOutlineThickness(0.f)
, mEdges()
, mTriangleShapes()
, mEdgeShapes()
, mNeedsTriangleUpdate(false)
, mNeedsEdgeUpdate(false)
{
}

ConcaveShape::ConcaveShape(const sf::Shape& shape)
: sf::Drawable()
, sf::Transformable(shape)
, mPoints()
, mFillColor(shape.GetFillColor())
, mOutlineColor(shape.GetOutlineColor())
, mOutlineThickness(shape.GetOutlineThickness())
, mEdges()
, mTriangleShapes()
, mEdgeShapes()
, mNeedsTriangleUpdate(true)
, mNeedsEdgeUpdate(true)
{
	const unsigned int size = shape.GetPointCount();

	SetPointCount(size);
	for (unsigned int i = 0; i < size; ++i)
		SetPoint(i, shape.GetPoint(i));
}


void ConcaveShape::SetPointCount(unsigned int count)
{
	mPoints.resize(count, Vertex(0.f, 0.f));
}

unsigned int ConcaveShape::GetPointCount() const
{
	return mPoints.size();
}

void ConcaveShape::SetPoint(unsigned int index, sf::Vector2f position)
{
	mPoints[index] = Vertex(position);

	mNeedsTriangleUpdate = true;
	mNeedsEdgeUpdate = true;
}

sf::Vector2f ConcaveShape::GetPoint(unsigned int index) const
{
	return mPoints[index].GetPosition();
}

void ConcaveShape::SetFillColor(const sf::Color& fillColor)
{
	mFillColor = fillColor;
	mNeedsTriangleUpdate = true;
}

sf::Color ConcaveShape::GetFillColor() const
{
	return mFillColor;
}

void ConcaveShape::SetOutlineColor(const sf::Color& outlineColor)
{
	mOutlineColor = outlineColor;
	mNeedsEdgeUpdate = true;
}

sf::Color ConcaveShape::GetOutlineColor() const
{
	return mOutlineColor;
}

void ConcaveShape::SetOutlineThickness(float outlineThickness)
{
	assert(outlineThickness >= 0.f);

	mOutlineThickness = outlineThickness;	
	mNeedsEdgeUpdate = true;
}
		
float ConcaveShape::GetOutlineThickness() const
{
	return mOutlineThickness;
}

void ConcaveShape::Swap(ConcaveShape& other)
{
	using std::swap;

	swap(static_cast<sf::Transformable&>(*this), static_cast<sf::Transformable&>(other));

	swap(mPoints,              other.mPoints);
	swap(mFillColor,           other.mFillColor);
	swap(mOutlineColor,		   other.mOutlineColor);
	swap(mOutlineThickness,    other.mOutlineThickness);
	swap(mEdges,               other.mEdges);
	swap(mTriangleShapes,      other.mTriangleShapes);
	swap(mEdgeShapes,          other.mEdgeShapes);
	swap(mNeedsTriangleUpdate, other.mNeedsTriangleUpdate);
	swap(mNeedsEdgeUpdate,     other.mNeedsEdgeUpdate);
}

void ConcaveShape::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// One or zero points aren't rendered
	if (mPoints.size() <= 1)
		return;
	
	// Batch logics
	if (mNeedsEdgeUpdate || mNeedsTriangleUpdate)
	{		
		if (mNeedsTriangleUpdate)
			Decompose();

		if (mNeedsEdgeUpdate)
			FormOutline();

		mNeedsEdgeUpdate = false;
		mNeedsTriangleUpdate = false;
	}

	// Combine transforms
	states.Transform *= GetTransform();
	
	// Draw all points
	THOR_CONST_FOREACH(ShapeContainer, mTriangleShapes, itr)
		target.Draw(**itr, states);
	
	// Draw all edges at the boundary
	THOR_CONST_FOREACH(ShapeContainer, mEdgeShapes, itr)
		target.Draw(**itr, states);
}

void ConcaveShape::Decompose() const
{
	mEdges.clear();

	// Split the concave polygon into convex triangles that can be represented by sf::ConvexShape
	TriangulatePolygon(mPoints.begin(), mPoints.end(), TriangleGenerator(mTriangleShapes, mFillColor), std::back_inserter(mEdges));
}

void ConcaveShape::FormOutline() const
{
	// If no outline is visible, don't create one
	if (mOutlineThickness == 0.f)
		return;

	// Create graphic edges	
	THOR_CONST_FOREACH(EdgeContainer, mEdges, itr)
	{
		const Vertex& first = (*itr)[0];
		const Vertex& second = (*itr)[1];
		const float radius = mOutlineThickness / 2.f;

		// Insert circles at the polygon points to round the outline off
		sf::CircleShape* circle = new sf::CircleShape();
		circle->SetPosition(first.GetPosition() - sf::Vector2f(radius, radius));
		circle->SetRadius(radius);
		circle->SetFillColor(mOutlineColor);

		// Create lines representing the edges
		sf::ConvexShape line = Shapes::Line(second.GetPosition() - first.GetPosition(), mOutlineColor, mOutlineThickness);
		line.SetPosition(first.GetPosition());

		// Add shapes
		mEdgeShapes.push_back( CopiedPtr<sf::Shape>(circle) );
		mEdgeShapes.push_back( CopiedPtr<sf::Shape>(new sf::ConvexShape(line)) );
	}
}

} // namespace thor
