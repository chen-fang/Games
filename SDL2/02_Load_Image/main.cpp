#include <SDL2/SDL.h>
#include <iostream>

int main()
{
   const int screenWidth = 640;
   const int screenHeight= 480;
   
   bool success;

   SDL_Window*  window        = NULL;
   SDL_Surface* screenSurface = NULL;
   SDL_Surface* imageSurface  = NULL;
   
   // Initialize SDL
   int flag_sdl_init = SDL_Init( SDL_INIT_VIDEO );
   if( flag_sdl_init < 0 )
   {
      success = false;
      printf( "SDL Initialization failed. SDL_Error: %s\n", SDL_GetError() );
   }
   else
   {
      // create window & surface
      window = SDL_CreateWindow( "Load Image Test",
				 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				 screenWidth, screenHeight, SDL_WINDOW_SHOWN );

      if( window == NULL )
      {
	 success = false;
	 printf( "Window is not created. SDL_Error: %s\n", SDL_GetError() );
      }
      else
      {
	 screenSurface = SDL_GetWindowSurface( window );
	 success = true;
      }
   }

   // Load Image
   if( success == true )
   {
      imageSurface = SDL_LoadBMP( "LaoPo.bmp" );
      if( imageSurface == NULL )
      {
	 printf( "Image is not loaded. SDL_Error: %s\n", SDL_GetError() );
	 success = false;
      }
   }

   // Apply Image
   if( success == true )
   {
      SDL_BlitSurface( imageSurface, NULL, screenSurface, NULL );
      SDL_UpdateWindowSurface( window );
      SDL_Delay( 2000 );
   }

   // close
   SDL_FreeSurface( imageSurface );
   SDL_DestroyWindow( window );
   SDL_Quit();
   
   return 0;
}
