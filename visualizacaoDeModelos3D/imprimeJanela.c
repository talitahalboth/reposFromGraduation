#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <math.h>
#define angleChange 2

#include "imprimeJanela.h"
#define false 1==0
#define true !false

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Wireframe";
int what;

int delayconst;

void delay ()
{
 for ( int c = 0 ; c <= delayconst ; c++ )
       for (int d = 0 ; d <=delayconst; d++ )
       {}
}


void imprime ()
{
  what = 0;
	int a,b=0;
  double radz, rady,anguloz = 0 ,anguloy = 0;
	SDL_Init( SDL_INIT_VIDEO );

   SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, 
      SDL_HWSURFACE | SDL_DOUBLEBUF );
   SDL_WM_SetCaption( WINDOW_TITLE, 0 );

   SDL_Event event;
   int programaRodando = true;
   delayconst = 20000/(object.vsize);

       double xc = 0, yc = 0, zc= -100000, booleano = true, booleano2 = true;
   while (programaRodando)
   {

      perspectivaFraca (xc,yc,zc);
      convertePonto ();

      if (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)
         {
            programaRodando = false;
         }
      }

      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 00,0));


  // zc = max > 0 ? -sqrt (xc*xc+max*10000) : zc;
       //printf("%d\n", max*1000);
    for (int i = 1; i < object.vsize+1 ; ++i)
    {
      int j = 0;
      while(object.a[i][j])
      {
        lineRGBA(screen, 
        objEmpErspectiva[i-1].x, objEmpErspectiva[i-1].y,
        objEmpErspectiva[object.a[i][j]-1].x, objEmpErspectiva[object.a[i][j]-1].y, 
        30, 240, 255, 50);
        j++;

      }
    }
  
        if(SDL_PollEvent(&event)) 
         {
        if (event.type == SDL_MOUSEMOTION && what)
         {      
            

            if (event.motion.xrel < 0)
            {
              anguloy+=angleChange;;
              rady = anguloy/(180/M_PI);
              rotacionaY (rady);                 

            }
            if (event.motion.xrel > 0)
            {         
              anguloy-=angleChange;;
              rady = anguloy/(180/M_PI);
              rotacionaY (rady);
            }
           if (event.motion.yrel < 0)
            {
              anguloz+=angleChange;
              radz = anguloz/(180/M_PI);
              rotacionaX (radz);
            }
            if (event.motion.yrel > 0)
            {
              anguloz-=angleChange;
                    radz = anguloz/(180/M_PI);                                 
                    rotacionaX (radz);
            }
            if (event.type ==  SDL_MOUSEBUTTONUP)
            {
              what = 0;
            }
           }
          }
      SDL_Flip(screen);
  
      switch( event.type ){
            case SDL_MOUSEBUTTONDOWN:
            what = 1;   
            break;
             case SDL_MOUSEBUTTONUP:
             what = 0;   
            break;
            case SDL_KEYDOWN:
              delay ();
                switch( event.key.keysym.sym ){
                    case SDLK_UP:
                      anguloz-=angleChange;
                      radz = anguloz/(180/M_PI);                                 
                      rotacionaX (radz);
                       //xc --;
                      delay ();
                        break;
                    case SDLK_DOWN:
                      anguloz+=angleChange;;
                      radz = anguloz/(180/M_PI);
                      rotacionaX (radz);
                        //xc ++;
                        delay ();
                        break;
                    case SDLK_LEFT:
                      anguloy+=angleChange;;
                      rady = anguloy/(180/M_PI);
                      rotacionaY (rady);
                        //yc ++;
                        delay ();
                        break;
                    case SDLK_RIGHT:
                      anguloy-=angleChange;;
                      rady = anguloy/(180/M_PI);
                      rotacionaY (rady);
                       //yc --;
                       delay ();
                        break;
                    case 'q':
                      programaRodando = false;
                      break;
                    case SDLK_ESCAPE:
                      programaRodando = false;
                    default:
                      //delay ();
                        break;
                    }

          }
    
     

   }

   SDL_Quit();

}
