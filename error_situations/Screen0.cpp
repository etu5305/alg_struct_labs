//Прикладная программа: пополнение и использование библиотеки фигур
#include <iostream>
using namespace std;
#include "error.h"
#include "screen.h"
#include "shape.h"
#include "sidelong_cross.h"
//Дополнительная "сборная" фигура
class myshape : public rectangle {
  line* l_eye; // левый глаз
  line* r_eye; // правый глаз
  line* mouth; // рот
public:
  myshape(point, point);
  void draw();
  void move(int, int);
};
myshape::myshape(point a, point b) : rectangle(a,b)
{
  int ll = neast().x-swest().x+1;
  int hh = neast().y-swest().y+1;
  l_eye = new line(point(swest().x+2,swest().y+hh*3/4),2);
  r_eye = new line(point(swest().x+ll-4,swest().y+hh*3/4),2);
  mouth = new line(point(swest().x+2,swest().y+hh/4),ll-4);
}
void myshape::draw()
{
  rectangle::draw();
  int a = (swest().x+neast().x)/2;
  int b = (swest().y+neast().y)/2;
  put_point(point(a,b));
}
void myshape::move(int a, int b)
{
  rectangle::move(a,b);
  l_eye->move(a,b);
  r_eye->move(a,b);
  mouth->move(a,b);
}

int main( )
{   setlocale(LC_ALL, "ru-RU");
  screen_init();
  //1.Объявление набора фигур	
  rectangle* p1 = new rectangle(point(4,0),point(16,5));
  //square_sidelong_cross *p2 = new suare_sidelong_cross(point(20,20),16);

  shape_refresh();
  std::cout << p1->seast().x;
  //2.Ориентация
  //p1->move(-2,-3); // частично за пределами экрана
  //p2->move(-22,0); // частично за пределами экрана

  //shape_refresh();
  return 0;
}
