# Try to find and setup Qt4 for this project
FIND_PACKAGE(Qt4)
FIND_PACKAGE(Boost 1.41 COMPONENTS regex)

IF(QT_FOUND)

MESSAGE(STATUS "\tUsing Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH} (${QT_QMAKE_EXECUTABLE})")
MESSAGE(STATUS "\tIncludes in ${QT_INCLUDE_DIR}")

# add Qt modules here, the include will setup QT_LIBRARIES
#
# SET(QT_USE_XXX TRUE)
#
# Possible values are:
# QT_DONT_USE_QTCORE
# QT_DONT_USE_QTGUI
# QT_USE_QT3SUPPORT
# QT_USE_QTASSISTANT
# QT_USE_QAXCONTAINER
# QT_USE_QAXSERVER
# QT_USE_QTDESIGNER
# QT_USE_QTMOTIF
# QT_USE_QTMAIN
# QT_USE_QTNETWORK
# QT_USE_QTNSPLUGIN
# QT_USE_QTOPENGL
# QT_USE_QTSQL
# QT_USE_QTXML
# QT_USE_QTSVG
# QT_USE_QTTEST
# QT_USE_QTUITOOLS
# QT_USE_QTDBUS
# QT_USE_QTSCRIPT
# QT_USE_QTASSISTANTCLIENT
# QT_USE_QTHELP
# QT_USE_QTWEBKIT
# QT_USE_QTXMLPATTERNS
# QT_USE_PHONON

INCLUDE(${QT_USE_FILE})

# Include current directory, necessary for proper UI headers to work
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Source files
SET(GUI_CXX_SRCS
	base/interface.cc	
    base/main.cpp
    base/mainwindow.cpp
    base/menu_bar.cpp
    base/allrobots.cpp
    base/mp.cpp
    base/wgt_base.cpp
   	base/WgtAbsoluteBase.cpp
    base/WgtRelativeBase.cpp
    base/WgtToolBase.cpp
    base/wgt_process_control.cpp
	base/wgt_robot_process_control.cpp
    base/ui_ecp_dialogs/wgt_yes_no.cpp
    base/ui_ecp_dialogs/wgt_message.cpp
    base/ui_ecp_dialogs/wgt_input_integer.cpp
    base/ui_ecp_dialogs/wgt_input_double.cpp
    base/ui_ecp_dialogs/wgt_choose_option.cpp
    base/ui_ecp_dialogs/wgt_teaching.cpp
    spkm/wgt_spkm_inc.cpp
    spkm/wgt_spkm_int.cpp
    spkm/wgt_spkm_ext.cpp
    polycrank/wgt_polycrank_int.cpp
    base/wgt_single_motor_move.cpp
    bird_hand/wgt_bird_hand_command.cpp
    irp6_m/wgt_irp6_m_joints.cpp
    irp6_m/wgt_irp6_m_motors.cpp
    irp6_m/wgt_irp6_m_angle_axis.cpp
    irp6_m/wgt_irp6_m_euler.cpp
    irp6_m/wgt_irp6_m_relative_angle_axis.cpp
    irp6_m/wgt_irp6_m_tool_angle_axis.cpp
    irp6_m/wgt_irp6_m_tool_euler.cpp
)

# Class headers that have to be MOCed (i.e. classes derived from QObject)
SET(GUI_MOC_SRCS
	base/interface.h	
    base/mainwindow.h
    base/wgt_base.h
    base/wgt_process_control.h
	base/wgt_robot_process_control.h
    base/ui_ecp_dialogs/wgt_yes_no.h
    base/ui_ecp_dialogs/wgt_message.h
    base/ui_ecp_dialogs/wgt_input_integer.h
    base/ui_ecp_dialogs/wgt_input_double.h
    base/ui_ecp_dialogs/wgt_choose_option.h
    base/ui_ecp_dialogs/wgt_teaching.h
    base/WgtAbsoluteBase.h
    base/WgtRelativeBase.h
    base/WgtToolBase.h
    spkm/wgt_spkm_inc.h
    spkm/wgt_spkm_int.h
    spkm/wgt_spkm_ext.h
    polycrank/wgt_polycrank_int.h
    base/wgt_single_motor_move.h
    bird_hand/wgt_bird_hand_command.h
    irp6_m/wgt_irp6_m_joints.h
    irp6_m/wgt_irp6_m_motors.h
    irp6_m/wgt_irp6_m_angle_axis.h
    irp6_m/wgt_irp6_m_euler.h
    irp6_m/wgt_irp6_m_relative_angle_axis.h
    irp6_m/wgt_irp6_m_tool_angle_axis.h
    irp6_m/wgt_irp6_m_tool_euler.h
    irp6ot_m/ui_r_irp6ot_m.h
	irp6ot_tfg/ui_r_irp6ot_tfg.h
	irp6p_m/ui_r_irp6p_m.h
	irp6p_tfg/ui_r_irp6p_tfg.h
	polycrank/ui_r_polycrank.h
	base/signal_dispatcher.h
	base/menu_bar.h
	base/menu_bar_action.h
	bird_hand/ui_r_bird_hand.h
	spkm/ui_r_spkm.h
	spkm/ui_r_spkm1.h
	spkm/ui_r_spkm2.h
	smb/ui_r_smb.h
	smb/ui_r_smb1.h
	smb/ui_r_smb2.h
	shead/ui_r_shead.h
	shead/ui_r_shead1.h
	shead/ui_r_shead2.h
	sbench/ui_r_sbench.h
	sarkofag/ui_r_sarkofag.h
	conveyor/ui_r_conveyor.h
	base/ui_robot.h
)

# Generate MOC files
QT4_WRAP_CPP(GUI_CXX_SRCS ${GUI_MOC_SRCS})

# UI files
SET(GUI_UI
    base/mainwindow.ui
    base/wgt_process_control.ui
    base/wgt_robot_process_control.ui
    base/ui_ecp_dialogs/wgt_yes_no.ui
    base/ui_ecp_dialogs/wgt_message.ui
    base/ui_ecp_dialogs/wgt_input_integer.ui
    base/ui_ecp_dialogs/wgt_input_double.ui
    base/ui_ecp_dialogs/wgt_choose_option.ui
    base/ui_ecp_dialogs/wgt_teaching.ui
    spkm/wgt_spkm_inc.ui
    spkm/wgt_spkm_int.ui
    spkm/wgt_spkm_ext.ui
    polycrank/wgt_polycrank_int.ui
    base/wgt_single_motor_move.ui
    bird_hand/wgt_bird_hand_command.ui
    base/wgt_absolute_template.ui
    base/wgt_relative_template.ui
    base/wgt_tool_template.ui
    irp6_m/wgt_irp6_m_angle_axis.ui
    irp6_m/wgt_irp6_m_euler.ui
    irp6_m/wgt_irp6_m_relative_angle_axis.ui
    irp6_m/wgt_irp6_m_tool_angle_axis.ui
    irp6_m/wgt_irp6_m_tool_euler.ui
)

# Generate UI include files
QT4_WRAP_UI(GUI_CXX_SRCS ${GUI_UI})

# Create GUI executable
ADD_EXECUTABLE(
	ui-qt
	${GUI_CXX_SRCS}
	base/menu_bar.cpp
	base/allrobots.cpp
	base/mp.cpp
	base/menu_bar_action.cpp
	base/ui_sr.cc
	base/ui_ecp.cc
	base/ui_ecp_robot/ui_ecp_r_common.cc
	irp6ot_m/ui_r_irp6ot_m.cc
	irp6p_m/ui_r_irp6p_m.cc
	irp6_m/ui_r_irp6_m.cc
	irp6p_tfg/ui_r_irp6p_tfg.cc
	irp6ot_tfg/ui_r_irp6ot_tfg.cc
	bird_hand/ui_ecp_r_bird_hand.cc
	bird_hand/ui_r_bird_hand.cc
	sarkofag/ui_r_sarkofag.cc
	conveyor/ui_r_conveyor.cc
	spkm/ui_ecp_r_spkm.cc
	spkm/ui_ecp_r_spkm1.cc
	spkm/ui_ecp_r_spkm2.cc
	spkm/ui_r_spkm.cc
	spkm/ui_r_spkm1.cc
	spkm/ui_r_spkm2.cc
	smb/ui_ecp_r_smb.cc
	smb/ui_ecp_r_smb1.cc
	smb/ui_ecp_r_smb2.cc
	smb/ui_r_smb.cc
	smb/ui_r_smb1.cc
	smb/ui_r_smb2.cc
	shead/ui_ecp_r_shead.cc
	shead/ui_ecp_r_shead1.cc
	shead/ui_ecp_r_shead2.cc
	shead/ui_r_shead.cc
	shead/ui_r_shead1.cc
	shead/ui_r_shead2.cc
	sbench/ui_ecp_r_sbench.cc
	sbench/ui_r_sbench.cc
	polycrank/ui_r_polycrank.cc
	base/ui.cc
	base/ui_robot.cc
	base/ui_r_single_motor.cc
	base/signal_dispatcher.cpp
)

# Link executable with QT libraries
TARGET_LINK_LIBRARIES(
	ui-qt
	ecp_robot
	${QT_LIBRARIES}
	${COMMON_LIBRARIES}
    ${Boost_REGEX_LIBRARY}
)

install(
  TARGETS ui-qt
  RUNTIME DESTINATION bin COMPONENT applications
)

install(PROGRAMS start.sh DESTINATION bin/ )

ELSE(QT_FOUND)

    MESSAGE("Qt not found! GUI will not be built")

ENDIF(QT_FOUND)
