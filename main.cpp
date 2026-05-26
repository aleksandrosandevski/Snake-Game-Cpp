// snake igra moja napravena

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>

/* int generiraj(int min, int max);
void postavuvanje();
void crtanje();
void vnes();
void logika(); */
// std::srand(static_cast<unsigned int>(std::time(nullptr)));

bool zavrsenaIgra;
constexpr int sirina=50;
constexpr int visina=20;
// sirina i visina na mapata(poleto)
int zmijaX, zmijaY, ovosjeX, ovosjeY, pogodoci; // prvite 4 promenlivi se koordinati na zmijata i ovosjeto spored x i y-oskata
// x-oskata e za sirina, y-oskata e za visina(kako spored koordinaten sitem i ova e dolniot brazen isecok na koordinaten sistem, taka odat x i y)
int opaskaX[150], opaskaY[150], brojOpaska=1; // tuka pretpostavuvame deka ke ima 150 clenovi vo opasot i vrednosta treba da e 1 za da i glavata se smeta

enum class nasoki
{
    stop=0,
    levo,
    desno,
    gore,
    dolu
};
nasoki nasoka;

int generiraj(int min, int max) // generira broj vo toj opseg
{
    static constexpr double dropka { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * dropka));
}

void postavuvanje()
{
    zavrsenaIgra=false;
    nasoka=nasoki::stop; // da si stoi vo edno mesto zmijata pred da se pritisne kopce za dvizenje
    zmijaX=generiraj(0, sirina-2);
    zmijaY=generiraj(0, visina-2);
    ovosjeX=generiraj(1, sirina-2);
    ovosjeY=generiraj(1, visina-2);
    /* ovosjeX= (rand() % sirina)-2;
    ovosjeY= (rand() % visina)-2; */
    while(zmijaX==ovosjeX && zmijaY==ovosjeY) // ako se na isto mesto so glavata, ovosjeto da se stavi na novo mesto
    {
        ovosjeX=generiraj(1, sirina-2);
        ovosjeY=generiraj(1, visina-2);
        /* ovosjeX= (rand() % sirina)-2;
        ovosjeY= (rand() % visina)-2; */
    } // treba da se napravi so celo telo, no toa ponatamu
    pogodoci=0;
    // broevite predsadeni na funkcijata za generiranje treba da ostanat taka, bidejki inaku ima nekoi bagovi
}

void crtanje()
{
    // FIX FLICKER: Instead of system("cls"), move cursor to (0,0)
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for(int i=0; i<sirina+1; i++)
    {
        std::cout<<'#';
    }
    std::cout<<std::endl;

    for(int i=0; i<visina-1; i++)
    {
        for(int j=0; j<sirina; j++)
        {
            if(j==0 || j==(sirina-1))
            {
                std::cout<<'#';
            }
            if(i==zmijaY && j==zmijaX)
            {
                std::cout<<'O'; // se pecati glavata na zmijata
            }
            else if(i==ovosjeY && j==ovosjeX)
            {
                std::cout<<'F'; // se pecati ovosjeto
            }
            else
            {
                bool printaj=false;
                for(int k=0; k<brojOpaska; k++) 
                {
                    if(opaskaX[k]==j && opaskaY[k]==i)
                    {
                        std::cout<<'o'; 
                        printaj=true; 
                    }
                }
                if(!printaj)
                {
                    std::cout<<' ';
                }
            }
        }
        std::cout<<std::endl;
    }
    for(int i=0; i<sirina+1; i++)
    {
        std::cout<<'#';
    }
    std::cout<<std::endl<<"Izedeni ovosja: "<<pogodoci<<std::endl;
}

void vnes()
{
   if(_kbhit()) // ako e stisnato kopce od tastaturata(ako ne e go zema prethodnotot odnosno odi vo taa nasoka)
   {
       switch(_getch()) // da se zeme vneseniot prv znak
       {
         case 'w':
            nasoka=nasoki::gore;
            break;
         case 'a':
            nasoka=nasoki::levo;
            break;
         case 'd':
            nasoka=nasoki::desno;
            break;
         case 's':
            nasoka=nasoki::dolu;
            break;
         case 'p':
            zavrsenaIgra=true;
            break;
         /* default:
            std::cout<<"Vnesen e pogresen znak!"; */
       }
   }
}

void logika()
{
   int prethodenX=opaskaX[0];
   int prethodenY=opaskaY[0]; // prethodniot element na opasot vo ovoj slucaj prviot
   int prethoden2X, prethoden2Y;
   opaskaX[0]=zmijaX;
   opaskaY[0]=zmijaY;
   for(int i=0; i<brojOpaska; i++)
   {
       prethoden2X=opaskaX[i];
       prethoden2Y=opaskaY[i]; // se zapametuva vrednosta na segasniot segment(koordinatite)
       opaskaX[i]=prethodenX;
       opaskaY[i]=prethodenY; // spored prethodniot, ja dobivaat vrednosta na prethodniot
       prethodenX=prethoden2X;
       prethodenY=prethoden2Y;
   }
   // so prethodniot kod ja dvizime opaskata na zmijata, odnosno samata zmija
   switch(nasoka) // i da ne stisneme kopce zmijata pak si odi vo prethodnata nasoka, bidejki pak si e istata
   {
      case nasoki::levo:
          --zmijaX; // stom odime levo x koordinata se namaluva
          break;
      case nasoki::desno:
          ++zmijaX; // stom odime desno x koodrinata se zgolemuva
          break;
      case nasoki::gore:
          --zmijaY; // stom odime nagore y koordinatata se namaluva bidejki tuka najgore e 0 pa odi nadolu
          break;
      case nasoki::dolu:
          ++zmijaY; // stom odime nadolu togas y koordinata se zgolemuva bidejki odime od 0 pa do visina
          break;
      default:
          break;
   }
   
   // Back to your original wall physics bounds
   if(zmijaX > sirina-2 || zmijaX < 0 || zmijaY > visina-2 || zmijaY < 0) 
   {
       zavrsenaIgra=true;
   }
   
   for(int i=0; i<brojOpaska; i++)
   {
       if(opaskaX[i]==zmijaX && opaskaY[i]==zmijaY) // ako glavata na zmijata se udrila so koj bilo del od nejzinata opaska
       {
           zavrsenaIgra=true;
       }
   }
   if(zmijaX==ovosjeX && zmijaY==ovosjeY) // ako zmijata go izela ovosjeto se zgolemuva brojot na pogodoci/poeni i se zgolemuva brojot na segmenti kaj opaskata
   {
       pogodoci++;
       while(zmijaX==ovosjeX && zmijaY==ovosjeY)
       {
           ovosjeX=generiraj(1, sirina-2);
           ovosjeY=generiraj(1, visina-2);
           /* ovosjeX= (rand() % sirina)-2;
           ovosjeY= (rand() % visina)-2; */
       }
       brojOpaska++;
   }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    postavuvanje();
    while(!zavrsenaIgra)
    {
        crtanje(); // najprvo se nacrta rezultatot od prethodnoto vnesuvanje(mrdanje0(iteracija)
        vnes(); // pak se vnesuva
        logika(); // pa se proveruva dali nesto e izedeno, dali treba da se zgolemi, dali e kraj na igra i sl.
        
        // Exact original movement rhythm loops using standard Windows Sleep
        if (nasoka == nasoki::levo || nasoka == nasoki::desno)
        {
            Sleep(10);
        }
        Sleep(100);
        if (nasoka == nasoki::gore || nasoka == nasoki::dolu)
        {
            Sleep(60);
        }
    }
    return 0;
}