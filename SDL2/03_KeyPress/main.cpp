#include <SDL2/SDL.h>
#include <iostream>

const int screenWidth = 640;
const int screenHeight= 480;

enum KeyPress
{
   KEY_PRESS_DEFAULT, // 0
   KEY_PRESS_UP,      // 1
   KEY_PRESS_DOWN,    // 2
   KEY_PRESS_LEFT,    // 3
   KEY_PRESS_RIGHT,   // 4
   KEY_PRESS_TOTAL    // 5
};
   
SDL_Window*  window        = NULL;
SDL_Surface* screenSurface = NULL;


bool init()
{
   int flag_sdl = SDL_Init( SDL_INIT_VIDEO );
   if( flag_sdl < 0 )
   {
      printf( "SDL Initialization failed. SDL_Error: %s\n", SDL_GetError() );
      return false;
   }
   window = SDL_CreateWindow( "Key Press", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			      screenWidth, screenHeight, SDL_WINDOW_SHOWN );
   if( window == NULL )
   {
      printf( "Window is not created. SDL_Error: %s\n", SDL_GetError() );
      return false;
   }
   screenSurface = SDL_GetWindowSurface( window );
   return true;
}

// Storage of images
SDL_Surface* imageSurface[ KEY_PRESS_TOTAL ];

// Load all images
bool LoadMedia()
{
   std::string path;
   
   // default
   path = "BMPs/LaoPo.bmp";
   imageSurface[ KEY_PRESS_DEFAULT ] = SDL_LoadBMP( path.c_str() );
   if( imageSurface[ KEY_PRESS_DEFAULT ] == NULL )
   {
      printf( "Failed to load default image...SDL_Error: %s\n", SDL_GetError() );
      return false;
   }

   // up
   path = "BMPs/Up.bmp";
   imageSurface[ KEY_PRESS_UP ] = SDL_LoadBMP( path.c_str() );
   if( imageSurface[ KEY_PRESS_UP ]  == NULL )
   {
      printf( "Failed to load up image...SDL_Error: %s\n", SDL_GetError() );
      return false;
   }

   // down
   path = "BMPs/Down.bmp";
   imageSurface[ KEY_PRESS_DOWN ] = SDL_LoadBMP( path.c_str() );
   if( imageSurface[ KEY_PRESS_DOWN ]  == NULL )
   {
      printf( "Failed to load down image...SDL_Error: %s\n", SDL_GetError() );
      return false;
   }

   // left
   path = "BMPs/Left.bmp";
   imageSurface[ KEY_PRESS_LEFT ] = SDL_LoadBMP( path.c_str() );
   if( imageSurface[ KEY_PRESS_LEFT ]  == NULL )
   {
      printf( "Failed to load left image...SDL_Error: %s\n", SDL_GetError() );
      return false;
   }

   // right
   path = "BMPs/Right.bmp";
   imageSurface[ KEY_PRESS_RIGHT ] = SDL_LoadBMP( path.c_str() );
   if( imageSurface[ KEY_PRESS_RIGHT ]  == NULL )
   {
      printf( "Failed to load right image...SDL_Error: %s\n", SDL_GetError() );
      return false;
   }

   return true;
}

void close()
{
   for( int i = 0; i < KEY_PRESS_TOTAL; ++i )
   {
      SDL_FreeSurface( imageSurface[i] );
   }
   SDL_DestroyWindow( window  );
   SDL_Quit();
}

int main()
{
   bool success;

      
   success = init();
   if( success == false ) return -1;

   success = LoadMedia();
   if( success == false ) return -1;

   // Main loop flag
   bool quit = false;
   
   // Event handler
   SDL_Event e;

   SDL_Surface* pImage = imageSurface[ KEY_PRESS_DEFAULT ];


   // main loop
   while( quit == false )
   {
      // event queue
      while( SDL_PollEvent( &e ) != 0 )
      {
	 printf( "here\n" );

	 // x-out
	 if( e.type == SDL_QUIT )
	 {
	    quit = true;
	 }
	 else if( e.type == SDL_KEYDOWN )
	 {
	    switch( e.key.keysym.sym )
	    {
	       case SDLK_ESCAPE:
		  quit = true;
		  break;
		  
	       case SDLK_UP:
		  pImage = imageSurface[ KEY_PRESS_UP ];
		  break;

	       case SDLK_DOWN:
		  pImage = imageSurface[ KEY_PRESS_DOWN ];
		  break;

	       case SDLK_RIGHT:
		  pImage = imageSurface[ KEY_PRESS_RIGHT ];
		  break;

	       case SDLK_LEFT:
		  pImage = imageSurface[ KEY_PRESS_LEFT ];
		  break;

	       default:
		  pImage = imageSurface[ KEY_PRESS_DEFAULT ];
		  break;
	    }
	 }
      }
      // Apply image
      SDL_BlitSurface( pImage, NULL, screenSurface, NULL );
      SDL_UpdateWindowSurface( window );
   }

   close();
   
   return 0;
}
