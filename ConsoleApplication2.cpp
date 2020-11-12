// ConsoleApplication2.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include<Windows.h>

using namespace std;

enum YON {

	YON_SOL = 1,
	YON_SAG = 2,
	YON_YUKARI = 3,
	YON_ASAGI = 4
};

struct yilanHucre
{
	int x;
	int y;
	YON yon;
	char karakter;
};


const int genislik = 80;
const char yilanKarekteri = 219;
const int yükseklik = 20;
const int maxYilanUzunlugu = 500;
int kuyrukUzunlugu = 0;
char sahne[genislik][yükseklik];
char tuslar[256];
yilanHucre yilankuyrugu[maxYilanUzunlugu];


void gotoxy(int x, int y) {

	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}




void kursoriGizle() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void sahneyiciz() {
	for (int y = 0;y < yükseklik;y++) {

		for (int x = 0;x < genislik;x++) {

			cout << sahne[x][y];
		}
		cout << endl;
	}
}
void sahneyiTemizle() {
	for (int y = 0;y < yükseklik;y++) {

		for (int x = 0;x < genislik;x++) {

			sahne[x][y]=' ';
		}
		cout << endl;
	}
}


void sinirlariCiz() {
	for (int x = 0;x < genislik;x++) {

		sahne[x][0]=219;
		sahne[x][yükseklik-1] = 219;
	}


	for (int x = 0;x < yükseklik;x++) {

		sahne[genislik-1][x] = 219;
		sahne[0][x] = 219;
	}
	}


void klavyeoku(char tuslar[]) {
	for(int x=0;x<256;x++){
	    
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
	   
	}
}



void yilaniHareketEttir() {

	for (int i = 0;i < kuyrukUzunlugu;i++) {

		switch (yilankuyrugu[i].yon)
		{

		case YON_SAG:
			yilankuyrugu[i].x++;
			break;
		case YON_SOL:
			yilankuyrugu[i].x--;
			break;
		case YON_ASAGI:
			yilankuyrugu[i].y++;
			break;
		case YON_YUKARI:
			yilankuyrugu[i].y--;
			break;
		default:
			break;
		}

		
		}	
	
	for (int i = kuyrukUzunlugu - 1;i >0;i--) {

			yilankuyrugu[i].yon = yilankuyrugu[i-1].yon;
	}
}


void yilanKuyrugunaEkle() {


	if (kuyrukUzunlugu == maxYilanUzunlugu)
		return;


	int x = yilankuyrugu[kuyrukUzunlugu - 1].x;
	int y = yilankuyrugu[kuyrukUzunlugu - 1].y;

	YON yon1 = yilankuyrugu[kuyrukUzunlugu - 1].yon;
	char kar = yilankuyrugu[kuyrukUzunlugu - 1].karakter;


	switch (yilankuyrugu[kuyrukUzunlugu - 1].yon)
	{

	case YON_SAG:
		x--;
		break;
	case YON_SOL:
		x++;
		break;
	case YON_ASAGI:
		y--;
		break;
	case YON_YUKARI:
		y++;
		break;
	default:
		break;
	}

	yilankuyrugu[kuyrukUzunlugu].x = x;
	yilankuyrugu[kuyrukUzunlugu].y = y;
	yilankuyrugu[kuyrukUzunlugu].yon = yon1;
	yilankuyrugu[kuyrukUzunlugu].karakter = kar;
	kuyrukUzunlugu++;
}

void yilanOlustur() {

	kuyrukUzunlugu = 1;
	yilankuyrugu[0].x = 20;
	yilankuyrugu[0].y = 10;
	yilankuyrugu[0].yon = YON_SAG;

	yilanKuyrugunaEkle();
	yilanKuyrugunaEkle();
}

void yilaniSahneyeYerlestir() {
	
	for (int i = 0;i < kuyrukUzunlugu;i++) {

		int x = yilankuyrugu[i].x;
		int y = yilankuyrugu[i].y;
		sahne[x][y] = yilanKarekteri;
	}

}

void klavyeKontrol() {
	klavyeoku(tuslar);
	if (tuslar['A'] != 0) {
		yilankuyrugu[0].yon = YON_SOL;
	}
	if (tuslar['W'] != 0) {
		yilankuyrugu[0].yon = YON_YUKARI;

	}
	if (tuslar['D'] != 0) {
		yilankuyrugu[0].yon = YON_SAG;
	}
	if (tuslar['S'] != 0) {
		yilankuyrugu[0].yon = YON_ASAGI;
	}
	if (tuslar['P'] != 0) {
		yilanKuyrugunaEkle();
	}
}

int main()
{

	kursoriGizle();
	yilanOlustur();
	

	
	
	
	 while (true) {
		 sahneyiTemizle();
		 sinirlariCiz();
		 klavyeKontrol();
		 yilaniHareketEttir();
		 yilaniSahneyeYerlestir();
		 gotoxy(0, 0);
	     sahneyiciz();
		 Sleep(50);
		
		


	 }
	

	gotoxy(0, yükseklik+3);



	return 0;
}


