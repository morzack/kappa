package genbu

import (
	"image/color"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

type Genbu struct {
	Input *Input
	Kappa *Kappa

	leftPower  Slider
	rightPower Slider
	shoot      Button
}

func NewGenbuInstance() (*Genbu, error) {
	g := &Genbu{
		Input: NewInput(),
		Kappa: NewKappa(defaultHost, defaultPort),
	}

	var err error
	if g.leftPower, err = NewSlider(10, 10, 60); err != nil {
		return nil, err
	}
	if g.rightPower, err = NewSlider(70, 10, 60); err != nil {
		return nil, err
	}
	g.shoot = NewButton(50-15/2, 80, 15)

	if err := g.Kappa.Connect(); err != nil {
		return nil, err
	}

	return g, nil
}

func (g *Genbu) Layout(outsideWidth int, outsideHeight int) (int, int) {
	return ScreenWidth, ScreenHeight
}

func (g *Genbu) Update(*ebiten.Image) error {
	/** UPDATE COMPONENTS **/
	g.Input.Update()
	g.leftPower.Update(g.Input)
	g.rightPower.Update(g.Input)
	g.shoot.Update(g.Input)

	/** HANDLE INPUT **/
	var shootingPower float32
	if g.shoot.pressed {
		shootingPower = 1
	} else {
		shootingPower = 0
	}

	/** DO NETWORKING **/
	command := KappaCommand{
		LeftPower:  g.leftPower.GetPercentFloatOffset(),
		RightPower: g.leftPower.GetPercentFloatOffset(),
		ShootPower: shootingPower,
		TurretMode: turretStop,
	}
	g.Kappa.HandleStep(command)

	return nil
}

func (g *Genbu) Draw(screen *ebiten.Image) {
	screen.Fill(color.White)

	g.leftPower.Draw(screen)
	g.rightPower.Draw(screen)
	g.shoot.Draw(screen)

	ebitenutil.DebugPrint(screen, g.Kappa.LastTelemetry)
}
