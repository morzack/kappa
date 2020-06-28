package genbu

import (
	"image/color"
	"math"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

type Slider struct {
	x int
	y int

	pxHeight  int
	sliderPos int

	image *ebiten.Image
}

const (
	sliderFilePath = "genbu/assets/slider.png"

	sliderSpriteWidth  = 16
	sliderSpriteHeight = 16

	sliderSpriteScale = 2
)

func NewSlider(x int, y int, pxHeight int) (Slider, error) {
	img, _, err := ebitenutil.NewImageFromFile(sliderFilePath, ebiten.FilterDefault)
	if err != nil {
		return Slider{}, err
	}

	s := Slider{
		x:        x,
		y:        y,
		pxHeight: pxHeight,
		image:    img,
	}

	return s, nil
}

func (s *Slider) Draw(screen *ebiten.Image) {
	// to whatever poor soul has to debug this in the future:
	// i'm sorry for all the magic here. it's pretty much
	// hardcoded to work with the sprites I initially made

	// top and bottom
	DrawImage(s.image, screen, s.x, s.y+s.pxHeight-sliderSpriteScale, sliderSpriteScale, 16*2, 0, sliderSpriteWidth, sliderSpriteHeight)
	DrawImage(s.image, screen, s.x, s.y+sliderSpriteScale, sliderSpriteScale, 16*3, 0, sliderSpriteWidth, sliderSpriteHeight)
	// sidelines
	ebitenutil.DrawRect(screen, float64(s.x+1*sliderSpriteScale), float64(s.y), float64(sliderSpriteScale), float64(s.pxHeight+sliderSpriteScale*8), color.Black)
	ebitenutil.DrawRect(screen, float64(s.x+6*sliderSpriteScale), float64(s.y), float64(sliderSpriteScale), float64(s.pxHeight+sliderSpriteScale*8), color.Black)
	// slider component
	DrawImage(s.image, screen, s.x, s.y+s.pxHeight-s.sliderPos, sliderSpriteScale, 16*0, 0, sliderSpriteWidth, sliderSpriteHeight)
}

func (s *Slider) SetPercent(percent int) {
	s.sliderPos = int(math.Round(float64(percent) / 100 * float64(s.pxHeight)))
}

func (s Slider) GetPercent() int {
	return int(math.Round(float64(s.sliderPos) / float64(s.pxHeight) * 100))
}
