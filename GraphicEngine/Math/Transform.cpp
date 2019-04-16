#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const Transform & t)
{
	position = t.position;
	rotation = t.rotation;
	scale = t.scale;
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
	rotation = Vector3::RotateClamp(rotation + rot);
}

Matrix4x4 Transform::GetMatrix()
{
	return Matrix4x4::TRSMatrix(position, rotation, scale);
}