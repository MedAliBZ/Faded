/**
* @file enigmes.c
* @brief toutes les enigmes
* @author Mohamed Ali Bouzaiene
* @version 0.0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions.h"
#include "enigmes.h"

int enigme1(SDL_Surface *screen)
{
    clock_t debut, fin;
    long clk_tck = CLOCKS_PER_SEC;
    int difference = 0;
    char temps[4];
    SDL_Surface *timee, *black;

    int num[8], i, affich[4], c, lvl = 0, continuer = 1, f = 0;
    TTF_Font *police = NULL;
    SDL_Surface *texte[8], *background, *bout[4], *finish[2];
    SDL_Rect position[8], pos, bouton[4], cont;
    SDL_Color couleurblanc = {255, 255, 255};
    SDL_Event event, event2;
    char rep[8][5];
    srand(time(NULL));
    num[0] = rand() % 5 + 1;
    for (i = 1; i < 4; i++)
    {
        num[i] = rand() % 20 + 2;
    }
    num[4] = ((num[1] + num[2]) * num[0]) - num[3];
    for (i = 5; i < 8; i++)
    {
        num[i] = rand() % 50 + 2;
    }
    affich[0] = rand() % 4 + 4;
    do
    {
        affich[1] = rand() % 4 + 4;
    } while (affich[0] == affich[1]);
    do
    {
        affich[2] = rand() % 4 + 4;
    } while (affich[0] == affich[2] || affich[1] == affich[2]);
    do
    {
        affich[3] = rand() % 4 + 4;
    } while (affich[0] == affich[3] || affich[1] == affich[3] || affich[2] == affich[3]);
    TTF_Init();
    for (i = 0; i < 8; i++)
    {
        sprintf(rep[i], "%i", num[i]);
    }
    police = TTF_OpenFont("roboto.ttf", 110); //chargement police

    if (police == NULL)
    {
        printf("police erreur\n");
    }
    for (i = 0; i < 8; i++)
        texte[i] = TTF_RenderText_Blended(police, rep[i], couleurblanc); //chargement text

    background = IMG_Load("enigme1.jpg");
    bout[0] = IMG_Load("bouton_enigme_not_pressed.png");
    bout[1] = IMG_Load("bouton_enigme_pressed.png");
    bout[2] = IMG_Load("bouton_continue_not_pressed.png");
    bout[3] = IMG_Load("bouton_continue_pressed.png");
    finish[0] = IMG_Load("enigme1_win.jpg");
    finish[1] = IMG_Load("enigme1_loss.jpg");

    position[1].x = 480;
    position[1].y = 260;
    position[2].x = 700;
    position[2].y = 260;
    position[0].x = 1000;
    position[0].y = 260;
    position[3].x = 1220;
    position[3].y = 260;
    position[4].x = 668;
    position[4].y = 478;
    position[5].x = 1180;
    position[5].y = 478;
    position[6].x = 668;
    position[6].y = 690;
    position[7].x = 1180;
    position[7].y = 690;
    cont.x = 1120;
    cont.y = 480;

    for (i = 0; i < 4; i++)
    {
        bouton[i].x = position[4 + i].x - 75;
        bouton[i].y = position[4 + i].y;
    }
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(background, NULL, screen, &pos);
    for (i = 0; i < 4; i++)
        SDL_BlitSurface(bout[0], NULL, screen, &bouton[i]);
    SDL_BlitSurface(texte[1], NULL, screen, &position[1]);
    SDL_BlitSurface(texte[2], NULL, screen, &position[2]);
    SDL_BlitSurface(texte[0], NULL, screen, &position[0]);
    SDL_BlitSurface(texte[3], NULL, screen, &position[3]);
    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
    SDL_Flip(screen);

    black = IMG_Load("block.png");
    debut = clock();

    while (continuer)
    {
        fin = clock();
        difference = (int)(fin - debut) / (int)clk_tck;
        sprintf(temps, "%i", difference);
        timee = TTF_RenderText_Blended(police, temps, couleurblanc);
        SDL_BlitSurface(black, NULL, screen, &pos);
        SDL_BlitSurface(timee, NULL, screen, &pos);
        SDL_Flip(screen);
        if (difference >= 10)
        {
            lvl = 2;
            SDL_BlitSurface(finish[1], NULL, screen, &pos);
            SDL_BlitSurface(bout[2], NULL, screen, &cont);
            SDL_Flip(screen);
            f = 1;
            while (f == 1)
            {
                SDL_WaitEvent(&event2);
                switch (event2.type)
                {
                case SDL_MOUSEMOTION:
                    if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                    {
                        SDL_BlitSurface(bout[3], NULL, screen, &cont);
                        SDL_Flip(screen);
                    }
                    else
                    {
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                    {
                        f = 0;
                        continuer = 0;
                    }
                }
            }
        }
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= bouton[0].x && event.motion.x <= (bouton[0].x + 273) && event.motion.y >= bouton[0].y && event.motion.y <= bouton[0].y + 138)
                {
                    SDL_BlitSurface(bout[1], NULL, screen, &bouton[0]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[1]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[2]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[3]);
                    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
                    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
                    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
                    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
                    SDL_Flip(screen);
                }
                else if (event.motion.x >= bouton[1].x && event.motion.x <= (bouton[1].x + 273) && event.motion.y >= bouton[1].y && event.motion.y <= bouton[1].y + 138)
                {
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[0]);
                    SDL_BlitSurface(bout[1], NULL, screen, &bouton[1]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[2]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[3]);
                    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
                    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
                    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
                    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
                    SDL_Flip(screen);
                }
                else if (event.motion.x >= bouton[2].x && event.motion.x <= (bouton[2].x + 273) && event.motion.y >= bouton[2].y && event.motion.y <= bouton[2].y + 138)
                {
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[0]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[1]);
                    SDL_BlitSurface(bout[1], NULL, screen, &bouton[2]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[3]);
                    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
                    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
                    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
                    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
                    SDL_Flip(screen);
                }
                else if (event.motion.x >= bouton[3].x && event.motion.x <= (bouton[3].x + 273) && event.motion.y >= bouton[3].y && event.motion.y <= bouton[3].y + 138)
                {
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[0]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[1]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[2]);
                    SDL_BlitSurface(bout[1], NULL, screen, &bouton[3]);
                    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
                    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
                    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
                    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
                    SDL_Flip(screen);
                }
                else
                {
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[0]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[1]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[2]);
                    SDL_BlitSurface(bout[0], NULL, screen, &bouton[3]);
                    SDL_BlitSurface(texte[affich[0]], NULL, screen, &position[4]);
                    SDL_BlitSurface(texte[affich[1]], NULL, screen, &position[5]);
                    SDL_BlitSurface(texte[affich[2]], NULL, screen, &position[6]);
                    SDL_BlitSurface(texte[affich[3]], NULL, screen, &position[7]);
                    SDL_Flip(screen);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x >= bouton[0].x && event.motion.x <= (bouton[0].x + 273) && event.motion.y >= bouton[0].y && event.motion.y <= bouton[0].y + 138)
                {
                    c = 0;
                    if (affich[c] == 4)
                    {
                        SDL_BlitSurface(finish[0], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        lvl = 1;
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        lvl = 2;
                        SDL_BlitSurface(finish[1], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                }
                else if (event.motion.x >= bouton[1].x && event.motion.x <= (bouton[1].x + 273) && event.motion.y >= bouton[1].y && event.motion.y <= bouton[1].y + 138)
                {
                    c = 1;
                    if (affich[c] == 4)
                    {
                        SDL_BlitSurface(finish[0], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        lvl = 1;
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        lvl = 2;
                        SDL_BlitSurface(finish[1], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                }
                else if (event.motion.x >= bouton[2].x && event.motion.x <= (bouton[2].x + 273) && event.motion.y >= bouton[2].y && event.motion.y <= bouton[2].y + 138)
                {
                    c = 2;
                    if (affich[c] == 4)
                    {
                        SDL_BlitSurface(finish[0], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        lvl = 1;
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        lvl = 2;
                        SDL_BlitSurface(finish[1], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                }
                else if (event.motion.x >= bouton[3].x && event.motion.x <= (bouton[3].x + 273) && event.motion.y >= bouton[3].y && event.motion.y <= bouton[3].y + 138)
                {
                    c = 3;
                    if (affich[c] == 4)
                    {
                        SDL_BlitSurface(finish[0], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        lvl = 1;
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        lvl = 2;
                        SDL_BlitSurface(finish[1], NULL, screen, &pos);
                        SDL_BlitSurface(bout[2], NULL, screen, &cont);
                        SDL_Flip(screen);
                        f = 1;
                        while (f == 1)
                        {
                            SDL_WaitEvent(&event2);
                            switch (event2.type)
                            {
                            case SDL_MOUSEMOTION:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                else
                                {
                                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                    SDL_Flip(screen);
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                                {
                                    f = 0;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
    } //taskiret l while
    for (i = 0; i < 8; i++)
        SDL_FreeSurface(texte[i]);
    for (i = 0; i < 4; i++)
        SDL_FreeSurface(bout[i]);
    for (i = 0; i < 2; i++)
        SDL_FreeSurface(finish[i]);
    SDL_FreeSurface(background);

    return lvl;
}

int enigme2(SDL_Surface *screen)
{
    int lvl = 2, continuer = 1, o = 0, f = 0, fail = -5, i = 0;
    SDL_Surface *fridge[2], *background, *panda, *finish[3], *bout[2];
    SDL_Rect position, pos, position1, position2, cont, cont1;
    SDL_Event event, event2;

    background = IMG_Load("enigme2.jpg");
    fridge[0] = IMG_Load("fridge.png");
    fridge[1] = IMG_Load("fridge_open.png");
    panda = IMG_Load("panda.png");
    bout[0] = IMG_Load("bouton2_continue_not_pressed.png");
    bout[1] = IMG_Load("bouton2_continue_pressed.png");
    finish[0] = IMG_Load("enigme2_win.jpg");
    finish[1] = IMG_Load("enigme2_loss.jpg");
    finish[2] = IMG_Load("enigme2_help.jpg");
    position.x = 500;
    position.y = 300;
    pos.x = 0;
    pos.y = 0;
    cont.x = 600;
    cont.y = 600;
    cont1.x = 560;
    cont1.y = 580;
    position1.x = 1200;
    position1.y = 350;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                if (position.x < 1390)
                    position.x += 30;
                if (o == 0 && position.x + 200 >= position1.x)
                    fail++;
                break;
            case SDLK_LEFT:
                if (position.x > 420)
                    position.x -= 30;
                if (o == 0 && position.x + 200 >= position1.x)
                    fail++;
                break;
            case SDLK_DOWN:
                if (position.y < 620)
                    position.y += 30;
                if (o == 0 && position.x + 200 >= position1.x)
                    fail++;
                break;
            case SDLK_UP:
                if (position.y > 180)
                    position.y -= 30;
                if (o == 0 && position.x + 200 >= position1.x)
                    fail++;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.motion.x >= position1.x && event.motion.x <= (position1.x + 203) && event.motion.y >= position1.y && event.motion.y <= position1.y + 468)
            {
                o = 1;
            }
            break;
        }
        if (o == 1 && position.x + 200 >= position1.x)
        {
            lvl = 1;
            SDL_BlitSurface(finish[0], NULL, screen, &pos);
            SDL_BlitSurface(bout[0], NULL, screen, &cont);
            SDL_Flip(screen);
            f = 1;
            while (f == 1)
            {
                SDL_WaitEvent(&event2);
                switch (event2.type)
                {
                case SDL_MOUSEMOTION:
                    if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                    {
                        SDL_BlitSurface(bout[1], NULL, screen, &cont);
                        SDL_Flip(screen);
                    }
                    else
                    {
                        SDL_BlitSurface(bout[0], NULL, screen, &cont);
                        SDL_Flip(screen);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                    {
                        f = 0;
                        continuer = 0;
                    }
                }
            }
        }
        else if (o == 0 && position.x + 200 >= position1.x)
        {
            if (fail == 15)
            {
                SDL_BlitSurface(finish[2], NULL, screen, &pos);
                SDL_BlitSurface(bout[0], NULL, screen, &cont1);
                SDL_Flip(screen);
                while (fail == 15)
                {
                    SDL_WaitEvent(&event2);
                    switch (event2.type)
                    {
                    case SDL_MOUSEMOTION:
                        if (event2.motion.x >= cont1.x && event2.motion.x <= (cont1.x + 273) && event2.motion.y >= cont1.y && event2.motion.y <= cont1.y + 138)
                        {
                            SDL_BlitSurface(bout[1], NULL, screen, &cont1);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(bout[0], NULL, screen, &cont1);
                            SDL_Flip(screen);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event2.motion.x >= cont1.x && event2.motion.x <= (cont1.x + 273) && event2.motion.y >= cont1.y && event2.motion.y <= cont1.y + 138)
                        {
                            fail++;
                        }
                    }
                }
            }
            else if (fail == 40)
            {
                lvl = 2;
                SDL_BlitSurface(finish[1], NULL, screen, &pos);
                SDL_BlitSurface(bout[0], NULL, screen, &cont1);
                SDL_Flip(screen);
                while (fail == 40)
                {
                    SDL_WaitEvent(&event2);
                    switch (event2.type)
                    {
                    case SDL_MOUSEMOTION:
                        if (event2.motion.x >= cont1.x && event2.motion.x <= (cont1.x + 273) && event2.motion.y >= cont1.y && event2.motion.y <= cont1.y + 138)
                        {
                            SDL_BlitSurface(bout[1], NULL, screen, &cont1);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(bout[0], NULL, screen, &cont1);
                            SDL_Flip(screen);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event2.motion.x >= cont1.x && event2.motion.x <= (cont1.x + 273) && event2.motion.y >= cont1.y && event2.motion.y <= cont1.y + 138)
                        {
                            fail = 41;
                            continuer = 0;
                        }
                    }
                }
            }
        }
        SDL_BlitSurface(background, NULL, screen, &pos);
        SDL_BlitSurface(fridge[o], NULL, screen, &position1);
        SDL_BlitSurface(panda, NULL, screen, &position);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(background);
    SDL_FreeSurface(panda);
    for (i = 0; i < 2; i++)
    {
        SDL_FreeSurface(fridge[i]);
        SDL_FreeSurface(bout[i]);
    }
    for (i = 0; i < 3; i++)
        SDL_FreeSurface(finish[i]);
    return lvl;
}

int enigme3(SDL_Surface *screen)
{
    int lvl = 0, k = 0, continuer = 1, i = 0, Q, affich[4], text[4], c, f;
    FILE *ff, *g;
    char questions[8][60], answers[8][12];
    SDL_Surface *background, *quest[8], *answ[8], *bout[4], *finish[2];
    SDL_Rect pos, position[9];
    SDL_Event event, event2;
    TTF_Font *police = NULL;
    SDL_Color couleurblanc = {255, 255, 255};
    SDL_Rect cont;

    TTF_Init();
    police = TTF_OpenFont("roboto.ttf", 50); //chargement police
    if (police == NULL)
        printf("police erreur\n");
    ff = fopen("answers.txt", "r");
    if (ff == NULL)
        printf("fichier NULL\n");
    g = fopen("questions.txt", "r");
    if (g == NULL)
        printf("fichier NULL\n");
    while (!feof(ff))
    {
        fgets(questions[k], 60, g);
        fgets(answers[k], 12, ff);
        k++;
    }
    for (i = 0; i < 8; i++)
    {
        quest[i] = TTF_RenderText_Blended(police, questions[i], couleurblanc);
        answ[i] = TTF_RenderText_Blended(police, answers[i], couleurblanc);
    }

    srand(time(NULL));
    Q = rand() % 8; //generation de nombre aleatoire entre 0 et 8
    text[0] = Q;
    do
    {
        text[1] = rand() % 8;
    } while (text[0] == text[1]);
    do
    {
        text[2] = rand() % 8;
    } while (text[0] == text[2] || text[1] == text[2]);
    do
    {
        text[3] = rand() % 8;
    } while (text[0] == text[3] || text[1] == text[3] || text[2] == text[3]);

    affich[0] = rand() % 4;
    do
    {
        affich[1] = rand() % 4;
    } while (affich[0] == affich[1]);
    do
    {
        affich[2] = rand() % 4;
    } while (affich[0] == affich[2] || affich[1] == affich[2]);
    do
    {
        affich[3] = rand() % 4;
    } while (affich[0] == affich[3] || affich[1] == affich[3] || affich[2] == affich[3]);

    background = IMG_Load("enigme3.jpg");
    bout[0] = IMG_Load("reponse_not_pressed.png");
    bout[1] = IMG_Load("reponse_pressed.png");
    bout[2] = IMG_Load("bouton3_continue_not_pressed.png");
    bout[3] = IMG_Load("bouton3_continue_pressed.png");
    finish[0] = IMG_Load("enigme3_win.jpg");
    finish[1] = IMG_Load("enigme3_loss.jpg");
    pos.x = 0;
    pos.y = 0;
    position[0].x = 435;
    position[0].y = 220;
    position[1].x = 450;
    position[1].y = 450;
    position[2].x = 1020;
    position[2].y = 450;
    position[3].x = 450;
    position[3].y = 650;
    position[4].x = 1020;
    position[4].y = 650;
    position[5].x = 500;
    position[5].y = 470;
    position[6].x = 1070;
    position[6].y = 470;
    position[7].x = 500;
    position[7].y = 670;
    position[8].x = 1070;
    position[8].y = 670;
    cont.x = 1140;
    cont.y = 530;
    SDL_BlitSurface(background, NULL, screen, &pos);
    SDL_BlitSurface(quest[Q], NULL, screen, &position[0]);
    for (i = 1; i < 5; i++)
        SDL_BlitSurface(bout[0], NULL, screen, &position[i]);
    for (i = 1; i < 5; i++)
        SDL_BlitSurface(answ[text[affich[i - 1]]], NULL, screen, &position[i + 4]);
    SDL_Flip(screen);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEMOTION:
            if (event.motion.x >= position[1].x && event.motion.x <= (position[1].x + 468) && event.motion.y >= position[1].y && event.motion.y <= position[1].y + 123)
            {
                SDL_BlitSurface(bout[1], NULL, screen, &position[1]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[2]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[3]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[4]);
                SDL_BlitSurface(answ[text[affich[0]]], NULL, screen, &position[5]);
                SDL_BlitSurface(answ[text[affich[1]]], NULL, screen, &position[6]);
                SDL_BlitSurface(answ[text[affich[2]]], NULL, screen, &position[7]);
                SDL_BlitSurface(answ[text[affich[3]]], NULL, screen, &position[8]);
                SDL_Flip(screen);
            }
            else if (event.motion.x >= position[2].x && event.motion.x <= (position[2].x + 468) && event.motion.y >= position[2].y && event.motion.y <= position[2].y + 123)
            {
                SDL_BlitSurface(bout[0], NULL, screen, &position[1]);
                SDL_BlitSurface(bout[1], NULL, screen, &position[2]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[3]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[4]);
                SDL_BlitSurface(answ[text[affich[0]]], NULL, screen, &position[5]);
                SDL_BlitSurface(answ[text[affich[1]]], NULL, screen, &position[6]);
                SDL_BlitSurface(answ[text[affich[2]]], NULL, screen, &position[7]);
                SDL_BlitSurface(answ[text[affich[3]]], NULL, screen, &position[8]);
                SDL_Flip(screen);
            }
            else if (event.motion.x >= position[3].x && event.motion.x <= (position[3].x + 468) && event.motion.y >= position[3].y && event.motion.y <= position[3].y + 123)
            {
                SDL_BlitSurface(bout[0], NULL, screen, &position[1]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[2]);
                SDL_BlitSurface(bout[1], NULL, screen, &position[3]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[4]);
                SDL_BlitSurface(answ[text[affich[0]]], NULL, screen, &position[5]);
                SDL_BlitSurface(answ[text[affich[1]]], NULL, screen, &position[6]);
                SDL_BlitSurface(answ[text[affich[2]]], NULL, screen, &position[7]);
                SDL_BlitSurface(answ[text[affich[3]]], NULL, screen, &position[8]);
                SDL_Flip(screen);
            }
            else if (event.motion.x >= position[4].x && event.motion.x <= (position[4].x + 468) && event.motion.y >= position[4].y && event.motion.y <= position[4].y + 123)
            {
                SDL_BlitSurface(bout[0], NULL, screen, &position[1]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[2]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[3]);
                SDL_BlitSurface(bout[1], NULL, screen, &position[4]);
                SDL_BlitSurface(answ[text[affich[0]]], NULL, screen, &position[5]);
                SDL_BlitSurface(answ[text[affich[1]]], NULL, screen, &position[6]);
                SDL_BlitSurface(answ[text[affich[2]]], NULL, screen, &position[7]);
                SDL_BlitSurface(answ[text[affich[3]]], NULL, screen, &position[8]);
                SDL_Flip(screen);
            }
            else
            {
                SDL_BlitSurface(bout[0], NULL, screen, &position[1]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[2]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[3]);
                SDL_BlitSurface(bout[0], NULL, screen, &position[4]);
                SDL_BlitSurface(answ[text[affich[0]]], NULL, screen, &position[5]);
                SDL_BlitSurface(answ[text[affich[1]]], NULL, screen, &position[6]);
                SDL_BlitSurface(answ[text[affich[2]]], NULL, screen, &position[7]);
                SDL_BlitSurface(answ[text[affich[3]]], NULL, screen, &position[8]);
                SDL_Flip(screen);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.motion.x >= position[1].x && event.motion.x <= (position[1].x + 468) && event.motion.y >= position[1].y && event.motion.y <= position[1].y + 123)
            {
                c = 0;
                if (text[affich[c]] == Q)
                {
                    SDL_BlitSurface(finish[0], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    lvl = 1;
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
                else
                {
                    lvl = 2;
                    SDL_BlitSurface(finish[1], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
            }
            else if (event.motion.x >= position[2].x && event.motion.x <= (position[2].x + 468) && event.motion.y >= position[2].y && event.motion.y <= position[2].y + 123)
            {
                c = 1;
                if (text[affich[c]] == Q)
                {
                    SDL_BlitSurface(finish[0], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    lvl = 1;
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
                else
                {
                    lvl = 2;
                    SDL_BlitSurface(finish[1], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
            }
            else if (event.motion.x >= position[3].x && event.motion.x <= (position[3].x + 468) && event.motion.y >= position[3].y && event.motion.y <= position[3].y + 123)
            {
                c = 2;
                if (text[affich[c]] == Q)
                {
                    SDL_BlitSurface(finish[0], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    lvl = 1;
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
                else
                {
                    lvl = 2;
                    SDL_BlitSurface(finish[1], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
            }
            else if (event.motion.x >= position[4].x && event.motion.x <= (position[4].x + 468) && event.motion.y >= position[4].y && event.motion.y <= position[4].y + 123)
            {
                c = 3;
                if (text[affich[c]] == Q)
                {
                    SDL_BlitSurface(finish[0], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    lvl = 1;
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
                else
                {
                    lvl = 2;
                    SDL_BlitSurface(finish[1], NULL, screen, &pos);
                    SDL_BlitSurface(bout[2], NULL, screen, &cont);
                    SDL_Flip(screen);
                    f = 1;
                    while (f == 1)
                    {
                        SDL_WaitEvent(&event2);
                        switch (event2.type)
                        {
                        case SDL_MOUSEMOTION:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                SDL_BlitSurface(bout[3], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bout[2], NULL, screen, &cont);
                                SDL_Flip(screen);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event2.motion.x >= cont.x && event2.motion.x <= (cont.x + 273) && event2.motion.y >= cont.y && event2.motion.y <= cont.y + 138)
                            {
                                f = 0;
                                continuer = 0;
                            }
                        }
                    }
                }
            }
            break;
        }
    }

    fclose(ff);
    fclose(g);
    SDL_FreeSurface(background);
    for (i = 0; i < 8; i++)
    {
        SDL_FreeSurface(quest[i]);
        SDL_FreeSurface(answ[i]);
    }
    for (i = 0; i < 4; i++)
        SDL_FreeSurface(bout[i]);
    for (i = 2; i < 2; i++)
        SDL_FreeSurface(finish[i]);

    return lvl;
}

void afficherenigme(SDL_Surface *screen, char *a)
{
    SDL_Surface *background;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    background = IMG_Load(a);
    SDL_BlitSurface(background, NULL, screen, &pos);
}

int resolutionenigme(int resultat, int resultat2)
{
    if (resultat2 == resultat)
        return 1;
    else
    {
        return 2;
    }
}

clock_t initchrono(TTF_Font **police, SDL_Surface **black)
{
    clock_t debut;
    TTF_Init();
    (*police) = TTF_OpenFont("roboto.ttf", 65);
    if ((*police) == NULL)
        printf("police\n");
    (*black) = IMG_Load("blaka1.jpg");
    debut = clock();
    return debut;
}

int chrono(clock_t debut, SDL_Surface *screen, TTF_Font *police, SDL_Surface *black)
{
    clock_t fin;
    long clk_tck = CLOCKS_PER_SEC;
    int difference = 0;
    char temps[4];
    SDL_Surface *timee;
    SDL_Rect pos_clock, pos, pos1;
    SDL_Color couleurNoire = {0, 0, 0};

    pos1.x = 1459;
    pos1.y = 820;

    pos.x = 1459;
    pos.y = 820;

    fin = clock();
    difference = (int)(fin - debut) / (int)clk_tck;
    sprintf(temps, "%i", difference);
    timee = TTF_RenderText_Blended(police, temps, couleurNoire);
    SDL_BlitSurface(black, NULL, screen, &pos);
    SDL_BlitSurface(timee, NULL, screen, &pos1);
    SDL_Flip(screen);
    return difference;
}

int updatesticks(int sticks, SDL_Surface *screen, TTF_Font *police, SDL_Surface *black, int choix)
{
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Surface *stickss;
    SDL_Rect pos_clock, pos, pos1;
    char stick[3];
    pos1.x = 650;
    pos1.y = 200;

    pos.x = 650;
    pos.y = 150;

    sticks -= choix;
    sprintf(stick, "%i", sticks);
    stickss = TTF_RenderText_Blended(police, stick, couleurNoire);
    SDL_BlitSurface(black, NULL, screen, &pos);
    SDL_BlitSurface(stickss, NULL, screen, &pos1);
    SDL_Flip(screen);
    return sticks;
}

int winlose(SDL_Surface *screen, int player, SDL_Surface *win, SDL_Surface *lose, SDL_Surface *rules, SDL_Surface *continu[], SDL_Rect position,int *lvl)
{
    SDL_Event event;
    SDL_Rect pos;
    int a = 1;

    pos.x=1050;
    pos.y=750;

    while (a)
    {
        if (player == 0)
        {
            SDL_BlitSurface(rules, NULL, screen, &position);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    a = 0;
                    break;
                case SDL_MOUSEMOTION:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            SDL_BlitSurface(continu[1], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(continu[0], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            a=0;
                            return 1;
                        }
                        break;
                }
            }
        }
        else if (player %2 == 0)
        {
            SDL_BlitSurface(lose, NULL, screen, &position);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    a = 0;
                    break;
                case SDL_MOUSEMOTION:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            SDL_BlitSurface(continu[1], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(continu[0], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            a=0;
                            (*lvl)=2;
                            return 0;
                        }
                        break;
                }
            }
        }
        else
        {
            SDL_BlitSurface(win, NULL, screen, &position);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    a = 0;
                    break;
                case SDL_MOUSEMOTION:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            SDL_BlitSurface(continu[1], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        else
                        {
                            SDL_BlitSurface(continu[0], NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.motion.x >= pos.x && event.motion.x <= (pos.x + 273) && event.motion.y >= pos.y && event.motion.y <= pos.y + 138)
                        {
                            a=0;
                            (*lvl)=1;
                            return 0;
                        }
                        break;
                }
            }
        }
    }
}

int enigme4(SDL_Surface *screen)
{
    SDL_Surface *background, *bouton[12], *blaka, *blaka1, *bot, *win, *lose, *rules, *continu[2];
    SDL_Rect position, pos[6], botpos;
    TTF_Font *police = NULL;
    int lvl = 0, continuer = 1, i, wakt, sticks, choix, player = 0, a;
    SDL_Event event;
    clock_t debut;

    lose=IMG_Load("enigme4_lose.jpg");
    win=IMG_Load("enigme4_win.jpg");
    rules=IMG_Load("enigme4_rules.jpg");
    continu[0]=IMG_Load("4_continuer_not_pressed.png");
    continu[1]=IMG_Load("4_continuer_pressed.png");
    blaka = IMG_Load("blaka.jpg");
    bot = IMG_Load("bot.jpg");
    background = IMG_Load("enigme4.jpg");
    bouton[0] = IMG_Load("1_not_pressed.png");
    bouton[1] = IMG_Load("2_not_pressed.png");
    bouton[2] = IMG_Load("3_not_pressed.png");
    bouton[3] = IMG_Load("4_not_pressed.png");
    bouton[4] = IMG_Load("5_not_pressed.png");
    bouton[5] = IMG_Load("6_not_pressed.png");
    bouton[6] = IMG_Load("1_pressed.png");
    bouton[7] = IMG_Load("2_pressed.png");
    bouton[8] = IMG_Load("3_pressed.png");
    bouton[9] = IMG_Load("4_pressed.png");
    bouton[10] = IMG_Load("5_pressed.png");
    bouton[11] = IMG_Load("6_pressed.png");

    botpos.x = 300;
    botpos.y = 550;
    position.x = 0;
    position.y = 0;
    pos[0].x = 320;
    pos[0].y = 650;
    pos[1].x = 470;
    pos[1].y = 650;
    pos[2].x = 620;
    pos[2].y = 650;
    pos[3].x = 320;
    pos[3].y = 800;
    pos[4].x = 470;
    pos[4].y = 800;
    pos[5].x = 620;
    pos[5].y = 800;

    continuer=winlose(screen,player,win,lose,rules,continu,position,&lvl);
    SDL_BlitSurface(background, NULL, screen, &position);
    for (i = 0; i < 6; i++)
        SDL_BlitSurface(bouton[i], NULL, screen, &pos[i]);
    debut = initchrono(&police, &blaka1);
    srand(time(NULL));
    sticks = rand() % 40 + 20;

    SDL_Flip(screen);
    

    while (continuer)
    {

        wakt = chrono(debut, screen, police, blaka1);
        sticks = updatesticks(sticks, screen, police, blaka, 0);
        if (player % 2 == 1 && sticks > 0)
        {
            SDL_BlitSurface(bot, NULL, screen, &botpos);
            srand(time(NULL));
            a = rand() % 4 + 1;
            if (wakt > 4)
            {
                player++;
                if (sticks <= 6)
                    choix = sticks;
                else if (sticks <= 13 && sticks >7)
                    choix = sticks - 7;
                else
                {
                    srand(time(NULL));
                    choix = rand() % 6 + 1;
                }
                SDL_BlitSurface(background, NULL, screen, &position);
                for (i = 0; i < 6; i++)
                    SDL_BlitSurface(bouton[i], NULL, screen, &pos[i]);
                sticks = updatesticks(sticks, screen, police, blaka, choix);
                debut = clock();
            }
            else if (wakt == a)
            {
                player++;
                if (sticks <= 6)
                    choix = sticks;
                else if (sticks <= 13 && sticks >7)
                    choix = sticks - 7;
                else
                {
                    srand(time(NULL));
                    choix = rand() % 6 + 1;
                }
                SDL_BlitSurface(background, NULL, screen, &position);
                for (i = 0; i < 6; i++)
                    SDL_BlitSurface(bouton[i], NULL, screen, &pos[i]);
                sticks = updatesticks(sticks, screen, police, blaka, choix);
                debut = clock();
            }
        }
        else if (player % 2 == 0 && sticks > 0)
        {
            if (wakt > 5)
            {
                player++;
                srand(time(NULL));
                choix = rand() % 6 + 1;
                sticks = updatesticks(sticks, screen, police, blaka, choix);
                debut = clock();
            }
            else
            {
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_MOUSEMOTION:
                        for (i = 0; i < 6; i++)
                        {
                            if (event.motion.x >= pos[i].x && event.motion.x <= (pos[i].x + 108) && event.motion.y >= pos[i].y && event.motion.y <= pos[i].y + 98)
                            {
                                SDL_BlitSurface(bouton[i + 6], NULL, screen, &pos[i]);
                                SDL_Flip(screen);
                            }
                            else
                            {
                                SDL_BlitSurface(bouton[i], NULL, screen, &pos[i]);
                                SDL_Flip(screen);
                            }
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        for (i = 0; i < 6; i++)
                        {
                            if (event.motion.x >= pos[i].x && event.motion.x <= (pos[i].x + 108) && event.motion.y >= pos[i].y && event.motion.y <= pos[i].y + 98)
                            {
                                choix = i + 1;
                                player++;
                                debut = clock();
                                sticks = updatesticks(sticks, screen, police, blaka, choix);
                            }
                        }
                        break;
                    }
                }
            }
        }
        else
            continuer=winlose(screen,player,win,lose,rules,continu,position,&lvl);
    }

    return lvl;
}
