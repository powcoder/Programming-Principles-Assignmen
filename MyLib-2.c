https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"MyLib-2.h"

#define PI 3.14159

void penup(ttlib *mytt)
{
    mytt->pendown = false;
}//not drawing

void pendown(ttlib *mytt)
{
    mytt->penup = true;
}//drawing

void turning(ttlib *mytt)
{
    double angle = (double)mytt->heading;
    mytt->heading = (180.0*angle)/PI;
}//turning angle into rad(heading)\

void repetition(ttlib *mytt)
{
    int A0 = 360;//sum of the interior angles of a triangle
    int A1 = 180-(mytt->angle);//direction angle
    int total_A2 = A1 * lines;//sum of the interior angles of the turtle
    lines (ttlib *mytt->lines);
    int temp1;
    int temp2;
    int i;//LCM

    while(1)
    {
        temp1 = (A0>total_A2)?total_A2:A0;
        while((A0%temp1 != 0) || (total_A2%temp1 != 0))
        {
            temp1--;
        }
        printf("GCD id: %d\n",temp1);
        break;
    }//calculate GCD

    if(A0<total_A2)
    {
        temp2 = A0;
        A0 = total_A2;
        total_A2 = temp2;
    }
    for (i=A0; i>0; i++)
        if (i%A0==0 && i%total_A2==0)
        {
            printf("LCM is:%d\n",i);
            break;
        }//calculate LCM

    if (temp1 - (int)temp1 == 0 || i - (int)i == 0)
        {
            mytt->repetition = i/total_A2;
        }
    else
        printf("It is not a spirolateral!\n");
    //calculate repetition
}

void forward(ttlib *mytt,int unit)//lines+
{
    double FWxmove = 0.0;
    double FWymove = 0.0;//go forward

    if (mytt->penup == 0)
    {
        FWxmove = unit * cos(mytt->heading);
        FWymove = unit * sin(mytt->heading);
        //calculate final position

        mytt->xn0 = mytt->x0+round(FWxmove);
        mytt->yn0 = mytt->y0+round(FWymove);//round for getting integer

        if(mytt->xn<0||mytt->xn>1100||mytt->yn<50||mytt->yn>1050)
        {
            printf("Out of drwaing space\n");
        }
        else
        {
            mytt->x0 = mytt->xn;
            mytt->y0 = mytt->yn;
        }
    }//if pen up, determine a heading direction first

    if (mytt->pendown == 1)
    {
        int sx,sy;//starting point
        int vx,vy;//varying coordinates
        double A3;

        int r;//repeat
        int l;//num of turns(lines)
        int i;//unit
        int distance;

        A3 = 180.0 - (double)(mytt->angle);
        int total = (mytt->repetition)*(mytt->turning)*(mytt->lines);

        int stop_flag0 = 1;

        int xn,x0;
        int yn,y0;
        int error, e2;

        for(r=0;r<(mytt->repetition);r++)
        {
            for(l=1;l<=(mytt->lines);l++)
            {
                distance = i*(mytt->unit);
                FWxmove = (distance * cos(fabs(A3*(r*(mytt->lines)+l)*180.0)))/PI;
                FWymove = (distance * sin(fabs(A3*(r*(mytt->lines)+l)*180.0)))/PI;

                /* source from Eike Anderson starts here; it originates from Eike Anderson's slide and it's to draw the line by determine the start point and the end point*/
                mytt->xn0 = mytt->x0+round(FWxmove);
                mytt->yn0 = mytt->y0+round(FWymove);

                vx = abs(xn-x0), sx = x0<xn ? 1:-1;
                vx = abs(yn-y0), sy = y0<yn ? 1:-1;
                error = (vx>vy ? vx : -vy)/2, e2;

                while(stop_flag0)
                {
                    if(x0>=0 && x0<1100 && y0>=0 && y0<1050)
                    {
                        if(x0==xn && y0==yn) break;
                        e2 = error;
                        if(e2 >-vx) { error -= vy; x0 += sx; }
                        if(e2 < vy) { error += vx; y0 += sy; }
                    }
                    else
                    {
                        printf("Out of drwaing space\n");
                        stop_flag0 = 0;
                    }
                }/* source from Eike Anderson ends here */
            }//lines
        }//repeat loop

    }//if pen down, draw forward
}

void backward(ttlib *mytt, int unit)//lines-
{
    double BWxmove = 0.0;
    double BWymove = 0.0;//go backward

    if (mytt->penup == 0)
    {
        BWxmove -= unit * cos(mytt->heading);
        BWymove -= unit * sin(mytt->heading);
        //calculate final position

        mytt->xn1 = mytt->x0-round(BWxmove);
        mytt->yn1 = mytt->y0-round(BWymove);//round for getting integer

        if(mytt->xn<0||mytt->xn>1100||mytt->yn<50||mytt->yn>1050)
        {
            print("Out of drwaing space\n");
        }
        else
        {
            mytt->x0 = mytt->xn;
            mytt->y0 = mytt->yn;
        }
    }//if pen up, determine a heading direction first

    if (mytt->pendown == 1)
    {
        int sx,sy;//starting point
        int vx,vy;//varying coordinates
        double A3;

        int r;//repeat
        int l;//num of turns(lines)
        int i;//unit
        int distance;

        A3 = 180.0 - (double)(mytt->angle);
        int total = (mytt->repetition)*(mytt->turning)*(mytt->lines);

        int stop_flag1 = 0;

        int xn,x0;
        int yn,y0;
        int error, e2;

        for(r=0;r<(mytt->repetition);r++)
        {
            for(l=1;l<=(mytt->lines);l++)
            {
                distance = i*(mytt->unit);
                BWxmove = -(distance * cos(fabs(A3*(r*(mytt->lines)+l)*180.0)))/PI;
                BWymove = -(distance * sin(fabs(A3*(r*(mytt->lines)+l)*180.0)))/PI;

                /* source from Eike Anderson starts here; it originates from Eike Anderson's slide and it's to draw the line by determine the start point and the end point*/
                mytt->xn1 = mytt->x0-round(BWxmove);
                mytt->yn1 = mytt->y0-round(BWymove);

                vx = abs(xn-x0), sx = x0<xn ? 1:-1;
                vx = abs(yn-y0), sy = y0<yn ? 1:-1;
                error = (vx>vy ? vx : -vy)/2, e2;

                while(stop_flag1)
                {
                    if(x0>=0 && x0<1100 && y0>=0 && y0<1050)
                    {
                        if(x0==xn && y0==yn) break;
                        e2 = error;
                        if(e2 >-vx) { error -= vy; x0 += sx; }
                        if(e2 < vy) { error += vx; y0 += sy; }
                    }
                    else
                    {
                        printf("Out of drwaing space\n");
                        stop_flag1=0;
                    }
                }/* source from Eike Anderson ends here */
            }//lines
        }//repeat loop
    }//if pen down, draw backward
}
