#ifndef ROBOT_H_
#define ROBOT_H_

#include <Alfredo_NoU2.h>

struct Shooter {
public:
    Shooter(NoU_Motor *motor);

    void Shoot(float power);

    void Execute();

private:
    NoU_Motor *motor;

    float setPower = 0;

    const float maxPower = 1;
    const float minPower = -1;
};

enum TurretState {
    STOP,
    CLOCKWISE,
    COUNTERCLOCKWISE
};

struct Turret {
public:
    Turret(NoU_Motor *motor);

    void SetState(TurretState state);

    void Execute();

private:
    NoU_Motor *motor;

    TurretState state = TurretState::STOP;

    const float turretMovePower = .5f;
};

struct Robot {
public:
    Robot(Shooter *shooter, Turret *turret, NoU_Drivetrain *drivetrain);

    void MoveTurret(TurretState direction);
    void ShootTurret(float power);

    void TankDrive(float leftPower, float rightPower);

    void Execute();

private:
    Shooter *shooter;
    Turret *turret;
    NoU_Drivetrain *drivetrain;

    const float drivetrainDeadband = .05f;
    const float dtMaxPower = .75f;
};

#endif
