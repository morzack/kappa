package genbu

import (
	"image"

	"github.com/hajimehoshi/ebiten"
)

const (
	ScreenWidth  = 256
	ScreenHeight = 256

	WindowTitle = "genbu"
)

func InitializeWindow() {
	ebiten.SetWindowSize(ScreenWidth*2, ScreenHeight*2)
	ebiten.SetWindowTitle(WindowTitle)
}

func DrawImage(img *ebiten.Image, screen *ebiten.Image, screenX int, screenY int, scale float64, spriteX int, spriteY int, spriteWidth int, spriteHeight int) {
	op := &ebiten.DrawImageOptions{}
	op.GeoM.Scale(scale, scale)
	op.GeoM.Translate(-float64(spriteWidth/2), -float64(spriteHeight/2))
	op.GeoM.Translate(float64(screenX), float64(screenY))
	screen.DrawImage(img.SubImage(image.Rect(spriteX, spriteY, spriteWidth+spriteX, spriteHeight+spriteY)).(*ebiten.Image), op)
}
