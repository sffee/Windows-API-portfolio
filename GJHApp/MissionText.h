#pragma once
#include "ObjectBase.h"

class MissionText : public ObjectBase
{
private:
	void Start() override;
	void Update() override;

public:
	void SetText(const GJHString& _Text);

public:
	int AccelMove(const GJHVector& _TargetPos);
	void Move(float _Angle);
};