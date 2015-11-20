#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>
////////////////////////////////////////////////////////////////////////////
struct oyuncular
{
	int x,y;
	int puan;
};
struct oyuncular oyuncu1,oyuncu2,*suan;
int i,m,j,n,z,k,c;
int tepeler[9][2];
float a[180],b[180];
int dizi_puan[50];
int sira=0;

void kordinat(float,float,float);
void Baslat();
void Bitir();
void bina_ciz(BITMAP *);
void top_at(BITMAP *);
void duraklat();
void ana_menu();
void puanlar();
void yuksek_puan_yaz();
void yuksek_puan_oku();

////////////////////////////////////////////////////////////////////////////
int main() 
{
		

	    for(i=0;i<=8;i++)
			{
				tepeler[i][1]=0;
				tepeler[i][2]=0;

			}
		Baslat();
		ana_menu();
		rest(-1);	
		Bitir();
		return 0;
}
////////////////////////////////////////////////////////////////////////////
		
END_OF_MAIN()

////////////////////////////////////////////////////////////////////////////
void Baslat() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1300, 680, 0, 0);
	
	if (res != 0) 
	{
	    allegro_message(allegro_error);
    	exit(-1);
	}
	
	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"A");
}
////////////////////////////////////////////////////////////////////////////

void Bitir() 
{

	clear_keybuf();
 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

	void bina_ciz(BITMAP *binalar)
	{
	
    	BITMAP *tugla=load_bitmap("images/tugla.bmp",NULL);
    	clear_to_color(binalar,makecol(255,0,255));
    	srand(time(NULL));
    	int yukseklik=rand()%10+4;
    	int genislik=rand()%4+4;
    	int x1=0,y1=660,x,y;

    	int k=0;
	
    	while(x1+genislik*20<1250)
    	{
        	x=x1;
        	y=y1;
		

	       	for(m=1;m<=yukseklik;m++)
	       	{

	       	   	x=x1;
			    for(j=1;j<=genislik;j++)
		      	{
			
			     	blit(tugla,binalar,0,0,x=x+20,y,1300,680);

			     }
		
			y=y-20;

		}


		if(k<4)
		{
			tepeler[k][1]=x-60;
			tepeler[k][2]=y;
		}

		if(k>=4)
		{

			for(n=8;n>=5;n--)
			{



				tepeler[n][1]=tepeler[n-1][1];
				tepeler[n][2]=tepeler[n-1][2];


			}


			tepeler[4][1]=x-10;
			tepeler[4][2]=y;


		}

		

		y1=660;
		x1=x1+genislik*20+10;
		genislik=rand()%4+4;
		yukseklik=rand()%10+4;

		k++;
	}


	int oyuncu_bina=rand()%4;
	oyuncu1.x=tepeler[oyuncu_bina][1];
	oyuncu1.y=tepeler[oyuncu_bina][2];
	oyuncu_bina=rand()%4+4;
	oyuncu2.x=tepeler[oyuncu_bina][1];
	oyuncu2.y=tepeler[oyuncu_bina][2];


	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

	void top_at(BITMAP *binalar)
	{
		
		BITMAP *arkaplan=load_bitmap("images/arkaplan.bmp",NULL);
		
		time_t bas,son;
		
		int aci,hiz=0;
		int x,y;
		int hiz_gos_x=550,hiz_gos_y=100;
		
		BITMAP *yuksek=load_bitmap("images/yuksek.bmp",NULL);
		SAMPLE *ses1=load_sample("sound/islem.wav");
		SAMPLE *avur=load_sample("sound/avur.wav");
		SAMPLE *bvur=load_sample("sound/bvur.wav");
		BITMAP *adam1=load_bitmap("images/adam1.bmp",NULL);
		BITMAP *adam2=load_bitmap("images/adam2.bmp",NULL);
		BITMAP *binalar2=create_bitmap(1300,680);
		BITMAP *arka=create_bitmap(1300,680);
		BITMAP *ok=load_bitmap("images/ok.bmp",NULL);
		BITMAP *top=load_bitmap("images/top.bmp",NULL);
		BITMAP *adamlar=create_bitmap(1300,680);
		BITMAP *ruzgar_sag=load_bitmap("images/ruzgar_sag.bmp",NULL);
		BITMAP *ruzgar_sol=load_bitmap("images/ruzgar_sol.bmp",NULL);

		clear_to_color(adamlar,makecol(255,0,255));

		blit(binalar,binalar2,0,0,00,00,1300,680);

		int sure_sinir=15,kalan_zaman;
		int renk;
		int ruzgar_hiz;
		int ruzgar_yon;
		for(z=0;z<=5;z++)
		{
			ruzgar_hiz=rand()%3+1;
			ruzgar_yon=rand()%2;

			hiz=0;
			if(z%2!=0)
			{
				renk=makecol(0,162,232);
				suan=&oyuncu1;
				aci=45;
			}

			else if(z%2==0)
			{
				
				renk=makecol(237,28,36);
				suan=&oyuncu2;
				aci=135;
			
			}
			
				

			x=suan->x;
			y=suan->y;
			
            sure_sinir=15;
			time(&bas);

			while (!key[KEY_ENTER]) 
			{
				time(&son);
				kalan_zaman=sure_sinir-difftime(son,bas);
				if(difftime(son,bas)==sure_sinir)
				{
				
					goto git;
					

				}

				if(key[KEY_UP])
				{

					aci++;

				}

                if(key[KEY_ESC])
				{
                   
                    sure_sinir=kalan_zaman;
                    duraklat();
                    time(&bas);
                    time(&son);
     
				}


				if(key[KEY_DOWN])
				{

					aci--;
	
				}

				if(aci<0)
				{
					aci+=360;
				}

				aci=aci%360;

				if(key[KEY_RIGHT])
				{

					hiz++;
					if(hiz>20)
					{
						hiz=20;
				
					}

				}

				if(key[KEY_LEFT])
				{
					hiz--;

					if(hiz<0)
					{
						hiz=0;
					}

				}


				draw_sprite(arka,arkaplan,0,0);
				draw_sprite(arka,binalar2,0,0);
		
				draw_sprite(adamlar,adam1,oyuncu1.x-8,oyuncu1.y-91);
				draw_sprite(adamlar,adam2,oyuncu2.x-8,oyuncu2.y-91);
		
				draw_sprite(arka,adamlar,0,0);


				rotate_sprite(arka,ok,x-35,y,ftofix(aci*-178/250));
				draw_sprite(arka,top,x,y);
		
				rectfill(arka,hiz_gos_x,hiz_gos_y,hiz_gos_x+201,hiz_gos_y+21,makecol(0,0,0));
				rectfill(arka,hiz_gos_x+1,hiz_gos_y+1,hiz*10+hiz_gos_x,hiz_gos_y+20,makecol(0+hiz*11,255-hiz*11,0));
				textprintf_ex(arka,font,hiz_gos_x+95,hiz_gos_y+8,makecol(255,255,255),-1,"%d",hiz);


				if(ruzgar_yon==0)
				{
					draw_sprite(arka,ruzgar_sol,hiz_gos_x+60,hiz_gos_y+30);
					textprintf_ex(arka,font,hiz_gos_x+100,hiz_gos_y+46,makecol(255,255,255),-1,"%d",ruzgar_hiz);

				}

				else if(ruzgar_yon==1)
				{
					draw_sprite(arka,ruzgar_sag,hiz_gos_x+60,hiz_gos_y+30);
					textprintf_ex(arka,font,hiz_gos_x+100,hiz_gos_y+46,makecol(255,255,255),-1,"%d",ruzgar_hiz);

				}

				
				textprintf_ex(arka,font,hiz_gos_x+91,hiz_gos_y-20,makecol(255,255,255),makecol(0,0,0),"%d",kalan_zaman);
				textprintf_ex(arka,font,10,70,makecol(255,255,255),makecol(0,0,0),"PUAN = %d",oyuncu1.puan);
			    textprintf_ex(arka,font,1200,70,makecol(255,255,255),makecol(0,0,0),"PUAN = %d",oyuncu2.puan);
		
				blit(arka,screen,0,0,00,00,1300,680);

				rest(15);
				clear_bitmap(arka);
		

			}

		int x_hiz=(int)(cos(aci*3.14/180)*hiz);
		int y_hiz=(int)(sin(aci*3.14/180)*hiz);

		
		if(ruzgar_yon==0)
		{

			x_hiz-=ruzgar_hiz;

		}

		if(ruzgar_yon==1)
		{

			x_hiz+=ruzgar_hiz;

		}

		int sayac1=0;
		int xx,yy;


		while(y<=690)
		{
			kordinat(x,y,8);

			for(k=0;k<180;k++)
			{
				xx=a[k];
				yy=b[k];


			if( ((getpixel(adamlar,x,y)==renk) || (getpixel(adamlar,xx,yy)==renk)))
			{

                play_sample(avur,100,128,1000,0);

				suan->puan+=500;
				goto git;

			}



			if( ((getpixel(binalar2,x,y)==makecol(255,255,255)) || (getpixel(binalar2,x,y)==makecol(63,72,204))) || ((getpixel(binalar2,xx,yy)==makecol(255,255,255)) || (getpixel(binalar2,xx,yy)==makecol(63,72,204))))
			{
                play_sample(bvur,200,128,1000,0);
				circlefill(binalar2,x,y,25,makecol(255,0,255));
				goto git;

			}


			}		
			
			clear_bitmap(arka);

			draw_sprite(arka,arkaplan,0,0);
			draw_sprite(arka,binalar2,0,0);
			

			draw_sprite(arka,adamlar,0,0);
			draw_sprite(arka,top,x,y);

			textprintf_ex(arka,font,10,70,makecol(255,255,255),makecol(0,0,0),"PUAN = %d",oyuncu1.puan);
			textprintf_ex(arka,font,1200,70,makecol(255,255,255),makecol(0,0,0),"PUAN = %d",oyuncu2.puan);


			rest(10);
			
			blit(arka,screen,0,0,00,00,1300,680);
			
			sayac1++;

			if(sayac1==10)
			{
				y_hiz-=3;
				sayac1=0;
			}

			x+=x_hiz;
			y-=y_hiz;
			
		}

		git:

		rest(500);
	
		suan->puan+=(kalan_zaman*10);
	
	}
		
		
    yuksek_puan_yaz();

}
	
////////////////////////////////////////////////////////////////////////////
	void kordinat(float X,float Y,float r)
	{
	
	   float PI=3.14159265;

    	for(c=0;c<180;c++)
    	{
	       	if(c<=90 && c>=0)
	       	{
		      	a[c]=r*cos(c*PI/180)+X;
	       		b[c]=r*sin(c*PI/180)+Y;
	       	}
		
	       	else if(i>90 && i<180)
	       	{
	       		a[c]=r*cos(c*PI/180)+X;
	       		a[c]=r*sin(c*PI/180)+Y;
		
	       	}
		
       	}

	}
	
////////////////////////////////////////////////////////////////////////////
	void ana_menu()
	{
		
	BITMAP *giris=load_bitmap("images/ana_menu.bmp",NULL);
	BITMAP *gecici=create_bitmap(1300,680);
	BITMAP *binalar=create_bitmap(1300,680);

	SAMPLE *ses1=load_sample("sound/islem.wav");
	
	show_mouse(screen);
	blit(giris,gecici,0,0,0,0,1300,680);

	
	while(!key[KEY_ESC])
	{
		
		

		if(mouse_x >92 && mouse_x <416 && mouse_y >328 && mouse_y <385 && (mouse_b&1) )
		{
			play_sample(ses1,100,128,1000,0);
			oyuncu1.puan=0;
			oyuncu2.puan=0;
			bina_ciz(binalar);
			top_at(binalar);	
			puanlar();
			
        }

		if(mouse_x >93 && mouse_x <597 && mouse_y >419 && mouse_y <472 && (mouse_b&1) )
		{
			play_sample(ses1,100,128,1000,0);
			yuksek_puan_oku();
		}

		if(mouse_x >105 && mouse_x <282 && mouse_y >523 && mouse_y <568 && (mouse_b&1) )
		{
			play_sample(ses1,100,128,1000,0);

			exit(0);
		}

		blit(gecici,screen,0,0,0,0,1300,680);
	}

}

////////////////////////////////////////////////////////////////////////////

void puanlar()
{		
        
        BITMAP *puan=load_bitmap("images/puan.bmp",NULL);
		SAMPLE *ses1=load_sample("sound/islem.wav");
		BITMAP *gecici=create_bitmap(1300,680);
		clear_bitmap(screen);
		
		while(!key[KEY_ESC])
		{
				
				blit(puan,gecici,0,0,0,0,1300,680);
				textprintf_ex(gecici,font,630,290,makecol(255,255,255),-1,"KIRMIZI OYUNCU =%d",oyuncu1.puan);
				textprintf_ex(gecici,font,630,300,makecol(255,255,255),-1,"MAVI OYUNCU    =%d",oyuncu2.puan);
				
				if(oyuncu1.puan>oyuncu2.puan)
				{
			     	textprintf_ex(gecici,font,630,310,makecol(255,255,255),-1,"KIRMIZI OYUNCU KAZANDI");
                }
                
				else if(oyuncu1.puan<oyuncu2.puan)
				{
			     	textprintf_ex(gecici,font,630,310,makecol(255,255,255),-1,"MAVI OYUNCU KAZANDI");
                }
                
				else 
				{
                    textprintf_ex(gecici,font,630,310,makecol(255,255,255),-1,"OYUNCULAR ESIT PUAN ALDI");
                }
                
					
				if(mouse_x>23 && mouse_x<109 && mouse_y>630 && mouse_y<646 && (mouse_b&1))
				{
					play_sample(ses1,100,128,1000,0);
					ana_menu();
				}
				
				else if(mouse_x>1233 && mouse_x<1273 && mouse_y>637 && mouse_y<653 && (mouse_b&1))
				{
					play_sample(ses1,100,128,1000,0);
					exit(0);
				}

				blit(gecici,screen,0,0,0,0,1300,680);
			
		}
		
		rest(-1);
}

////////////////////////////////////////////////////////////////////////////
void yuksek_puan_yaz()
{
    
     FILE *y_puan;
 
     if((y_puan=fopen("yuksek.txt","a"))==NULL)
     {
      textout_ex(screen,font,"Yuksek.txt Baglanmadi",600,20,makecol(255,255,255),-1);                       
     }
     
     
     else
     {
           fprintf(y_puan,"%d\n",oyuncu1.puan);
           fprintf(y_puan,"%d\n",oyuncu2.puan);
     }
     
   fclose(y_puan);
}
////////////////////////////////////////////////////////////////////////////
void yuksek_puan_oku()
{    
     
     FILE *y_puan;
     BITMAP *ypuan=create_bitmap(1300,680);
     BITMAP *ypuan1=load_bitmap("images/yuksek.bmp",NULL);
     SAMPLE *ses1=load_sample("sound/islem.wav");
     blit(ypuan1,ypuan,0,0,0,0,1300,680);
     int i1,i2,i3,index;
     
     if((y_puan=fopen("yuksek.txt","r"))==NULL)
     {
            textout_ex(screen,font,"Yuksek.txt Baglanmadi",600,20,makecol(255,255,255),-1);                                        
     }
     
     else
     {	
         while(!feof(y_puan))
		{
			fscanf(y_puan,"%d\n",&dizi_puan[sira]);
			sira++;	
		}
           
     }
  
     for(i1=0;i1<sira-1;i1++)
     {
         for(i2=i1;i2<sira;i2++)
         {
            if(dizi_puan[i1]<dizi_puan[i2])
            {
               index=dizi_puan[i1];
               dizi_puan[i1]=dizi_puan[i2];
               dizi_puan[i2]=index;
            }
         }
     }
     
     
     for(i3=0;i3<3;i3++)
     {
           textprintf_ex(ypuan,font,530,160+i3*10,makecol(255,255,255),-1,"%d.Puan =  %d",i3+1,dizi_puan[i3]);                      
     }
     
     while(!key[KEY_ESC])
     {
            
                if(mouse_x>12 && mouse_x<254 && mouse_y>631 && mouse_y<658 && (mouse_b&1))
				{
					play_sample(ses1,100,128,1000,0);
					ana_menu();
				}
				else if(mouse_x>1154 && mouse_x<1277 && mouse_y>634 && mouse_y<663 && (mouse_b&1))
				{
					play_sample(ses1,100,128,1000,0);
					exit(0);
				}

				blit(ypuan,screen,0,0,00,00,1300,680);
     }
     
    
     rest(-1);
     fclose(y_puan);
}
 
////////////////////////////////////////////////////////////////////////////
 void duraklat()
{   
    SAMPLE *ses1=load_sample("sound/islem.wav");
    play_sample(ses1,100,128,1000,0);
   	BITMAP *giris=load_bitmap("images/duraklat.bmp",NULL);
	BITMAP *gecici=create_bitmap(1300,680);
	BITMAP *binalar=create_bitmap(1300,680);
	
	show_mouse(screen);
	blit(giris,gecici,0,0,0,0,1300,680);

	while(!key[KEY_ESC])
	{


		if(mouse_x >92 && mouse_x <416 && mouse_y >328 && mouse_y <385 && (mouse_b&1) )
		{
            oyuncu1.puan=0;
			oyuncu2.puan=0;
			play_sample(ses1,100,128,1000,0);
			bina_ciz(binalar);
			top_at(binalar);
			puanlar();
			
		}
		

        if(mouse_x >90 && mouse_x <320 && mouse_y >245 && mouse_y <318 && (mouse_b&1) )
		{
            play_sample(ses1,100,128,1000,0);
			break;
		}
		
		if(mouse_x >93 && mouse_x <597 && mouse_y >419 && mouse_y <472 && (mouse_b&1) )
		{
			play_sample(ses1,100,128,1000,0);
			yuksek_puan_oku();
		}

		if(mouse_x >105 && mouse_x <282 && mouse_y >523 && mouse_y <568 && (mouse_b&1) )
		{
			play_sample(ses1,100,128,1000,0);

			exit(0);
		}

		blit(gecici,screen,0,0,0,0,1300,680);
		
	}
    
    rest(100);
    
}
