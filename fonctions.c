/**
* @file fonctions.c
* @brief all the menu functions
* @author Mohamed Ali Bouzaiene
* @version 0.0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions.h"

void menu(SDL_Surface *background, SDL_Surface *screen, SDL_Rect positionbackground, texte *txt, SDL_Surface *play, SDL_Surface *setting, SDL_Surface *quit, SDL_Rect positionplay, SDL_Rect positionsetting, SDL_Rect positionquit, SDL_Surface *credits, SDL_Rect positioncredits)
{
    SDL_BlitSurface(background, NULL, screen, &positionbackground);
    SDL_BlitSurface(play, NULL, screen, &positionplay);
    SDL_BlitSurface(setting, NULL, screen, &positionsetting);
    SDL_BlitSurface(credits, NULL, screen, &positioncredits);
    SDL_BlitSurface(quit, NULL, screen, &positionquit);
    SDL_Flip(screen);
}

void menu1(SDL_Surface *background1, SDL_Surface *screen, SDL_Rect positionbackground)
{
    SDL_BlitSurface(background1, NULL, screen, &positionbackground);
    SDL_Flip(screen);
}

void fleche(int etat, SDL_Surface *screen, SDL_Surface *play, SDL_Surface *quit, SDL_Surface *setting, SDL_Surface *credits, SDL_Surface *quit1, SDL_Surface *setting1, SDL_Surface *play1, SDL_Surface *credits1, SDL_Rect positionplay, SDL_Rect positionquit, SDL_Rect positionsetting, SDL_Rect positioncredits)
{
    if (etat == 0)
    {
        SDL_BlitSurface(play1, NULL, screen, &positionplay);
        SDL_BlitSurface(setting, NULL, screen, &positionsetting);
        SDL_BlitSurface(credits, NULL, screen, &positioncredits);
        SDL_BlitSurface(quit, NULL, screen, &positionquit);
        SDL_Flip(screen);
    }
    else if (etat == 1)
    {
        SDL_BlitSurface(play, NULL, screen, &positionplay);
        SDL_BlitSurface(setting1, NULL, screen, &positionsetting);
        SDL_BlitSurface(credits, NULL, screen, &positioncredits);
        SDL_BlitSurface(quit, NULL, screen, &positionquit);
        SDL_Flip(screen);
    }
    else if (etat == 2)
    {
        SDL_BlitSurface(play, NULL, screen, &positionplay);
        SDL_BlitSurface(setting, NULL, screen, &positionsetting);
        SDL_BlitSurface(credits1, NULL, screen, &positioncredits);
        SDL_BlitSurface(quit, NULL, screen, &positionquit);
        SDL_Flip(screen);
    }
    else if (etat == 3)
    {
        SDL_BlitSurface(play, NULL, screen, &positionplay);
        SDL_BlitSurface(setting, NULL, screen, &positionsetting);
        SDL_BlitSurface(credits, NULL, screen, &positioncredits);
        SDL_BlitSurface(quit1, NULL, screen, &positionquit);
        SDL_Flip(screen);
    }
}

void animation1(SDL_Surface *background3, SDL_Surface *screen, SDL_Rect *position, SDL_Surface *background1, SDL_Rect positionbackground)
{
    SDL_BlitSurface(background1, NULL, screen, &positionbackground);
    SDL_BlitSurface(background3, NULL, screen, &(*position));
    SDL_Flip(screen);
    (*position).x -= 4;
    (*position).y += 6;
    if ((*position).y > 50)
    {
        (*position).x = 10;
        (*position).y = 0;
    }
    SDL_BlitSurface(background3, NULL, screen, &(*position));
    SDL_Flip(screen);
}

int personnage(SDL_Surface *screen)
{
    SDL_Rect pos[3], position;
    SDL_Surface *background[2], *boutons[6];
    int i, continuer = 1, perso = 0, j;
    SDL_Event event;

    background[0] = IMG_Load("changement.jpg");
    background[1] = IMG_Load("changement2.jpg");
    boutons[0] = IMG_Load("prec.png");
    boutons[1] = IMG_Load("prec_pressed.png");
    boutons[2] = IMG_Load("suiv.png");
    boutons[3] = IMG_Load("suiv_pressed.png");
    boutons[4] = IMG_Load("save_not_pressed.png");
    boutons[5] = IMG_Load("save_pressed.png");

    position.x = 0;
    position.y = 0;
    pos[0].x = 1400;
    pos[0].y = 500;
    pos[1].x = 1850;
    pos[1].y = 500;
    pos[2].x = 1520;
    pos[2].y = 700;

    SDL_BlitSurface(background[0], NULL, screen, &position);
    for (i = 0, j = 0; i < 3, j < 5; i++, j = j + 2)
        SDL_BlitSurface(boutons[j], NULL, screen, &pos[i]);
    SDL_Flip(screen);
    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION: //les bouttons
                for (i = 0, j = 0; i < 3, j < 5; i++, j = j + 2)
                {
                    if (i < 2)
                    {
                        if (event.motion.x >= pos[i].x && event.motion.x <= (pos[i].x + 63) && event.motion.y >= pos[i].y && event.motion.y <= pos[i].y + 78)
                        {
                            SDL_BlitSurface(boutons[j + 1], NULL, screen, &pos[i]);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(boutons[j], NULL, screen, &pos[i]);
                            SDL_Flip(screen);
                        }
                    }
                    else
                    {
                        if (event.motion.x >= pos[i].x && event.motion.x <= (pos[i].x + 273) && event.motion.y >= pos[i].y && event.motion.y <= pos[i].y + 138)
                        {
                            SDL_BlitSurface(boutons[j + 1], NULL, screen, &pos[i]);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(boutons[j], NULL, screen, &pos[i]);
                            SDL_Flip(screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN: //les bouttons
                if (event.motion.x >= pos[0].x && event.motion.x <= (pos[0].x + 63) && event.motion.y >= pos[0].y && event.motion.y <= pos[0].y + 78)
                {
                    perso--;
                    if (perso < 0)
                        perso = 1;
                    SDL_BlitSurface(background[perso], NULL, screen, &position);
                    for (i = 0, j = 0; i < 3, j < 5; i++, j = j + 2)
                        SDL_BlitSurface(boutons[j], NULL, screen, &pos[i]);
                }
                else if (event.motion.x >= pos[1].x && event.motion.x <= (pos[1].x + 63) && event.motion.y >= pos[1].y && event.motion.y <= pos[1].y + 78)
                {
                    perso++;
                    if (perso > 1)
                        perso = 0;
                    SDL_BlitSurface(background[perso], NULL, screen, &position);
                    for (i = 0, j = 0; i < 3, j < 5; i++, j = j + 2)
                        SDL_BlitSurface(boutons[j], NULL, screen, &pos[i]);
                }
                else if (event.motion.x >= pos[2].x && event.motion.x <= (pos[2].x + 273) && event.motion.y >= pos[2].y && event.motion.y <= pos[2].y + 138)
                {
                    continuer = 0;
                }
                break;
            }
            SDL_Flip(screen);
        }
    }
    for (i = 0; i < 6; i++)
        SDL_FreeSurface(boutons[i]);
    for (i = 0; i < 2; i++)
        SDL_FreeSurface(background[i]);
    return perso;
}

int change(SDL_Surface *screen)
{
    SDL_Surface *bk, *boutons[8];
    SDL_Rect pos, po[4];
    SDL_Event event;
    int continuer = 1, i, j;

    pos.x = 0;
    pos.y = 0;
    bk = IMG_Load("control.jpg");

    boutons[0] = IMG_Load("arrow_not_pressed.png");
    boutons[1] = IMG_Load("arrow_pressed.png");
    boutons[2] = IMG_Load("zqsd_not_pressed.png");
    boutons[3] = IMG_Load("zqsd_pressed.png");
    boutons[4] = IMG_Load("mouse_not_pressed.png");
    boutons[5] = IMG_Load("mouse_pressed.png");
    boutons[6] = IMG_Load("controller_not_pressed.png");
    boutons[7] = IMG_Load("controller_pressed.png");

    po[0].x = 1400;
    po[0].y = 250;
    po[1].x = 1700;
    po[1].y = 250;
    po[2].x = 1570;
    po[2].y = 450;
    po[3].x = 1550;
    po[3].y = 700;

    SDL_BlitSurface(bk, NULL, screen, &pos);
    SDL_BlitSurface(boutons[0], NULL, screen, &po[0]);
    SDL_BlitSurface(boutons[2], NULL, screen, &po[1]);
    SDL_BlitSurface(boutons[4], NULL, screen, &po[2]);
    SDL_BlitSurface(boutons[6], NULL, screen, &po[3]);
    SDL_Flip(screen);
    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= po[0].x && event.motion.x <= (po[0].x + 178) && event.motion.y >= po[0].y && event.motion.y <= po[0].y + 112)
                {
                    SDL_BlitSurface(boutons[1], NULL, screen, &po[0]);
                    SDL_Flip(screen);
                }
                else
                {
                    SDL_BlitSurface(boutons[0], NULL, screen, &po[0]);
                    SDL_Flip(screen);
                }
                if (event.motion.x >= po[1].x && event.motion.x <= (po[1].x + 178) && event.motion.y >= po[1].y && event.motion.y <= po[1].y + 112)
                {
                    SDL_BlitSurface(boutons[3], NULL, screen, &po[1]);
                    SDL_Flip(screen);
                }
                else
                {
                    SDL_BlitSurface(boutons[2], NULL, screen, &po[1]);
                    SDL_Flip(screen);
                }
                if (event.motion.x >= po[2].x && event.motion.x <= (po[2].x + 155) && event.motion.y >= po[2].y && event.motion.y <= po[2].y + 124)
                {
                    SDL_BlitSurface(boutons[5], NULL, screen, &po[2]);
                    SDL_Flip(screen);
                }
                else
                {
                    SDL_BlitSurface(boutons[4], NULL, screen, &po[2]);
                    SDL_Flip(screen);
                }
                if (event.motion.x >= po[3].x && event.motion.x <= (po[3].x + 159) && event.motion.y >= po[3].y && event.motion.y <= po[3].y + 121)
                {
                    SDL_BlitSurface(boutons[7], NULL, screen, &po[3]);
                    SDL_Flip(screen);
                }
                else
                {
                    SDL_BlitSurface(boutons[6], NULL, screen, &po[3]);
                    SDL_Flip(screen);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x >= po[0].x && event.motion.x <= (po[0].x + 178) && event.motion.y >= po[0].y && event.motion.y <= po[0].y + 112)
                {
                    i = 0; //fleche
                    continuer = 0;
                }
                if (event.motion.x >= po[1].x && event.motion.x <= (po[1].x + 178) && event.motion.y >= po[1].y && event.motion.y <= po[1].y + 112)
                {
                    i = 1; //zqsd
                    continuer = 0;
                }
                if (event.motion.x >= po[2].x && event.motion.x <= (po[2].x + 155) && event.motion.y >= po[2].y && event.motion.y <= po[2].y + 124)
                {
                    i = 2; //souris
                    continuer = 0;
                }
                if (event.motion.x >= po[3].x && event.motion.x <= (po[3].x + 159) && event.motion.y >= po[3].y && event.motion.y <= po[3].y + 121)
                {
                    i = 0; //flech car pas de manette
                    continuer = 0;
                }
                break;
            }
        }
    }
    return i;
}


/*void music(SDL_Surface *screen,SDL_Surface *bout[2],Mix_Music *musique[2])
{
    SDL_Rect positionmusic;
    int i = 0;
    SDL_Event event;

    

    positionmusic.x = 1755;
    positionmusic.y = 115;

    
    
    SDL_BlitSurface(bout[0], NULL, screen, &pos);
    SDL_Flip(screen);
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 108) && event.motion.y >= pos.y && event.motion.y <= pos.y + 98)
            {
                SDL_BlitSurface(bout[1], NULL, screen, &pos);
                SDL_Flip(screen);
            }
            else
            {
                SDL_BlitSurface(bout[0], NULL, screen, &pos);
                SDL_Flip(screen);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 108) && event.motion.y >= pos.y && event.motion.y <= pos.y + 98)
            {
                if (i<1)
                i++;
                else
                {
                    i=0;
                }
                Mix_PlayMusic(musique[i], -1);
            }
            break;
        }
    }
}*/