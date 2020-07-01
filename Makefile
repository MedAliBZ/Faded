Game: menu1.o game.o ennemy.o vie.o player.o bounding.o chrono.o scrol.o collisionparfait.o enigmes.o gamep.o savegame.o minimap.o xo.o fonctions.o
	gcc menu1.o game.o ennemy.o vie.o player.o bounding.o chrono.o scrol.o collisionparfait.o enigmes.o gamep.o savegame.o minimap.o xo.o fonctions.o -o Game -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx

menu1.o:menu1.c
	gcc -c menu1.c 
game.o:game.c
	gcc -c game.c
ennemy.o:ennemy.c
	gcc -c ennemy.c
vie.o:vie.c
	gcc -c vie.c
player.o:player.c
	gcc -c player.c
bounding.o:bounding.c
	gcc -c bounding.c
chrono.o:chrono.c
	gcc -c chrono.c
scrol.o:scrol.c
	gcc -c scrol.c
collisionparfait.o:collisionparfait.c
	gcc -c collisionparfait.c
enigmes.o:enigmes.c
	gcc -c enigmes.c
savegame.o:savegame.c
	gcc -c savegame.c
gamep.o:gamep.c
	gcc -c gamep.c
minimap.o:minimap.c
	gcc -c minimap.c
xo.o:xo.c
	gcc -c xo.c
fonctions.o:fonctions.c
	gcc -c fonctions.c
