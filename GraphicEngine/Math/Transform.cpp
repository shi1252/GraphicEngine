#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Translate(Vector3 pos)
{
	position = pos;
}

void Transform::Translate(Vector3 dir, float distance)
{
	position += dir * distance;
}

void Transform::Rotate(Vector3 rot)
{
	rotation += rot;
}