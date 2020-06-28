package genbu

import (
	"image/color"

	"github.com/hajimehoshi/ebiten"
)

type Genbu struct {
	slider Slider
}

func NewGenbuInstance() (*Genbu, error) {
	g := &Genbu{}

	if s, err := NewSlider(80, 50, 100); err != nil {
		return nil, err
	} else {
		g.slider = s
	}

	return g, nil
}

func (g *Genbu) Layout(outsideWidth int, outsideHeight int) (int, int) {
	return ScreenWidth, ScreenHeight
}

func (g *Genbu) Update(*ebiten.Image) error {
	g.slider.SetPercent(g.slider.GetPercent() + 1)
	if g.slider.GetPercent() >= 100 {
		g.slider.SetPercent(0)
	}
	return nil
}

func (g *Genbu) Draw(screen *ebiten.Image) {
	screen.Fill(color.White)
	g.slider.Draw(screen)
}
