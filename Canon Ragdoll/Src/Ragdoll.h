#pragma once
#include <Box2D/Box2D.h>
#include "Ragdoll.h"

class Ragdoll
{
public:
	Ragdoll(b2World* world, const b2Vec2& position, float scale);

	b2Body* GetTorso() const;

private:
	b2Body* headBody;
	b2Body* torsoBody;
	b2Body* leftArmBody;
	b2Body* rightArmBody;
	b2Body* leftLegBody;
	b2Body* rightLegBody;
};

