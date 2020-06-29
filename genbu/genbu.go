package genbu

import (
	"image/color"
	"log"

	"github.com/hajimehoshi/ebiten"
)

type Genbu struct {
	leftPower  Slider
	rightPower Slider

	shoot Button

	input *Input

	kappa *Kappa
}

func NewGenbuInstance() (*Genbu, error) {
	g := &Genbu{
		input: NewInput(),
		kappa: &Kappa{
			ip: "192.168.4.1",
		},
	}

	var err error
	if g.leftPower, err = NewSlider(10, 10, 60); err != nil {
		return nil, err
	}
	if g.rightPower, err = NewSlider(70, 10, 60); err != nil {
		return nil, err
	}

	g.shoot = NewButton(50-15/2, 80, 15)

	// if _, err := g.kappa.ping(); err != nil {
	// 	return nil, err
	// }

	return g, nil
}

func (g *Genbu) Layout(outsideWidth int, outsideHeight int) (int, int) {
	return ScreenWidth, ScreenHeight
}

func (g *Genbu) Update(*ebiten.Image) error {
	g.input.Update()
	g.leftPower.Update(g.input)
	g.rightPower.Update(g.input)
	g.shoot.Update(g.input)

	var shootingPower float32
	if g.shoot.pressed {
		shootingPower = 1
	} else {
		shootingPower = 0
	}

	command := KappaCommand{
		LeftPower:  g.leftPower.GetPercentFloatOffset(),
		RightPower: g.leftPower.GetPercentFloatOffset(),
		ShootPower: shootingPower,
		TurretMode: turretStop,
	}
	if err := g.kappa.sendCommand(command); err != nil {
		log.Printf("packet err: %s", err.Error())
	}

	return nil
}

func (g *Genbu) Draw(screen *ebiten.Image) {
	screen.Fill(color.White)
	g.leftPower.Draw(screen)
	g.rightPower.Draw(screen)
	g.shoot.Draw(screen)
}
