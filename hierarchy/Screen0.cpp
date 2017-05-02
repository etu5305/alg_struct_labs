//Прикладная программа: пополнение и использование библиотеки фигур
#include <iostream>
using namespace std;
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
  rotatable* p1 = new rectangle(point(0,0),point(16,5));// цилиндр
  shape* p2 = new line(point(0,15),17); //ободок цилиндра
  shape* p3 = new myshape(point(25,10),point(37,18)); //лицо
  square_sidelong_cross *p4 = new square_sidelong_cross(point(0,0),6);//по бокам
  square_sidelong_cross *p5 = new square_sidelong_cross(point(0,0), 6);
  square_sidelong_cross *p6 = new square_sidelong_cross(point(0,0),6);//эмблема  

  //2.Ориентация
  p1->rotate_right();
	   	
  //3.Сборка изображения
  p3->move(-10,-10);
  stack(p2,p3);
  stack(p1,p2);
  l_side(p4,p2);
  r_side(p5,p2);
  put_to_center(p6, p1);
  shape_refresh();

  return 0;
}
