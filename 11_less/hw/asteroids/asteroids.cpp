#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <cmath>
#include <memory>
#include <list>
#include <random>
#include <iostream>
using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

enum class names {
    asteroid,
    player,
    bullet,
    explosion,
    none
};

class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   std::vector<IntRect> frames;

   Animation(){}

   Animation (Texture &t, int x, int y, int w, int h, int count, float Speed)
   {
     Frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( IntRect(x+i*w, y, w, h)  );

     sprite.setTexture(t);
     sprite.setOrigin(w/2,h/2);
     sprite.setTextureRect(frames[0]);
   }


   void update()
   {
     Frame += speed;
     int n = frames.size();
     if (Frame >= n) Frame -= n;
     if (n>0) sprite.setTextureRect( frames[int(Frame)] );
   }

   bool isEnd()
   {
     return Frame+speed>=frames.size();
   }

};


class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   names name;
   Animation anim;

   Entity()
   {
     life=true;
   }

   void settings(Animation &a,int X,int Y, float Angle=0,int radius=1) 
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)
   {
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     //app.draw(circle);
   }

   virtual ~Entity(){};
};


class asteroid: public Entity
{
  public:
    asteroid()
    {  
      using namespace std;
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> dis(1, 8);

      dx=dis(gen)-4;
      dy=dis(gen)-4;
      name=names::asteroid;
    }

   void update() override
   {
     x+=dx;
     y+=dy;

     if (x>W) x=0;  if (x<0) x=W;
     if (y>H) y=0;  if (y<0) y=H;
   }

};


class bullet: public Entity
{
   public:
   bullet()
   {
     name=names::bullet;
   }

   void  update() override
   {
     dx=cos(angle*DEGTORAD)*6;
     dy=sin(angle*DEGTORAD)*6;
     // angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>W || x<0 || y>H || y<0) life= false;
   }

};


class player: public Entity
{
   public:
   bool thrust;
   int health_points = 3;
   int points = 0;

   player()
   {
      name=names::player;
     // health_points = 3;
   }

   void update() override
   {
     if (thrust)
      { dx+=cos(angle*DEGTORAD)*0.2;
        dy+=sin(angle*DEGTORAD)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int maxSpeed=15;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>W) x=0; if (x<0) x=W;
    if (y>H) y=0; if (y<0) y=H;
   }

};


bool isCollide(std::shared_ptr<Entity> a,std::shared_ptr<Entity> b)
//bool isCollide(Entity *a,Entity *b)
{

  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}

class health {
public:
    Animation anim;
    float x, y, angle;
    health(Animation& a, int X, int Y, float Angle = 0) :x(X), y(Y), angle(Angle), anim(a) {}
    void draw(sf::RenderWindow& app)
    {
      anim.sprite.setPosition(x, y);
      anim.sprite.setRotation(angle);
      anim.sprite.setScale(0.3f, 0.3f);
      app.draw(anim.sprite);
    }
};

int main()
{
	
    Music music;//создаем объект музыки
    music.openFromFile("audio/always.ogg");//загружаем файл
    music.play();//
    music.setLoop(true);
    std::random_device rd;
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t6,t7, t8, t9;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t8.loadFromFile("images/health.png");
    t9.loadFromFile("images/game_over.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);
    Sprite game_over(t9);

    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);
    Animation Health_Points(t8, 10,0,150,150, 1, 0);

    sf::Text text_points;
    sf::Font font;

    font.loadFromFile("images/Chunk Five Print.otf");
    text_points.setFont(font);
    text_points.setFillColor(sf::Color(255, 0, 0, 200));
    text_points.setOutlineColor(sf::Color::Black);
    text_points.setOutlineThickness(2);
    text_points.setCharacterSize(48);
    text_points.setStyle(sf::Text::Regular);
    text_points.setString(std::to_string(0));
    text_points.setPosition(20, 0);
    app.setFramerateLimit(60);

    std::list<std::shared_ptr<Entity>> entities;
    //std::list<Entity*> entities;

    for(int i=0;i<15;i++)
    {
      std::shared_ptr<asteroid> a (new asteroid());
      //asteroid *a = new asteroid();
      a->settings(sRock, rd()%W, rd()%H, rd()%360, 25);
      entities.push_back(a);
    }

    std::shared_ptr<player> p (new player());
    //player *p = new player();
    p->settings(sPlayer,W/2,H/2,0,20);
    entities.push_back(p);

    SoundBuffer shootBuffer;//создаём буфер для звука
    shootBuffer.loadFromFile("audio/shoot.ogg");//загружаем в него звук
    Sound shoot(shootBuffer);

    SoundBuffer babahBuffer;//создаём буфер для звука
    babahBuffer.loadFromFile("audio/babah.ogg");//загружаем в него звук
    Sound babah(babahBuffer);

    // SoundBuffer deathBuffer;//создаём буфер для звука
    // babahBuffer.loadFromFile("audio/death.ogg");//загружаем в него звук
    // Sound death(deathBuffer);
    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                std::shared_ptr<bullet> b (new bullet());
                //bullet *b = new bullet();
                shoot.play();
                b->settings(sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
    else p->thrust=false;


    for(auto a:entities)
     for(auto b:entities)
     {
      if (a->name==names::asteroid && b->name==names::bullet)
       if ( isCollide(a,b) )
           {
            babah.play();
            a->life=false;
            b->life=false;
            
            p->points++;
            text_points.setString(std::to_string(p->points));

            std::shared_ptr<Entity> e(new Entity());
            //Entity *e = new Entity();
            e->settings(sExplosion,a->x,a->y);
            e->name=names::explosion;
            entities.push_back(e);


            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             std::shared_ptr<Entity> e(new asteroid());
             //Entity *e = new asteroid();
             e->settings(sRock_small,a->x,a->y,rd()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name==names::player && b->name==names::asteroid)
       if ( isCollide(a,b) )
           {
            babah.play();
            b->life=false;
            
            std::shared_ptr<Entity> e(new Entity());
            //Entity *e = new Entity();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name=names::explosion;
            entities.push_back(e);

            p->settings(sPlayer,W/2,H/2,0,20);
            p->dx=0; p->dy=0;

            if (p->health_points > 1)
              {
                p->settings(sPlayer, W / 2, H / 2, 0, 20);
                p->dx = 0;
                p->dy = 0;
                p->health_points--;
              }
            else
              {
                p->health_points--;
                for (int i = 0; i < 64; i++) {  
                app.draw(background);
                e->anim.update();
                e->draw(app);
                app.display();
              }
                app.draw(background);
                app.display();
              }
            }

            if (p-> health_points == 0) {

                app.clear();
                app.draw(background);
                for (int i = 0; i < 255; i = i + 7) {

                  game_over.setPosition(330, 150);
                  game_over.setColor(sf::Color(255, 255, 255, i));
                  app.draw(game_over);
                  app.display();
                }
                system("pause");
                return 0;
            }

     }


    if (p->thrust)  p->anim = sPlayer_go;
    else   p->anim = sPlayer;


    for(auto e:entities) 
      if (e->name==names::explosion)
        if (e->anim.isEnd()) 
          e->life=false;

    if (rd()%150 == 0)
     {
       std::shared_ptr<asteroid> a(new asteroid());
       //asteroid *a = new asteroid();
       a->settings(sRock, 0,rd()%H, rd()%360, 25);
       entities.push_back(a);
     }

    for(auto i=entities.begin();i!=entities.end();)
    {
      std::shared_ptr<Entity> e;
      e = *i;
      //Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); //delete e;
      }
      else i++;
    }

   //////draw//////
   app.draw(background);
   for(auto i:entities) i->draw(app);

    for (auto i = 0; i < p->health_points; i++) {  
      std::shared_ptr<health> health_p(new health(Health_Points, 50 + i * 50, 80, 0));
      //health *health_p = new health(Health_Points, 50 + i * 50, 80, 0);
    health_p->draw(app);
  }
  app.draw(text_points);
   app.display();
  }

    return 0;
}

//g++ asteroids.cpp -o asteroids  -lsfml-graphics -lsfml-window -lsfml-system -lfsm-audio