
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
//X KOORDINATLARININ PIKSELLERE DONUSUMU
float pix_findX(float X)
{
    if(X<0)
        return((20+X)*25);
    else
        return((X*25)+500);
}
//Y KOORDINATLARININ PIKSELLERE DONUSUMU
float pix_findY(float Y)
{
    if(Y<0)
        return((Y*-25)+500);
    else
        return((20-Y)*25);
}
double kare_top(double a, double b)
{
    return a*a + b*b;
}
int fakt(int i)
{
    int a=1;
    for(int m=1; m<=i; m+=1)
    {
        a=i*a;
    }
    return a;
}
int kombinasyon (int n,int r)
{
    int b= fakt(n)/(fakt(r)*fakt(n-r));
    return b;
}
void coordinate()
{
//X VE Y KOORDINATLARININ SAYILARINI YAZDIRMA
    char sayi[5];
    for(int i=0;i<=40;i++)
    {
        if(i!=20)
        {
        sprintf(sayi,"%d",i-20);
        outtextxy(i*25,503,sayi);
        outtextxy(503,(40-i)*25,sayi);
        }
    }
    outtextxy(503,503,"0");

//KOORDINAT NOKTALARINI CIZME
    for(int a=0; a<=1000; a += 25)
    {
        line(0,a,1000,a);
        line(a,0,a,1000);
    }


//X0 VE Y0 DOGRULARINI BELIRGINLESTIRME
    setcolor(RED);
    line(500,0,500,1000);
    line(0,500,1000,500);
}

int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, (char*)"");
    initwindow(1000,1000,"");
    int a,b,i=0;

//KOORDINAT NOKTALARININ NUMARALARINI YAZMA

    coordinate();

//NOKTALARI DOSYADAN ALMA

    int xcoor[100],ycoor[100];
    int xcoorpix[100],ycoorpix[100],j=0;

    FILE *dosya;
    dosya=fopen("coor_po.txt","r");
    if(dosya!=NULL)
    {
        while(!feof(dosya))
        {
            fscanf(dosya,"%d %c %d",&xcoor[i],&a,&ycoor[i]);

            i++;
        }
    }
    else
    {
        printf("Dosya Yok!!");
    }
    fclose(dosya);

//NOKTALARI SIRALAMA
int geciciX,geciciY;
for(int a=0;a<i;a++)
{
    for(int b=0;b<=a;b++)
        {
    if(xcoor[a]==xcoor[b])
    {
        if(ycoor[a]>ycoor[b])
            {
            geciciX=xcoor[a];
            geciciY=ycoor[a];
            xcoor[a]=xcoor[b];
            ycoor[a]=ycoor[b];
            xcoor[b]=geciciX;
            ycoor[b]=geciciY;
        }
    }
    else if(xcoor[a]>xcoor[b])
        {
            geciciX=xcoor[a];
            geciciY=ycoor[a];
            xcoor[a]=xcoor[b];
            ycoor[a]=ycoor[b];
            xcoor[b]=geciciX;
            ycoor[b]=geciciY;
        }
        }

}

//NOKTALARI YAZDIRMA
for(int a=0;a<i;a++)
{
    printf("{%d,%d}\n",xcoor[a],ycoor[a]);
}

//NOKTALARI GOSTERME

    setcolor(LIGHTRED);
    for(int a=0; a<i; a++)
    {
        fillellipse(pix_findX(xcoor[a]),pix_findY(ycoor[a]),7,7);
    }

//CEMBER BASLANGIC

    double uzaklik1, uzaklik2;
    double X=0,Y=0;

    for (int k = 0; k < i; k++)
    {
        X += xcoor[k];
        Y += ycoor[k];
    }
    X /= i;
    Y /= i;
    float P = 1;
    for (int k = 0; k < 10000; k++)
    {
        int f = 0;
        uzaklik1 = kare_top(X - xcoor[0], Y - ycoor[0]);
        for (int j = 1; j < i; j++)
        {
            uzaklik2 = kare_top(X - xcoor[j], Y - ycoor[j]);
            if (uzaklik1 < uzaklik2)
            {
                uzaklik1 = uzaklik2;
                f = j;
            }
        }
        X += (xcoor[f] - X)*P;
        Y += (ycoor[f] - Y)*P;
        P -= 0.0001;
    }
    circle(pix_findX(X),pix_findY(Y),sqrt(uzaklik1)*25);

    char merkez[20];
    char ycap[15];
    sprintf(merkez,"merkez (%.3f,%.3f)",X,Y);
    outtextxy(pix_findX(X),pix_findY(Y),merkez);
    sprintf(ycap,"Yariçap = %.3f",sqrt(uzaklik1));
    outtextxy(0,0,ycap);

    fillellipse(pix_findX(X),pix_findY(Y),3,3);

    printf("\nMerkez = {%0.3f,%0.3f} \nYaricap = %0.4f\n",X,Y,sqrt(uzaklik1));

    moverel(pix_findX(X),pix_findY(Y));
    linerel(sqrt(uzaklik1)*25,0);

//B-SPLINE BASLANGIC

    float XC=0.0,YC=0.0;

    for(double t=0; t<=1.0; t+=0.0001)
    {
        for(int j=0; j<i; j++)
        {
            XC+=kombinasyon(i-1,j)*pow(1-t,i-1-j)*pow(t,j)*xcoor[j];
            YC+=kombinasyon(i-1,j)*pow(1-t,i-1-j)*pow(t,j)*ycoor[j];
        }
            putpixel(pix_findX(XC),pix_findY(YC),15);

        XC=0.0;
        YC=0.0;
    }

    getch();
    closegraph();
    return 0;
}
