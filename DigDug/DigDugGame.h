#pragma once
#include "Minigin.h"

class DigDugGame : public dae::Minigin
{
public:
	virtual ~DigDugGame() = default;

	virtual void LoadGame() const override;
};
