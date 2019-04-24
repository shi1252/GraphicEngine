#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const Transform & t)
{
	position = t.position;
	rotation = t.rotation;
	scale = t.scale;
	matrix = t.matrix;
	invMatrix = t.invMatrix;
}

Transform::~Transform()
{
}

void Transform::Translate(Vector3 pos)
{
	position = pos;
	ValueChanged();
}

void Transform::Translate(Vector3 dir, float distance)
{
	position += dir * distance;
	ValueChanged();
}

void Transform::Rotate(Vector3 rot)
{
	rotation = Vector3::RotateClamp(rotation + rot);
	ValueChanged();
}

Matrix4x4 Transform::GetMatrix()
{
	return matrix;
}

Matrix4x4 Transform::GetInverseMatrix()
{
	return invMatrix;
}

void Transform::ValueChanged()
{
	matrix = Matrix4x4::TRSMatrix(position, rotation, scale);
}