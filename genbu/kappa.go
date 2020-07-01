package genbu

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

type turretState string

const (
	turretStop             turretState = "stop"
	turretClockwise        turretState = "clockwise"
	turretCounterclockwise turretState = "counterclockwise"
)

type KappaCommand struct {
	LeftPower  float32     `json:"leftPower"`
	RightPower float32     `json:"rightPower"`
	ShootPower float32     `json:"shootPower"`
	TurretMode turretState `json:"turretMode"`
}

const (
	ip = "192.168.4.1"
)

type Kappa struct {
}

func (k *Kappa) PostData(data []byte, endpoint string) error {
	resp, err := http.Post(fmt.Sprintf("http://%s/%s", ip, endpoint), "application/json", bytes.NewBuffer(data))
	if err != nil {
		return err
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}

	if string(body) != "ok" {
		return fmt.Errorf("%s", body)
	}

	return nil
}

func (k *Kappa) ping() (bool, error) {
	resp, err := http.Get(fmt.Sprintf("http://%s/ping", ip))
	if err != nil {
		return false, err
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return false, err
	}

	return string(body) == "kappa", nil
}

func (k *Kappa) sendCommand(command KappaCommand) error {
	commandData, err := json.Marshal(command)
	if err != nil {
		return err
	}
	return k.PostData(commandData, "command")
}
