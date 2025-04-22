#include "Ragdoll.h"
#include "Box2DHelper.h"


Ragdoll::Ragdoll(b2World* world, const b2Vec2& position)
{
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.2f;

	headBody = Box2DHelper::CreateRectangularDynamicBody(world, 2.5f, 2.5f, density, friction, restitution);
	headBody->SetTransform(b2Vec2(25.0f, 30.0f), 0.0f);

	torsoBody = Box2DHelper::CreateRectangularDynamicBody(world, 5, 10, density, friction, restitution);
	torsoBody->SetTransform(b2Vec2(25.0f, 35.0f), 0.0f);

	//leftArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	//leftArmBody->SetTransform(b2Vec2(22.5f, 35.0f), 0.0f);

	//rightArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	//rightArmBody->SetTransform(b2Vec2(27.5f, 35.0f), 0.0f);

	//leftLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	//leftLegBody->SetTransform(b2Vec2(24.0f, 44.0f), 0.0f);

	//rightLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 2, 15, density, friction, restitution);
	//rightLegBody->SetTransform(b2Vec2(24.0f, 44.0f), 0.0f);


	//Cabeza y torso
	b2Vec2 headAnchor(25.0f, 31.0f);
	b2Vec2 centerAnchor(25.0f, 30.0f);
	b2DistanceJoint* headJoint = Box2DHelper::CreateDistanceJoint(world, headBody, headAnchor, torsoBody, centerAnchor, 0, 0.5f, 0.2f);

	/*
	//Brazo izquierdo y torso
	b2Vec2 centerAnchorLA(23.0f, 31.0f);
	b2Vec2 leftArmAnchor(22.5f, 32.0f);
	b2DistanceJoint* leftArmJoint = Box2DHelper::CreateDistanceJoint(world, leftArmBody, leftArmAnchor, torsoBody, centerAnchorLA, 1, 0.5f, 0.2f);

	//Brazo derecho y torso
	b2Vec2 centerAnchorRA(26.5f, 31.0f);
	b2Vec2 rightArmAnchor(27.7f, 32.0f);
	b2DistanceJoint* rightArmJoint = Box2DHelper::CreateDistanceJoint(world, rightArmBody, rightArmAnchor, torsoBody, centerAnchorRA, 1, 0.8f, 0.1f);

	//Pierna izquierda y torso
	b2Vec2 centerAnchorLL(24.0f, 39.5f);
	b2Vec2 leftLegAnchor(25.0f, 41.25f);
	float leftLegLength = b2Distance(centerAnchorLL, leftLegAnchor) * 0.7f;
	b2DistanceJoint* leftLegJoint = Box2DHelper::CreateDistanceJoint(world, leftLegBody, leftLegAnchor, torsoBody, centerAnchorLL, leftLegLength, 0.5f, 0.2f);

	//Pierna derecha y torso
	b2Vec2 centerAnchorRL(26.0f, 39.5f);
	b2Vec2 rightLegAnchor(26.0f, 41.25f);
	float rightLegLength = b2Distance(centerAnchorRL, rightLegAnchor) * 0.7f;
	b2DistanceJoint* rightLegJoint = Box2DHelper::CreateDistanceJoint(world, rightLegBody, rightLegAnchor, torsoBody, centerAnchorRL, rightLegLength, 0.5f, 0.2f);
	*/
}

b2Body* Ragdoll::GetTorso() const
{
	return torsoBody;
}