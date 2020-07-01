/**
* @file enigmes.h
* @brief toutes les enigmes
* @author Mohamed Ali Bouzaiene
* @version 0.0.1
*/

#ifndef ENIGMES_H_INCLUDED
#define ENIGMES_H_INCLUDED


void afficherenigme(SDL_Surface* screen, char* a);
/**
* @brief affichage enigme
*/
int resolutionenigme(int resultat,int resultat2);
/**
* @brief resultat enigme
*/

clock_t initchrono(TTF_Font **police,SDL_Surface **black);
/**
* @brief initialisation du chronometre pour les enigmes
*/
int chrono(clock_t debut, SDL_Surface *screen,TTF_Font *police,SDL_Surface *black);
/**
* @brief l'affichage du chronometre
*/

int updatesticks(int sticks,SDL_Surface* screen,TTF_Font *police, SDL_Surface *black,int choix);//pour enigme4
/**
* @brief pour l enigme4
*/
int winlose(SDL_Surface *screen, int player, SDL_Surface *win, SDL_Surface *lose, SDL_Surface *rules, SDL_Surface *continu[], SDL_Rect position,int *lvl);//enigme4 aussi
/**
* @brief pour enigme4
*/
int enigme1(SDL_Surface* screen);//generation automatique d une reponse et d une question
/**
* @brief enigme 1 math random
*/
int enigme2(SDL_Surface* screen);//resultat precis
/**
* @brief enigme 2 panda
*/
int enigme3(SDL_Surface* screen);//generation aleatoire apartir d un ficher
/**
* @brief enigme 3 des question apartir d'un fichier
*/
int enigme4(SDL_Surface* screen);//contre bot et mini game
/**
* @brief enigme 4 minigame du batons contre un bot
*/


#endif