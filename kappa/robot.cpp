#include "robot.h"

/*** Shooter ***/
Shooter::Shooter(NoU_Motor *motor) : motor(motor) {
    motor->setInverted(true);
}

void Shooter::Shoot(float power) {
    setPower = power > maxPower ? maxPower : (power < minPower ? minPower : power);
}

void Shooter::Execute() {
    motor->set(setPower);
}

/*** Turret ***/
Turret::Turret(NoU_Motor *motor) : motor(motor) {}

void Turret::SetState(TurretState s) {
    state = s;
}

void Turret::Execute() {
    switch (state) {
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
Robot::Robot(Shooter *shooter, Turret *turret, NoU_Drivetrain *drivetrain) :
        shooter(shooter),
        turret(turret),
        drivetrain(drivetrain) {
    drivetrain->setMaximumOutput(dtMaxPower);
    drivetrain->setInputDeadband(drivetrainDeadband);
    drivetrain->setMinimumOutput(-dtMaxPower);
}

void Robot::MoveTurret(TurretState direction) {
    turret->SetState(direction);
}

void Robot::ShootTurret(float power) {
    shooter->Shoot(power);
}

void Robot::TankDrive(float leftPower, float rightPower) {
    drivetrain->tankDrive(leftPower, rightPower);
}

void Robot::Execute() {
    shooter->Execute();
    turret->Execute();
}
