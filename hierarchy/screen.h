//screen.h - Поддержка работы с экраном
const int XMAX=79; //Размер экрана
const int YMAX=24;
class point {	//Точка на экране
public:
	int x, y;
//	point() { };
	point(int a = 0,int b = 0) : x(a), y(b){ }
};
//Набор утилит для работы с экраном
extern void put_point(int a, int b); //Вывод точки
inline void put_point(point p) { put_point(p.x,p.y); }
extern void put_line(int, int, int, int); //Вывод линии
extern void put_line(point a, point b)
	{ put_line(a.x,a.y,b.x,b.y); }
extern void screen_init();	//Создание экрана
extern void screen_destroy();	//Удаление экрана
extern void screen_refresh();	//Обновление
extern void screen_clear();	//Очистка

//1. Поддержка экрана в форме матрицы символов
char screen[XMAX] [YMAX];	
enum color { black='*', white='.' };
void screen_init()
{
  for (int y=0; y<YMAX; y++)
    for (int x=0; x<XMAX; x++)
       screen[x] [y] = white;
}

inline int on_screen(int a, int b) // проверка попадания
{ return 0<=a && a <XMAX && 0<=b && b<YMAX; }

class OutScreen {
	int x, y; 
public: OutScreen(int a, int b) : x(a), y(b) {}
		void Msg() { std::cout << " x=" << x << " y=" << y; }
};
void put_point(int a, int b)
{ if (on_screen(a,b)) screen[a] [b] = black; else throw OutScreen(a, b); }

void put_line(int x0, int y0, int x1, int y1)
/*
Рисование отрезка прямой (x0,y0) - (x1,y1).
Уравнение прямой: b(x-x0) + a(y-y0) = 0.
Минимизируется величина abs(eps),
где eps = 2*(b(x-x0)) + a(y-y0).
*/
{
  register int dx = 1;
  int a = x1 - x0;
  if (a < 0) dx = -1, a = -a;
  register int dy = 1;
  int b = y1 - y0;
  if (b < 0) dy = -1, b = -b;
  int two_a = 2*a;
  int two_b = 2*b;
  int xcrit = -b + two_a;
  register int eps = 0;

  for (;;) {
	put_point(x0,y0);
	if (x0==x1 && y0==y1) break;
	if (eps <= xcrit) x0 +=dx, eps +=two_b;
	if (eps>=a || a<b) y0 +=dy, eps -=two_a;
  }
}

void screen_clear() { screen_init(); } //Очистка экрана

void screen_refresh() // Обновление экрана
{
  for (int y=YMAX-1; 0<=y; y--) { // с верхней строки до нижней
    for (int x=0; x<XMAX; x++) // от левого столбца до правого
      cout << screen[x] [y];
    cout << '\n';
  }
}
