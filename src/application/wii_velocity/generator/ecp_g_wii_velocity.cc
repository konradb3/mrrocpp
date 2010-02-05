#include "application/wii_velocity/generator/ecp_g_wii_velocity.h"

#include "lib/impconst.h"
#include "lib/com_buf.h"
#include "math.h"

namespace mrrocpp {
namespace ecp {
namespace irp6ot {
namespace generator {

wii_velocity::wii_velocity (common::task::task& _ecp_task) : common::generator::tff_nose_run(_ecp_task,10)
{
	configure_behaviour(lib::UNGUARDED_MOTION, lib::UNGUARDED_MOTION, lib::UNGUARDED_MOTION, lib::UNGUARDED_MOTION, lib::UNGUARDED_MOTION, lib::UNGUARDED_MOTION);
}

bool wii_velocity::first_step()
{
	td.interpolation_node_no = 1;
	td.internode_step_no = step_no;
	td.value_in_step_no = td.internode_step_no - 3;

	lib::Homog_matrix tool_frame(0.0, 0.0, 0.25);
	tool_frame.get_frame_tab(the_robot->ecp_command.instruction.rmodel.tool_frame_def.tool_frame);

	the_robot->ecp_command.instruction.instruction_type = lib::GET;
	the_robot->ecp_command.instruction.get_type = ARM_DEFINITION; // arm - ORYGINAL
	the_robot->ecp_command.instruction.set_type = ARM_DEFINITION | RMODEL_DV;
	the_robot->ecp_command.instruction.set_rmodel_type = lib::TOOL_FRAME;
	the_robot->ecp_command.instruction.get_rmodel_type = lib::TOOL_FRAME;
	the_robot->ecp_command.instruction.set_arm_type = lib::PF_VELOCITY;
	the_robot->ecp_command.instruction.get_arm_type = lib::JOINT;
	the_robot->ecp_command.instruction.motion_type = lib::RELATIVE;
	the_robot->ecp_command.instruction.interpolation_type = lib::TCIM;
	the_robot->ecp_command.instruction.motion_steps = td.internode_step_no;
	the_robot->ecp_command.instruction.value_in_step_no = td.value_in_step_no;

	for (int i=0; i<6; i++)
	{
		 the_robot->ecp_command.instruction.arm.pf_def.behaviour[i] = generator_edp_data.next_behaviour[i];
		 the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[i] = generator_edp_data.next_velocity[i];
		 the_robot->ecp_command.instruction.arm.pf_def.force_xyz_torque_xyz[i] = generator_edp_data.next_force_xyz_torque_xyz[i];
		 the_robot->ecp_command.instruction.arm.pf_def.reciprocal_damping[i] = generator_edp_data.next_reciprocal_damping[i];
		 the_robot->ecp_command.instruction.arm.pf_def.inertia[i] = generator_edp_data.next_inertia[i];
	}
	return true;
}

bool wii_velocity::next_step()
{
	char buffer[200];
	int operate = 0;

	sensor_m[lib::SENSOR_WIIMOTE]->get_reading();

	if (pulse_check_activated && check_and_null_trigger())
	{
		return false;
	}

	// Przygotowanie kroku ruchu - do kolejnego wezla interpolacji
	the_robot->ecp_command.instruction.instruction_type = lib::SET_GET;

	operate = (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.up || (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right || (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.down || (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.left;

	if(operate)
	{
		//wyznaczenie nowych wartosci predkosci
		configure_velocity(
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.up && !(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_0 : 0,
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right && !(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.up && !(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.down ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_1 :	 0,
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.down && !(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_2 : 0,
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.left ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_3 : 0,
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.up && (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_4 : 0,
			(int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.down && (int)sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.right ? sensor_m[lib::SENSOR_WIIMOTE]->image.sensor_union.wiimote.orientation_y * C_5 : 0
		);
	}
	else
	{
		configure_velocity(0,0,0,0,0,0);
	}

	for (int i=0; i<6; i++)
	{
		 the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[i] = generator_edp_data.next_velocity[i];
	}

	//sprintf(buffer,"P%d %f %f %f %f %f %f",step_no,the_robot->reply_package.arm.pf_def.arm_coordinates[0],the_robot->reply_package.arm.pf_def.arm_coordinates[1],the_robot->reply_package.arm.pf_def.arm_coordinates[2],the_robot->reply_package.arm.pf_def.arm_coordinates[3],the_robot->reply_package.arm.pf_def.arm_coordinates[4],the_robot->reply_package.arm.pf_def.arm_coordinates[5]);
	//sprintf(buffer,"V%d %f %f %f %f	 %f %f",step_no,the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[0],the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[1],the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[2],the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[3],the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[4],the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[5]);
	//sr_ecp_msg.message(buffer);

	// Obliczenie zadanej pozycji posredniej w tym kroku ruchu
	if (node_counter==1)
	{
		the_robot->ecp_command.instruction.arm.pf_def.gripper_coordinate
				= the_robot->reply_package.arm.pf_def.gripper_coordinate;
	}

	return true;
}

}
} // namespace irp6ot
} // namespace ecp
} // namespace mrrocpp

