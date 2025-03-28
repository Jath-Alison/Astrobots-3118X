#pragma once

#include "ART/SimpleMotorGroup.h"
#include "ART/Units.h"
#include "ART/Vec2.h"

namespace art
{
	class HolonomicDrive
	{
	public:
		HolonomicDrive(SimpleMotorGroup leftFront,SimpleMotorGroup leftBack, SimpleMotorGroup rightFront,SimpleMotorGroup rightBack);

		void arcade(double x, double y, double rot);
		
		void LeftSplitArcade(const vex::controller &cont);
		
		void LeftSplitArcadeCurved(const vex::controller &cont);

		void rotateCommand(art::Angle angle);


		void update();
	// protected:

		SimpleMotorGroup m_leftFront;
        SimpleMotorGroup m_leftBack;
		
		SimpleMotorGroup m_rightFront;
        SimpleMotorGroup m_rightBack;
		
		double m_cmdX{0};
		double m_cmdY{0};
		double m_cmdRot{0};
	};
} // namespace art
