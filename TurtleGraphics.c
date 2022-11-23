https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include"MyLib-2.h"

typedef struct RGBcolour
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}RGBcolour;

bool leftMouseButtonDown = false;
bool leftMouseButtonUp = false;

ttlib ttdata;
ttlib *MyTurtle = &ttdata;

//import images function
void importImage(char *image, SDL_Window *window,SDL_Renderer *renderer, SDL_Rect pos)
{
        SDL_Surface *picture = IMG_Load(image);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, picture);
        SDL_RenderCopy(renderer, texture, NULL, &pos);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(picture);
}

/* source from Eike Anderson starts here; it originates from Eike Anderson's slide and it's to get the coulor of the pixel from where the mouse clicked*/
RGBcolour getPixelColour(SDL_Renderer *renderer,int width,int height,int x,int y)
{
    RGBcolour pcol;
    Uint32 pixels[10]; /* pixel and safety buffer (although 1 should be enough) */
    pcol.r=0;
    pcol.g=0;
    pcol.b=0;
    if(x>=0 && x<width && y>=0 && y<height) /* test if the coordinates are valid */
    {
        SDL_Rect rect; /* SDL rectangle of 1 pixel */
                        /* 2 helper structures to get SDL to generate the right pixel format */
        SDL_Surface *s = SDL_CreateRGBSurface(0,5,5,32,0,0,0,0); /* helper 1 */
        SDL_Surface *ns = SDL_ConvertSurfaceFormat(s,SDL_PIXELFORMAT_ARGB8888,0); /* 2 */
        rect.x=x;
        rect.y=y;
        rect.w=1;
        rect.h=1;
        /* renderer, pixel, target format, target array, safety value 5 (1 was needed) */
        if(!SDL_RenderReadPixels(renderer,&rect,SDL_PIXELFORMAT_ARGB8888,pixels,5))
        { /* pixel, pixel format (from helper 2), colour channels by reference */
            SDL_GetRGB(pixels[0],ns->format,&(pcol.r),&(pcol.g),&(pcol.b));
        }
        SDL_FreeSurface(s); /* free helper 1 */
        SDL_FreeSurface(ns); /* free helper 2 */
    }
    return pcol;
}
/* source from Eike Anderson ends here */

/* source from Eike Anderson starts here; it originates from Eike Anderson's slide and it's to check if the colors are the same*/
int sameColour(RGBcolour c1,RGBcolour c2)
{
    return((c1.r==c2.r) && (c1.g==c2.g) && (c1.b==c2.b));
}
/* source from Eike Anderson ends here */

/* source from Eike Anderson starts here; it originates from Eike Anderson's slide and it's to fill the source color with the destination color*/
void fill(SDL_Renderer *renderer,int wdth,int hght,int x,int y,RGBcolour src,RGBcolour dst)
{
    RGBcolour pcol;

    if (sameColour(src,dst)) return;

    pcol=getPixelColour(renderer,wdth,hght,x,y);
    if(!sameColour(src,pcol)) return;

    SDL_SetRenderDrawColor(renderer,dst.r,dst.g,dst.b,255);

    if (x>=0 && x<wdth && y>=0 && y<hght)
    {
        SDL_RenderDrawPoint(renderer,x,y);
    }
    else return;
}
/* source from Eike Anderson ends here */

/*void drawing_lines(SDL_Renderer *renderer,int width,int height,int x0,int y0,int xn,int yn,RGBcolour col)
{
	int dx = abs(xn-x0),sx = x0<xn ? 1:-1;
	int dy = abs(yn-y0),sy = y0<yn ? 1:-1;
	int error = (dx>dy ? dx : -dy)/2,e2;
	int stop_flag3=1;
	
	SDL_SetRenderDrawColor(render,col.r,col.g,col.b,255);
	while(stop_flag3)
	{
		if(x0>=0)
	}
}*/

//current(x,y)position
SDL_Rect point;

//declaring a bg surface
SDL_Surface *s;

int main(void)
{
    int winPosX = 100;
    int winPosY = 100;
    int winWidth = 1100;
    int winHeight = 1100;
    int go;
    printf("aaaaaaaaaaaaaaaaa\n")
    //create a window
    if( SDL_Init( SDL_INIT_EVERYTHING )!=0)
    {
        fprintf(stderr, "SDL init failed\n");
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("MyTurtle",winPosX,winPosY,
                                                    winWidth,winHeight,
                                                    SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture_button = SDL_CreateTexture(renderer,  SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1100, 1100);
    SDL_Texture * texture_draw = SDL_CreateTexture(renderer,  SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1100, 1100);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
    printf("BBBBBBBBBBBBBBBBBBBB")
    //current (x,y) point pos
    point.x = 550;
	point.y = 525;
	point.w = 10;
	point.h = 10;

    //initialize some variables
    int x0 = 550;
    int y0 = 525;
    int xn = 550;
    int yn = 525;
    ttdata.angle = 90;
    ttdata.heading = 0.0;
    ttdata.lines = 3;
    ttdata.repetition = 3;
    ttdata.penup = false;
    ttdata.pendown = true;
    printf("CCCCCCCCCCCCCCCCC\n")
    //pen colors
    RGBcolour red = {255,0,0};
    RGBcolour yellow = {255,255,0};
    RGBcolour blue = {0,0,255};
    RGBcolour green = {0,128,0};
    RGBcolour purple = {128,0,128};
    RGBcolour black = {0,0,0};
    RGBcolour drawCol = black;

    //background colors
    RGBcolour white = {255,255,255};
    RGBcolour pink = {255,204,229};
    RGBcolour sky = {204,229,255};
    RGBcolour grass = {204,255,153};
    //bg surface
    s = SDL_CreateRGBSurface(0, 1100, 1050, 32, 0, 0, 0,0);

    //store all the coordinates
    SDL_Rect window_rect={0,0,1100,1050};
    SDL_Rect draw_pos={0,50,1100,1100};
    SDL_Rect red_pos={0,0,50,50};  //x,y,width,height
    SDL_Rect yellow_pos={50,0,50,50};
    SDL_Rect blue_pos={100,0,50,50};
    SDL_Rect green_pos={150,0,50,50};
    SDL_Rect purple_pos={200,0,50,50};
    SDL_Rect black_pos={250,0,50,50};

    SDL_Rect white_pos={330,0,50,50};
    SDL_Rect pink_pos={380,0,50,50};
    SDL_Rect sky_pos={430,0,50,50};
    SDL_Rect grass_pos={480,0,50,50};

    SDL_Rect length_pos={560,0,50,50};
    SDL_Rect plus0_pos={610,0,25,25};
    SDL_Rect minus0_pos={610,25,25,25};
    SDL_Rect lines_pos={635,0,50,50};
    SDL_Rect plus1_pos={685,0,25,25};
    SDL_Rect minus1_pos={685,25,25,25};
    SDL_Rect turning_pos={710,0,50,50};
    SDL_Rect plus2_pos={760,0,25,25};
    SDL_Rect minus2_pos={760,25,25,25};
    SDL_Rect repetition_pos={785,0,50,50};
    SDL_Rect plus3_pos={835,0,25,25};
    SDL_Rect minus3_pos={835,25,25,25};
    SDL_Rect save_pos={860,0,50,50};

    //load images for buttons
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, texture_button);

    importImage("./icon/red.jpg",window,renderer,red_pos);
    importImage("./icon/yellow.jpg",window,renderer,yellow_pos);
    importImage("./icon/blue.jpg",window,renderer,blue_pos);
    importImage("./icon/green.jpg",window,renderer,green_pos);
    importImage("./icon/purple.jpg",window,renderer,purple_pos);
    importImage("./icon/black.jpg",window,renderer,black_pos);

    importImage("./icon/white.jpg",window,renderer,white_pos);
    importImage("./icon/pink.jpg",window,renderer,pink_pos);
    importImage("./icon/sky.jpg",window,renderer,sky_pos);
    importImage("./icon/grass.jpg",window,renderer,grass_pos);

    importImage("./icon/length.jpg",window,renderer,length_pos);
    importImage("./icon/plus0.jpg",window,renderer,plus0_pos);
    importImage("./icon/minus0.jpg",window,renderer,minus0_pos);
    importImage("./icon/lines.jpg",window,renderer,lines_pos);
    importImage("./icon/plus1.jpg",window,renderer,plus1_pos);
    importImage("./icon/minus1.jpg",window,renderer,minus1_pos);
    importImage("./icon/turning.jpg",window,renderer,turning_pos);
    importImage("./icon/plus2.jpg",window,renderer,plus2_pos);
    importImage("./icon/minus2.jpg",window,renderer,minus2_pos);
    importImage("./icon/repetition.jpg",window,renderer,repetition_pos);
    importImage("./icon/plus3.jpg",window,renderer,plus3_pos);
    importImage("./icon/minus3.jpg",window,renderer,minus3_pos);
    importImage("./icon/save.jpg",window,renderer,save_pos);

    SDL_RenderCopy(renderer, texture_button, NULL, NULL);

    //create white drawing space
    SDL_SetRenderTarget(renderer, texture_draw);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,NULL);
    SDL_SetRenderTarget(renderer, NULL);

    go=1;
    while(go)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        //update pixel texture
        //SDL_UpdateTexture(texture_draw, NULL, pixels, 640 * sizeof(Uint32));
        //retrieve mouse positions
        
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        leftMouseButtonUp=false;
        
        switch(event.type)
        {
			case SDL_MOUSEBUTTONDOWN:
                leftMouseButtonUp=false;
                leftMouseButtonDown=true;
                //drawing pen Col button
                if (mouseX>=red_pos.x && mouseX<=red_pos.x + red_pos.w && mouseY>=red_pos.y && mouseY<=red_pos.y + red_pos.h)
                {
                    printf("red clicked\n");
                    drawCol = red;
                    break;
                }//red pen
                if (mouseX>=yellow_pos.x && mouseX<=yellow_pos.x + yellow_pos.w && mouseY>=yellow_pos.y && mouseY<=yellow_pos.y + yellow_pos.h)
                {
                    printf("yellow clicked\n");
                    drawCol = yellow;
                    break;
                }//yellow pen
                if (mouseX>=blue_pos.x && mouseX<=blue_pos.x + blue_pos.w && mouseY>=blue_pos.y && mouseY<=blue_pos.y + blue_pos.h)
                {
                    printf("blue clicked\n");
                    drawCol = blue;
                    break;
                }//blue pen
                if (mouseX>=green_pos.x && mouseX<=green_pos.x + green_pos.w && mouseY>=green_pos.y && mouseY<=green_pos.y + green_pos.h)
                {
                    printf("green clicked\n");
                    drawCol = green;
                    break;
                }//green pen
                if (mouseX>=purple_pos.x && mouseX<=purple_pos.x + purple_pos.w && mouseY>=purple_pos.y && mouseY<=purple_pos.y + purple_pos.h)
                {
                    printf("purple clicked\n");
                    drawCol = purple;
                    break;
                }//purple pen
                if (mouseX>=black_pos.x && mouseX<=black_pos.x + black_pos.w && mouseY>=black_pos.y && mouseY<=black_pos.y + black_pos.h)
                {
                    printf("black clicked\n");
                    drawCol = black;
                    break;
                }//black pen
                
                //bgCol button
                if (mouseX>=white_pos.x && mouseX<=white_pos.x + white_pos.w && mouseY>=white_pos.y && mouseY<=white_pos.y + white_pos.h)
                {
                    printf("white clicked\n");
                    SDL_FillRect(s,NULL, SDL_MapRGB(s->format,255,255,255));
                    texture_draw = SDL_CreateTextureFromSurface(renderer,s);
                    break;
                }//white bg
                if (mouseX>=pink_pos.x && mouseX<=pink_pos.x + pink_pos.w && mouseY>=pink_pos.y && mouseY<=pink_pos.y + pink_pos.h)
                {
                    printf("pink clicked\n");
                    SDL_FillRect(s,NULL, SDL_MapRGB(s->format,255,204,229));
                    texture_draw = SDL_CreateTextureFromSurface(renderer,s);
                    break;
                }//pink bg
                if (mouseX>=sky_pos.x && mouseX<=sky_pos.x + sky_pos.w && mouseY>=sky_pos.y && mouseY<=sky_pos.y + sky_pos.h)
                {
                    printf("sky clicked\n");
                    SDL_FillRect(s,NULL, SDL_MapRGB(s->format,204,229,255));
                    texture_draw = SDL_CreateTextureFromSurface(renderer,s);
                    break;
                }//sky bg
                if (mouseX>=grass_pos.x && mouseX<=grass_pos.x + grass_pos.w && mouseY>=grass_pos.y && mouseY<=grass_pos.y + grass_pos.h)
                {
                    printf("grass clicked\n");
                    SDL_FillRect(s,NULL, SDL_MapRGB(s->format,204,255,153));
                    texture_draw = SDL_CreateTextureFromSurface(renderer,s);
                    break;
                }//grass bg

                if (mouseX>=plus0_pos.x && mouseX<=plus0_pos.x + plus0_pos.w && mouseY>=plus0_pos.y && mouseY<=plus0_pos.y + plus0_pos.h)
                {
                        printf("go forward clicked\n");
                }
                if (mouseX>=minus0_pos.x && mouseX<=minus0_pos.x + minus0_pos.w && mouseY>=minus0_pos.y && mouseY<=minus0_pos.y + minus0_pos.h)
                {
                        printf("go backward clicked\n");
                }
                //length+-

                if (mouseX>=plus1_pos.x && mouseX<=plus1_pos.x + plus1_pos.w && mouseY>=plus1_pos.y && mouseY<=plus1_pos.y + plus1_pos.h)
                {
                        printf("lines plus clicked\n");
                }
                if (mouseX>=minus1_pos.x && mouseX<=minus1_pos.x + minus1_pos.w && mouseY>=minus1_pos.y && mouseY<=minus1_pos.y + minus1_pos.h)
                {
                        printf("lines minus clicked\n");
                }
                //lines+-

                if (mouseX>=plus2_pos.x && mouseX<=plus2_pos.x + plus2_pos.w && mouseY>=plus2_pos.y && mouseY<=plus2_pos.y + plus2_pos.h)
                {
                        printf("turning plus clicked\n");
                }
                if (mouseX>=minus2_pos.x && mouseX<=minus2_pos.x + minus2_pos.w && mouseY>=minus2_pos.y && mouseY<=minus2_pos.y + minus2_pos.h)
                {
                        printf("turning minus clicked\n");
                }
                //angle+-

                if (mouseX>=plus3_pos.x && mouseX<=plus3_pos.x + plus3_pos.w && mouseY>=plus3_pos.y && mouseY<=plus3_pos.y + plus3_pos.h)
                {
                        printf("repetition plus clicked\n");
                }
                if (mouseX>=minus3_pos.x && mouseX<=minus3_pos.x + minus3_pos.w && mouseY>=minus3_pos.y && mouseY<=minus3_pos.y + minus3_pos.h)
                {
                        printf("repetition minus clicked\n");
                }
                //repetition+-

               /* if (mouseX>=save_pos.x && mouseX<=save_pos.x + save_pos.w && mouseY>=save_pos.y && mouseY<=save_pos.y + save_pos.h)
                {
                    printf("save clicked\n");
                    currenttool = SAVE;
                    Uint32 * save_pixels[winWidth * winHeight-50];
                    //cut the drawing board from the renderer to save_pixels
                    SDL_RenderReadPixels(renderer,&draw_pos,SDL_PIXELFORMAT_ARGB8888,save_pixels,winWidth * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_ARGB8888));
                    //create a surface from the save_pixels
                    SDL_Surface *save_surface = SDL_CreateRGBSurfaceFrom(save_pixels, winWidth, winHeight-50, SDL_BITSPERPIXEL(SDL_PIXELFORMAT_ARGB8888), winWidth * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_ARGB8888), 0,0,0,0);
                    IMG_SavePNG(save_surface,"saved.png");
                    SDL_FreeSurface(save_surface);
                    
                    break;
                }//save img */

                case SDL_MOUSEMOTION:
                    if (leftMouseButtonDown)
                    {
                        SDL_SetRenderTarget(renderer, texture_draw);


                        SDL_SetRenderTarget(renderer, NULL);
                
                    }
                    break;

                    case SDL_QUIT:
                        go = 0;
                        break;    	
		        }

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture_button, NULL, NULL);
                SDL_RenderCopy(renderer, texture_draw, NULL, &draw_pos);
                SDL_RenderPresent(renderer);

        }
        SDL_DestroyTexture(texture_button);
        SDL_DestroyTexture(texture_draw);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
}
