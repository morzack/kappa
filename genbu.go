package main

import (
	"log"

	"github.com/hajimehoshi/ebiten"
	"github.com/morzack/kappa/genbu"
)

func main() {
	genbu, err := genbu.NewGenbuInstance()
	if err != nil {
		log.Fatal(err)
	}

	if err := ebiten.RunGame(genbu); err != nil {
		log.Fatal(err)
	}
}
