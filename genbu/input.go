package genbu

import "github.com/hajimehoshi/ebiten"

type mouseState int

const (
	mouseReleased mouseState = iota
	mousePressed
)

type Input struct {
	mState           mouseState
	mStartX, mStartY int
	mX, mY           int
}

func NewInput() *Input {
	return &Input{}
}

func (i *Input) Update() {
	switch i.mState {
	case mouseReleased:
		if ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft) {
			x, y := ebiten.CursorPosition()
			i.mStartX = x
			i.mStartY = y
			i.mState = mousePressed
		}
	case mousePressed:
		if !ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft) {
			i.mState = mouseReleased
		}
	}
	i.mX, i.mY = ebiten.CursorPosition()
}
