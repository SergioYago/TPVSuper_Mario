#pragma once
#include "pickable.h"
class coin : public pickable
{
public:
	coin(Game* g, Point2D pos, int w, int h, bool p);
	void triggerAction() override;
	void render() const override;
	void update() override;
	~coin();
};

