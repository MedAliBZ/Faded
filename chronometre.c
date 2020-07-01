clock_t initchrono()
{
    clock_t debut;
    debut = clock();
    return debut;
}

int chrono(int debut)
{
    clock_t fin;
    long clk_tck = CLOCKS_PER_SEC;
    int difference = 0;
    char temps[4];
    SDL_Surface *timee, *black;

    black = IMG_Load("test/blaka.png");
    fin = clock();
    difference = (int)(fin - debut) / (int)clk_tck;
    sprintf(temps, "%i", difference);
    timee = TTF_RenderText_Blended(police, temps, couleurblanc);
    SDL_BlitSurface(black, NULL, screen, &pos);
    SDL_BlitSurface(timee, NULL, screen, &pos);
    SDL_Flip(screen);
        return difference;
}
