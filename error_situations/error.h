//классы для обработки ошибок
// выход за пределы экрана
//#include <iostream>
class Out_Screen{
  int x,y;

 public:
  Out_Screen () {}
  Out_Screen (int a, int b) { x = a; y = b; }
  int get_x () { return x;}
  int get_y () { return y;}
  void message () {std::cout << "Point (" << x << "," << y << ")is out of screen. " << endl;}
};


