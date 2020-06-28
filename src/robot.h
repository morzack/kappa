#ifndef ROBOT_H_
#define ROBOT_H_

#include <Alfredo_NoU2.h>

struct Shooter
{
public:
    Shooter(NoU_Motor *motor);

    void shoot(float power);

    void execute();

private:
    NoU_Motor *motor;

    float setPower = 0;

    const float maxPower = 1;
    const float minPower = -1;
};

enum TurretState
{
    STOP,
    CLOCKWISE,
    COUNTERCLOCKWISE
};

struct Turret
{
public:
    Turret(NoU_Motor *motor);

    void setDirection(TurretState state);

    void execute();

private:
    NoU_Motor *motor;

    TurretState state = TurretState::STOP;

    const float turretMovePower = .5f;
};

struct Robot
{
public:
    Robot(Shooter *shooter, Turret *turret, NoU_Drivetrain *drivetrain);

    void moveTurret(TurretState direction);
    void shootTurret(float power);

    void tankDrive(float leftPower, float rightPower);

    void execute();

private:
    Shooter *shooter;
    Turret *turret;
    NoU_Drivetrain *drivetrain;

    const float drivetrainDeadband = .05f;
    const float dtMaxPower = .75f;
};

#endif