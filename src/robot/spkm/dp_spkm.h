#if !defined(__SPKM_DATA_PORT_H)
#define __SPKM_DATA_PORT_H

/*!
 * @file
 * @brief File contains data port communication structures for SwarmItFix Parallel Kinematic Machine
 * @author twiniars <twiniars@ia.pw.edu.pl>, Warsaw University of Technology
 *
 * @ingroup spkm
 */

#include "robot/epos/dp_epos.h"

namespace mrrocpp {
namespace lib {
namespace spkm {

/*!
 * @brief SwarmItFix Parallel Kinematic Machine mp to ecp command
 * @ingroup spkm
 */
struct mp_to_ecp_parameters
{
	//! The goal pose of the manipulator
	lib::frame_tab goal_pose;

	//! Interpolation type for the motion
	lib::epos::EPOS_MOTION_VARIANT motion_type;

	//! Allowed time for the motion in seconds.
	//! If 0, then the time will be limited by the motor limits.
	//! If > 0 and greater than a limit imposed by the motors, then the motion will be slowed down.
	//! In another case, the NACK will be replied.
	double duration;

	//! True if the contact is expected during the motion.
	//! The NACK will be replied if:
	//! - the contact was expected and did not happend
	//! - OR the contact was NOT expected and did happend.
	bool guarded_motion;
};

} // namespace spkm
} // namespace lib
} // namespace mrrocpp

#endif
