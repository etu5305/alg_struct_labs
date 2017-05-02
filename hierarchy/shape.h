//shape.h -- Библиотека фигур 

class shape: public point { //Виртуальный базовый класс "фигура"
public:
  static shape* list;
  shape* next;
  shape() { next = list; list = this; }
  virtual point north() const = 0;
  virtual point south() const = 0;
  virtual point east() const = 0;
  virtual point west() const = 0;
  virtual point neast() const = 0;
  virtual point seast() const = 0;
  virtual point nwest() const = 0;
  virtual point swest() const = 0;
  virtual void draw() = 0;
  virtual void move(int a, int b) { x+=a; y+=b; };
  virtual ~shape(){};
};

shape * shape::list = nullptr;	//Инициализация списка фигур (список пуст)

class rotatable : virtual public shape { //Фигуры, пригодные к повороту 
	enum class rotated{left, no, right};
	rotated state; //Текущее состояние поворота
public:
	rotatable(rotated r = rotated :: no) : state(r) {}  
	virtual void rotate_left() = 0;		//Повернуть влево
	virtual void rotate_right() = 0;	//Повернуть вправо
};
class mirrorable : virtual public shape { //Фигуры, пригодные к зеркальному отражению
	enum class mirrored{no, hor, vert};
	mirrored state;	//Текущее состояние отражения
public:
	mirrorable(mirrored m = mirrored :: no) : state(m) {}
	virtual void flip_horisontally() = 0;	//Отразить горизонтально
	virtual void flip_vertically() = 0;		//Отразить вертикально
};

class line : virtual public shape {
/*
отрезок прямой ["w", "e" ]
north() определяет точку - "выше центра отрезка и
так далеко на север, как самая его северная точка"
*/
  point w, e;
public:
  point north() const { return point((w.x+e.x)/2, e.y<w.y? w.y: e.y); }
  point south() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point east() const  { return point(e.x<w.x? e.x: w.x, (w.y+e.y)/2); }
  point west() const  { return point(e.x<w.x? w.x: e.x, (w.y+e.y)/2); }
  point neast() const { return point(e.x<w.x? w.x: e.x, e.y<w.y? w.y: e.y); }
  point seast() const { return point(e.x<w.x? w.x: e.x, e.y<w.y? e.y: w.y); }
  point nwest() const { return point(e.x<w.x? e.x: w.x, e.y<w.y? w.y: e.y); }
  point swest() const { return point(e.x<w.x? e.x: w.x, e.y<w.y? e.y: w.y); }
  void move(int a, int b)
	{ w.x +=a; w.y +=b; e.x +=a; e.y +=b; }
  void draw() { put_line(w,e); }
  line(point a, point b) { w = a; e = b; }
  line(point a, int l) { w = point(a.x+l-1,a.y); e = a; }
};

//Прямоугольник
class rectangle : public rotatable {
/* nw ------ n ------ ne
   |				  |
   |				  |
   w	     c        e
   |		          |
   |		          |
   sw ------ s ------ se
*/
  point sw, ne;
public:
  point north() const { return point((sw.x+ne.x)/2,ne.y); }
  point south() const { return point((sw.x+ne.x)/2,sw.y); }
  point east() const { return point(sw.x,(sw.y+ne.y)/2); }
  point west() const { return point(ne.x,(sw.y+ne.y)/2); }
  point neast() const { return ne; }
  point seast() const { return point(sw.x, ne.y); }
  point nwest() const { return point(ne.x, sw.y); }
  point swest() const { return sw; }
  void rotate_right() //Поворот вправо - относительно se
	{ int w = ne.x - sw.x, h = ne.y - sw.y; 
	  sw.x = ne.x - h*2; ne.y = sw.y + w/2;	}
  void rotate_left() //Поворот влево - относительно sw
	{ int w = ne.x - sw.x, h = ne.y - sw.y; 
	  ne.x = sw.x + h*2; ne.y = sw.y + w/2; }
  void move(int a, int b)
	{ sw.x+=a; sw.y+=b; ne.x+=a; ne.y+=b; }
  void draw();
  rectangle(point,point);
};
rectangle::rectangle(point a, point b)
{
  if (a.x <= b.x) {
	if (a.y <= b.y) {
	   sw = a;
	   ne = b;
	}
	else {
	   sw = point(a.x,b.y);
	   ne = point(b.x,a.y);
	}
  }
  else {
	if (a.y <= b.y) {
	  sw = point(b.x,a.y);
	  ne = point(a.x,b.y);
	}
	else {
	  sw = b;
	  ne = a;
	}
  }
}  
void rectangle::draw()
{
  point nw(sw.x,ne.y);
  point se(ne.x,sw.y);
  put_line(nw,ne);
  put_line(ne,se);
  put_line(se,sw);
  put_line(sw,nw);
}


void shape_refresh() // Перерисовка всех фигур
{
  screen_clear();
  for (shape* p = shape::list; p; p=p->next) p->draw();
  screen_refresh();
}
void stack(shape* p, const shape* q) // поместить p над q
{
  point n = q->north();
  point s = p->south();
  p->move(n.x-s.x,n.y-s.y+1);
}
void r_side(shape* p, const shape* q) // поместить p справа от q
{
  point e = q->east();
  point w = p->west();
  p->move(e.x-w.x-1,e.y-w.y);
}
void l_side(shape* p, const shape* q) // поместить p слева от q
{
  point w = q->west();
  point e = p->east();
  p->move(w.x-e.x+1,w.y-e.y);
}
