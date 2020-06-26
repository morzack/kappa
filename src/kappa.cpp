#include <Arduino.h>

#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

BluetoothSerial bluetooth;

NoU_Motor shooterMotor(1);
NoU_Motor turretMotor(2);

float shooterPower, turretPower;
long lastTimePacketReceived = 0;

void setup() {
    Serial.begin(9600);
    RSL::initialize();
    bluetooth.begin("DefaultBot");
}

void loop() {
    while (bluetooth.available() > 0) {
        lastTimePacketReceived = millis();
        if ((bluetooth.read()) == 'z') {
            shooterPower = bluetooth.parseFloat();
            turretPower = bluetooth.parseFloat();
        }
    }
    shooterMotor.set(shooterPower * .675);
    turretMotor.set(turretPower * .625);

    // RSL logic
    if (millis() - lastTimePacketReceived > 1000) {
        RSL::setState(RSL_DISABLED);
    }
    else {
        RSL::setState(RSL_ENABLED);
    }
    RSL::update();
}