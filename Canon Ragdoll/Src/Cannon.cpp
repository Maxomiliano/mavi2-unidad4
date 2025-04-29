#include "Cannon.h"
#include "Box2DHelper.h"

Cannon::Cannon(b2World* world, const b2Vec2& position)
{
	cannonBody = Box2DHelper::CreateRectangularStaticBody(world, 25, 5);
	cannonBody->SetTransform(position, 0.0f);
}

void Cannon::Rotate(b2Vec2 mousePos)
{

}

b2Body* Cannon::GetCannon() const
{
	return cannonBody;
}