package genbu

import (
	"image/color"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

type Button struct {
	x, y   int
	radius int

	pressed bool
}

func NewButton(x, y, radius int) Button {
	return Button{
		x:      x,
		y:      y,
		radius: radius,
	}
}

func (b *Button) CheckInBounds(x, y int) bool {
	return (x < b.x+b.radius && b.x < x && y < b.y+b.radius && b.y < y)
}

func (b *Button) Draw(screen *ebiten.Image) {
	ebitenutil.DrawRect(screen, float64(b.x), float64(b.y), float64(b.radius), float64(b.radius), color.Black)

	offset := float64(b.radius) * .1

	if !b.pressed {
		ebitenutil.DrawRect(screen, float64(b.x)+offset, float64(b.y)+offset, float64(b.radius)-2*offset, float64(b.radius)-2*offset, color.White)
	}
}

func (b *Button) Update(input *Input) {
	b.pressed = b.CheckInBounds(input.mX, input.mY) && input.mState == mousePressed
}
