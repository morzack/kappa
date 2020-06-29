#include "robot.h"

/*** Shooter ***/
Shooter::Shooter(NoU_Motor *motor) : motor(motor)
{
    motor->setInverted(true);
}

void Shooter::shoot(float power)
{
    setPower = power > maxPower ? maxPower : (power < minPower ? minPower : power);
}

void Shooter::execute()
{
    motor->set(setPower);
}

/*** Turret ***/
Turret::Turret(NoU_Motor *motor) : motor(motor){};

void Turret::setDirection(TurretState s)
{
    state = s;
}

void Turret::execute()
{
    switch (state)
    {
    case TurretState::CLOCKWISE:
        motor->set(-turretMovePower);
        break;
    case TurretState::COUNTERCLOCKWISE:
        motor->set(turretMovePower);
        break;
    case TurretState::STOP:
        motor->set(0);
        break;
    default:
        motor->set(0);
        break;
    }
}

/*** Robot ***/
Robot::Robot(Shooter *shooter, Turret *turret, NoU_Drivetrain *drivetrain) : shooter(shooter), turret(turret), drivetrain(drivetrain)
{
    drivetrain->setMaximumOutput(dtMaxPower);
    drivetrain->setInputDeadband(drivetrainDeadband);
    drivetrain->setMinimumOutput(-dtMaxPower);
}

void Robot::moveTurret(TurretState direction)
{
    turret->setDirection(direction);
}

void Robot::shootTurret(float power)
{
    shooter->shoot(power);
}

void Robot::tankDrive(float leftPower, float rightPower)
{
    drivetrain->tankDrive(leftPower, rightPower);
}

void Robot::execute()
{
    shooter->execute();
    turret->execute();
}