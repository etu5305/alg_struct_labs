//Добавка к сборной фигуре
//Крест
class cross : virtual public shape {
  point c; int w;
public:
  point north() const { return point(c.x,c.y+w); }
  point south() const { return point(c.x,c.y-w); }
  point east() const { return point(c.x-w,c.y); }
  point west() const { return point(c.x+w,c.y); }
  point neast() const { return point(c.x+w, c.y+w); }
  point seast() const { return point(c.x+w, c.y-w); }
  point nwest() const { return point(c.x-w, c.y+w); }
  point swest() const { return point(c.x-w,c.y-w); }
  void move(int a, int b)
	{ c.x+=a; c.y+=b;}
  virtual void draw();
  cross(point,int);
};
cross::cross(point a, int b) : c(a), w(b)
{ }  
void cross::draw()
{
  put_line(north(),south());
  put_line(east(),west());
}

//Прямоугольник с крестом
class r_cross : public rectangle, public cross {
public:
  point north() const { return cross::north(); }
  point south() const { return cross::south(); }
  point east() const { return cross::east(); }
  point west() const { return cross::west(); }
  point neast() const { return rectangle::neast(); }
  point seast() const { return rectangle::seast(); }
  point nwest() const { return rectangle::nwest(); }
  point swest() const { return rectangle::swest(); }
  void move(int a, int b)
	{ rectangle::move(a, b); cross::move(a, b); }
  void draw();
  r_cross(point,point,int);
};
r_cross::r_cross(point a, point b, int c) : rectangle(a, b), cross(point((a.x+b.x)/2, (a.y+b.y)/2), c)
{ }

void r_cross::draw()
{
  rectangle::draw();
  cross::draw();
}

// Косой крест
class sidelong_cross : public cross {
public:
  void draw()
  {
    put_line(nwest(),seast());
    put_line(swest(),neast());
  }
  sidelong_cross(point a, int b) : cross(a,b)
{ } 
};

//Прямоугольник с косым крестом
class r_sidelong_cross : public r_cross, public sidelong_cross {
public:
  point north() const { return sidelong_cross::north(); }
  point south() const { return sidelong_cross::south(); }
  point east() const { return sidelong_cross::east(); }
  point west() const { return sidelong_cross::west(); }
  point neast() const { return r_cross::neast(); }
  point seast() const { return r_cross::seast(); }
  point nwest() const { return r_cross::nwest(); }
  point swest() const { return r_cross::swest(); }
  void move(int a, int b)
  { r_cross::move(a,b); }
  void draw() {
    rectangle::draw();
    sidelong_cross::draw();
  }
  r_sidelong_cross(point,point,int);
};

r_sidelong_cross::r_sidelong_cross(point a, point b, int c) : r_cross(a, b,c), sidelong_cross(point((a.x+b.x)/2, (a.y+b.y)/2), c)
{ }

//Квадрат с косым крестом
class square_sidelong_cross : public r_sidelong_cross {
 public:
  square_sidelong_cross(point,int);
};

square_sidelong_cross::square_sidelong_cross(point sw, int side) : r_sidelong_cross (sw, point(sw.x+side, sw.y+side), side/2)
{}
