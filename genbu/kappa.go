package genbu

import (
	"fmt"
	"net/url"

	"github.com/gorilla/websocket"
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
	defaultHost = "192.168.4.1"
	defaultPort = 8080
)

type Kappa struct {
	connection *websocket.Conn
	baseURL    url.URL

	Connected     bool
	LastTelemetry string
}

func NewKappa(ip string, port int) *Kappa {
	u := url.URL{
		Scheme: "ws",
		Host:   fmt.Sprintf("%s:%d", ip, port),
	}
	return &Kappa{
		baseURL: u,
	}
}

func (k *Kappa) Connect() error {
	if k.Connected {
		return fmt.Errorf("Already connected")
	}
	var err error
	if k.connection, _, err = websocket.DefaultDialer.Dial(k.baseURL.String(), nil); err != nil {
		return err
	}
	k.Connected = true
	return nil
}

func (k *Kappa) Disconnect() error {
	if !k.Connected {
		return fmt.Errorf("Already disconnected")
	}
	if err := k.connection.WriteMessage(websocket.CloseMessage,
		websocket.FormatCloseMessage(websocket.CloseNormalClosure, "")); err != nil {
		return err
	}
	if err := k.connection.Close(); err != nil {
		return err
	}
	k.Connected = false
	return nil
}

func (k *Kappa) ReadMessage() (string, error) {
	msgType, msg, err := k.connection.ReadMessage()
	if err != nil {
		return "", err
	}
	if msgType == websocket.CloseMessage {
		return "disconnected", k.Disconnect()
	} else if msgType == websocket.TextMessage {
		return string(msg), nil
	}
	return "", fmt.Errorf("Unexpected message type")
}

func (k *Kappa) SendCommand(command KappaCommand) error {
	return k.connection.WriteJSON(command)
}

func (k *Kappa) HandleStep(command KappaCommand) string {
	if err := k.SendCommand(command); err != nil {
		fmt.Printf("Error when sending command: %s", err)
	}
	telemetry, err := k.ReadMessage()
	if err != nil {
		fmt.Printf("Error when reading telemetry: %s", err)
	}
	return telemetry
}
