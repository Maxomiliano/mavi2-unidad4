#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Cannon.h"

using namespace sf;

class Cannon
{
private:
	b2Body* cannonBody;
	Vector2f cannonPos;
	float angle;

public: 
	Cannon(b2World* world, const b2Vec2& position);
	void Rotate(b2Vec2 mousePos);
	b2Body* GetCannon() const;
};

