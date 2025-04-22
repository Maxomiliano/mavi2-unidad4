#include "Ragdoll.h"
#include "Box2DHelper.h"


Ragdoll::Ragdoll(b2World* world, const b2Vec2& position)
{
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.2f;

	headBody = Box2DHelper::CreateRectangularDynamicBody(world, 5, 5, density, friction, restitution);
	headBody->SetTransform(b2Vec2(50.0f, 60.0f), 0.0f);

	torsoBody = Box2DHelper::CreateRectangularDynamicBody(world, 10, 20, density, friction, restitution);
	torsoBody->SetTransform(b2Vec2(50.0f, 70.0f), 0.0f);

	leftArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	leftArmBody->SetTransform(b2Vec2(45.0f, 70.0f), 0.0f);

	rightArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	rightArmBody->SetTransform(b2Vec2(55.0f, 70.0f), 0.0f);

	leftLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	leftLegBody->SetTransform(b2Vec2(48.0f, 88.5f), 0.0f);

	rightLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	rightLegBody->SetTransform(b2Vec2(52.0f, 88.5f), 0.0f);


	//Cabeza y torso
	b2Vec2 headAnchor(50.0f, 62.0f);
	b2Vec2 centerAnchor(50.0f, 60.0f);
	b2DistanceJoint* headJoint = Box2DHelper::CreateDistanceJoint(world, headBody, headAnchor, torsoBody, centerAnchor, 0, 0.5f, 0.2f);

	//Brazo izquierdo y torso
	b2Vec2 centerAnchorLA(46.0f, 62.0f);
	b2Vec2 leftArmAnchor(45.0f, 64.0f);
	b2DistanceJoint* leftArmJoint = Box2DHelper::CreateDistanceJoint(world, leftArmBody, leftArmAnchor, torsoBody, centerAnchorLA, 1, 0.5f, 0.2f);

	//Brazo derecho y torso
	b2Vec2 centerAnchorRA(53.0f, 62.0f);
	b2Vec2 rightArmAnchor(55.0f, 64.0f);
	b2DistanceJoint* rightArmJoint = Box2DHelper::CreateDistanceJoint(world, rightArmBody, rightArmAnchor, torsoBody, centerAnchorRA, 1, 0.8f, 0.1f);

	//Pierna izquierda y torso
	b2Vec2 centerAnchorLL(48.0f, 79.0f);
	b2Vec2 leftLegAnchor(48.0f, 82.5f);
	float leftLegLength = b2Distance(centerAnchorLL, leftLegAnchor) * 0.7f;
	b2DistanceJoint* leftLegJoint = Box2DHelper::CreateDistanceJoint(world, leftLegBody, leftLegAnchor, torsoBody, centerAnchorLL, leftLegLength, 0.5f, 0.2f);

	//Pierna derecha y torso
	b2Vec2 centerAnchorRL(52.0f, 79.0f);
	b2Vec2 rightLegAnchor(52.0f, 82.5f);
	float rightLegLength = b2Distance(centerAnchorRL, rightLegAnchor) * 0.7f;
	b2DistanceJoint* rightLegJoint = Box2DHelper::CreateDistanceJoint(world, rightLegBody, rightLegAnchor, torsoBody, centerAnchorRL, rightLegLength, 0.5f, 0.2f);
}

b2Body* Ragdoll::GetTorso() const
{
	return torsoBody;
}