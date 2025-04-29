#include "Cannon.h"
#include "Box2DHelper.h"

Cannon::Cannon()
{
	
}

void Cannon::PlaceCannon(b2World* world, const b2Vec2& position)
{
	cannonBody = Box2DHelper::CreateRectangularStaticBody(world, 25, 5);
	float angle = b2_pi / 1.5f;
	cannonBody->SetTransform(b2Vec2(10.0f, 90.0f), angle);
}

void Cannon::Rotate(b2Vec2 mousePos)
{

}