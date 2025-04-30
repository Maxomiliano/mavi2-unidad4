#include "Ragdoll.h"
#include "Box2DHelper.h"


Ragdoll::Ragdoll(b2World* world, const b2Vec2& position, float scale)
{
	float density = 100.0f;
	float friction = 0.1f;
	float restitution = 0.1f;

	b2Vec2 torsoOffset(0.0f, 0.0f);
	b2Vec2 headOffset(0.0f, -5.0f * scale);
	b2Vec2 leftArmOffset(-2.5f * scale, 0.0f);
	b2Vec2 rightArmOffset(2.5f * scale, 0.0f);
	b2Vec2 leftLegOffset(-1.5f * scale, 5.0f * scale);
	b2Vec2 rightLegOffset(1.5f * scale, 5.0f * scale);

	headBody = Box2DHelper::CreateRectangularDynamicBody(world, 2.5f * scale, 2.5f * scale, density, friction, restitution);
	headBody->SetTransform(position + headOffset, 0.0f);

	torsoBody = Box2DHelper::CreateRectangularDynamicBody(world, 4 * scale, 9 * scale, density, friction, restitution);
	torsoBody->SetTransform(position + torsoOffset, 0.0f);

	leftArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 6 * scale, density, friction, restitution);
	leftArmBody->SetTransform(position + leftArmOffset, 0.0f);

	rightArmBody = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 6 * scale, density, friction, restitution);
	rightArmBody->SetTransform(position + rightArmOffset, 0.0f);

	leftLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 6 * scale, density, friction, restitution);
	leftLegBody->SetTransform(position + leftLegOffset, 0.0f);

	rightLegBody = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 6 * scale, density, friction, restitution);
	rightLegBody->SetTransform(position + rightLegOffset, 0.0f);


	//Cabeza y torso
	b2Vec2 headAnchor = position + headOffset + b2Vec2(0.0f, 1.0f * scale);
	b2Vec2 centerAnchor = position + torsoOffset + b2Vec2(0.0f, -4.0f * scale);
	b2DistanceJoint* headJoint = Box2DHelper::CreateDistanceJoint(world, headBody, headAnchor, torsoBody, centerAnchor, 0, 0.5f, 0.2f);

	
	//Brazo izquierdo y torso
	b2Vec2 centerAnchorLA = position + torsoOffset + b2Vec2(-2.0f * scale, -4.0f * scale);
	b2Vec2 leftArmAnchor = position + leftArmOffset + b2Vec2(0.0f, -3.0f * scale);
	b2DistanceJoint* leftArmJoint = Box2DHelper::CreateDistanceJoint(world, leftArmBody, leftArmAnchor, torsoBody, centerAnchorLA, 1, 0.5f, 0.2f);

	//Brazo derecho y torso
	b2Vec2 centerAnchorRA = position + torsoOffset + b2Vec2(2.0f * scale, -4.0f * scale);
	b2Vec2 rightArmAnchor = position + rightArmOffset + b2Vec2(0.0f, -3.0f * scale);
	b2DistanceJoint* rightArmJoint = Box2DHelper::CreateDistanceJoint(world, rightArmBody, rightArmAnchor, torsoBody, centerAnchorRA, 1, 0.8f, 0.1f);

	//Pierna izquierda y torso
	b2Vec2 centerAnchorLL = position + torsoOffset + b2Vec2(-1.0f * scale, 4.0f * scale);
	b2Vec2 leftLegAnchor = position + leftLegOffset + b2Vec2(0.0f, -3.0f * scale);
	b2DistanceJoint* leftLegJoint = Box2DHelper::CreateDistanceJoint(world, leftLegBody, leftLegAnchor, torsoBody, centerAnchorLL, 1, 0.5f, 0.2f);

	//Pierna derecha y torso
	b2Vec2 centerAnchorRL = position + torsoOffset + b2Vec2(1.0f * scale, 4.0f * scale);
	b2Vec2 rightLegAnchor = position + rightLegOffset + b2Vec2(0.0f, -3.0f * scale);
	b2DistanceJoint* rightLegJoint = Box2DHelper::CreateDistanceJoint(world, rightLegBody, rightLegAnchor, torsoBody, centerAnchorRL, 1, 0.5f, 0.2f);
	/*
	*/
}

b2Body* Ragdoll::GetTorso() const
{
	return torsoBody;
}