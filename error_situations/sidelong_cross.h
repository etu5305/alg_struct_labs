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
  void draw();
  void resize (int i) {w=i;}
  point get_c() {return c;}
  cross(point,int);
};

cross::cross(point a, int b) : c(a), w(b)
{ }

void cross::draw()
{
  put_line(north(),south());
  put_line(east(),west());
}

// Косой крест
class sidelong_cross : public cross {
 public:
  void draw()
  {
    put_line(nwest(),seast());
    put_line(swest(),neast());
  }
 sidelong_cross(point a, int b) : cross(a,b) { } 
};

//Прямоугольник с косым крестом
class r_sidelong_cross : public rectangle, public sidelong_cross {
 public:
  point north() const { return rectangle::north(); }
  point south() const { return rectangle::south(); }
  point east() const { return rectangle::east(); }
  point west() const { return rectangle::west(); }
  point neast() const { return rectangle::neast(); }
  point seast() const { return rectangle::seast(); }
  point nwest() const { return rectangle::nwest(); }
  point swest() const { return rectangle::swest(); }
  void move(int a, int b)
  { rectangle::move(a, b); sidelong_cross::move(a, b); }
  void draw() {
     try{
      rectangle::draw();
     }
     catch (Out_Screen &err){
      std::cout << "Sidelong cross is out of screen. Resizing.." <<endl;
      point n_e = rectangle::neast();
      point s_w = rectangle::swest();
  
      n_e = rectangle::neast();
      s_w = rectangle::swest();

      point p_c = sidelong_cross::get_c();

      point q_c((n_e.x+s_w.x)/2, (n_e.y+s_w.y)/2);
      sidelong_cross::move(q_c.x-p_c.x, q_c.y-p_c.y);
      sidelong_cross::resize(q_c.x - s_w.x);
      
      if (!(on_screen(s_w.x, s_w.y) && on_screen(n_e.x,n_e.y))){
	std::cout<< "Failed to resize it." <<endl;
	}
    }
    catch (...){
      std::cout << "Unknown error." << endl;
      }
    //sidelong_cross::draw();
   
  }
  r_sidelong_cross(point,point,int);
};

r_sidelong_cross::r_sidelong_cross(point a, point b, int c) : rectangle(a, b), sidelong_cross(point((a.x+b.x)/2, (a.y+b.y)/2), c)
{ }

//Квадрат с косым крестом
class square_sidelong_cross : public r_sidelong_cross {
 public:
  square_sidelong_cross(point,int);
};

square_sidelong_cross::square_sidelong_cross(point sw, int side) : r_sidelong_cross (sw, point(sw.x+side, sw.y+side), side/2)
{ }

void put_to_center(shape* p, const shape*q) // поместить р в центр q
{
  point w = p->west();
  point e = p->east();
  point n = p->north();
  point s = p->south();
  point p_c((w.x+e.x)/2, (n.y+s.y)/2);
  w = q->west();
  e = q->east();
  n = q->north();
  s = q->south();
  point q_c((w.x+e.x)/2, (n.y+s.y)/2);
  p->move(q_c.x-p_c.x, q_c.y-p_c.y);
}
