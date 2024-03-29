/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/TankDriveSubsystem.h"
#include "T34_XboxController.h"
#include "Robot.h"
#include "RobotMap.h"

#include <iostream>

#include <ntcore_cpp.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() 
{
    m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    m_tank_drive = TankDriveSubsystem::GetInstance();
    m_driver_controller.reset(new T34_XboxController(RobotMap::DRIVER1_JOYSTICK_PORT));

    m_driver_controller->SetAxisDeadband(
        frc::GenericHID::JoystickHand::kLeftHand, 
        AxisType::YAxis, 
        0.06);

    m_driver_controller->SetAxisDeadband(
        frc::GenericHID::JoystickHand::kRightHand, 
        AxisType::YAxis, 
        0.06);
    
    //NT_Inst inst = NT_GetDefaultInstance();
    //NT_AddEntryListener(inst, "", 0, &m_chooser, ScriptUpdater, NT_NOTIFY_NEW | NT_NOTIFY_UPDATE);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() 
{
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString(
    //     "Auto Selector", kAutoNameDefault);
    std::cout << "Auto selected: " << m_autoSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom) 
    {
        // Custom Auto goes here
    } 
    else 
    {
        // Default Auto goes here
    }
}

void Robot::AutonomousPeriodic() 
{
    if (m_autoSelected == kAutoNameCustom) 
    {
        // Custom Auto goes here
    } 
    else    
    {
        // Default Auto goes here
    }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
    double left = m_driver_controller->GetYDB(frc::GenericHID::JoystickHand::kLeftHand);
    double right = m_driver_controller->GetYDB(frc::GenericHID::JoystickHand::kRightHand);
    frc::SmartDashboard::PutNumber("Left Joy", left);
    frc::SmartDashboard::PutNumber("Right Joy", right);
    m_tank_drive->SetMotorOutputByPercentage(left, right);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
