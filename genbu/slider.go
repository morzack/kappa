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

	dragRadius = 30
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
	if percent < 0 {
		percent = 0
	} else if percent > 100 {
		percent = 100
	}
	s.sliderPos = int(math.Round(float64(percent) / 100 * float64(s.pxHeight)))
}

func (s Slider) GetPercent() int {
	return int(math.Round(float64(s.sliderPos) / float64(s.pxHeight) * 100))
}

func (s Slider) ScreenPosToPercent(x, y int) int {
	calculatedY := s.y - y + s.pxHeight + sliderSpriteHeight/2
	return int(math.Round(float64(calculatedY) / float64(s.pxHeight) * 100))
}

func (s Slider) CheckInRadius(x, y int) bool {
	return math.Hypot(float64(x-(s.x+sliderSpriteWidth/2)), float64(y-(s.y+s.pxHeight-s.sliderPos+sliderSpriteHeight/2))) < dragRadius
}

func (s *Slider) Update(input *Input) {
	if s.CheckInRadius(input.mX, input.mY) && input.mState == mousePressed {
		s.SetPercent(s.ScreenPosToPercent(input.mX, input.mY))
	} else {
		s.SetPercent(50)
	}
}

func (s Slider) GetPercentFloatOffset() float32 {
	return float32(s.GetPercent()-50) / 50
}
