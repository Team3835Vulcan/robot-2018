#pragma once

/*
Fits two new trajectories for a tank drive robot
*/

#include "IFitter.h"
#include <memory>

class TankFitter :
	public IFitter {
private:
	double m_wheelbase;

	//WARNING: THIS CLASS DOES NOT TAKE OWNERSHIP
	//OVER THE CREATED TRAJECTORIES. 	
	//IT IS YOUR RESPONISIBILITY TO DELETE THEM.
	Trajectory* m_left;
	Trajectory* m_right;

public:
	TankFitter(double wheelbase);

	void Fit(const Trajectory& traj) override;

	const Trajectory& GetLeft() const;
	const Trajectory& GetRight() const;
};

