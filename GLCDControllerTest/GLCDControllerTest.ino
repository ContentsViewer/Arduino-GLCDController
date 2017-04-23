/*
*プログラム
*  最終更新日: 4.26.2016
*  説明:
*    GLCDControllerテスト用プログラムです.
*    グラフィック液晶ディスプレイSG12864ASLB-GB-Gが必要
*/
#include "GLCDController.h"

GLCDController glcdCtrl;

unsigned long updateTimePrev = 0;
int fpsPrev = 0;

int Power(int a, int power);
void Draw();
void PrintNumber(int num);

void setup(){
  Serial.begin(19200);
  GLCDController::Param param;
  param.pinRS = 13;
  param.pinRW = 12;
  param.pinE = 11;
  param.pinCS1 = 14;
  param.pinCS2 = 15;
  param.pinRST = 10;

  param.sizeX = 128;
  param.sizeY = 64;
  
  //グラフィックディスプレイを使う前に必ずする
  glcdCtrl.Begin(param);
}


void loop() {
  for(int i = 0; i < 32; i++){
    glcdCtrl.canvas.color = true;
    glcdCtrl.canvas.Line(63 - i * 2, 0, 0, i * 2);
    Draw();
    
    glcdCtrl.canvas.color = true;
    glcdCtrl.canvas.Line(0, i * 2, i * 2, 63);
    Draw();
    
    glcdCtrl.canvas.color = true;
    glcdCtrl.canvas.Line(i * 2, 63, 63, 63 - i * 2);
    Draw();
    
    glcdCtrl.canvas.color = true;
    glcdCtrl.canvas.Line(63, 63 - i * 2, 63 - i * 2, 0);
    Draw();
  }
  
  
  for(int i = 0; i < 32; i++){
    glcdCtrl.canvas.color = false;
    glcdCtrl.canvas.Line(63 - i * 2, 0, 0, i * 2);
    Draw();
    
    glcdCtrl.canvas.color = false;
    glcdCtrl.canvas.Line(0, i * 2, i * 2, 63);
    Draw();
    
    glcdCtrl.canvas.color = false;
    glcdCtrl.canvas.Line(i * 2, 63, 63, 63 - i * 2);
    Draw();
    
    glcdCtrl.canvas.color = false;
    glcdCtrl.canvas.Line(63, 63 - i * 2, 63 - i * 2, 0);
    Draw();
  }
}

void Draw() {
  glcdCtrl.canvas.color = true;
  glcdCtrl.canvas.Pos(64, 0);
  glcdCtrl.canvas.Mes("GLCD");
  glcdCtrl.canvas.Pos(70, 8);
  glcdCtrl.canvas.Mes("Controller");
  glcdCtrl.canvas.Pos(70, 16);
  glcdCtrl.canvas.Mes("Test");
  unsigned long updateTime = millis();
  
  glcdCtrl.canvas.color = true;
  glcdCtrl.canvas.Pos(75, 30);
  glcdCtrl.canvas.Mes("FPS:");
  int posX = glcdCtrl.canvas.posX - 15;
  int posY = glcdCtrl.canvas.posY + 8;
  
  glcdCtrl.canvas.color = false;
  glcdCtrl.canvas.Pos(posX, posY);
  PrintNumber(fpsPrev);
  
  glcdCtrl.canvas.color = true;
  glcdCtrl.canvas.Pos(posX, posY);
  int fps = int(1000 / (updateTime - updateTimePrev));
  PrintNumber(fps);
  glcdCtrl.Draw();

  updateTimePrev = updateTime;
  fpsPrev = fps;
}

void PrintNumber(int num) {
  int numberOfDigits = 1;
  int powered = 1;
  for (numberOfDigits = 0; num / powered != 0; numberOfDigits++, powered *= 10) {
  }

  powered = Power(10, numberOfDigits - 1);
  for (int i = 0; i < numberOfDigits; i++, powered /= 10) {
    int digit = num / powered;
    num %= powered;

    glcdCtrl.canvas.PutChar(0x30 + digit);

  }
}

int Power(int a, int power){
  int powered = 1;
  for(int i = 0; i < power; i++){
    powered *= a;
  }
  return powered;
}

/*
int n, m, c;
void setup() {
  GLCDController::Param param;
  param.pinRS = 13;
  param.pinRW = 12;
  param.pinE = 11;
  param.pinCS1 = 14;
  param.pinCS2 = 15;
  param.pinRST = 2;

  param.sizeX = 128;
  param.sizeY = 64;


  Serial.begin(19200);
  //グラフィックディスプレイを使う前に必ずする
  glcdCtrl.Begin(param);
  randomSeed(analogRead(4));
  n = 0;
  m = 0;
  c = 0;
}

void loop() {

  glcdCtrl.canvas.color = 1;  //色を黒に指定
  glcdCtrl.canvas.Pos(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.canvas.Celput(miku);  //画像ファイル「miku」 *1 をScr *2 に描画
  glcdCtrl.canvas.Mes("Miku,Miku");  //文字「Miku,Miku」をScrに描画
  glcdCtrl.Draw();  //Scr画面をグラフィック液晶に描画 *3

  delay(2000);

  glcdCtrl.canvas.color = 0;  //色を白に指定
  glcdCtrl.canvas.Pos(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.canvas.Celput(miku);  //画像ファイル「miku」 *1 をScr *2 に白で描画; mikuを消去
  glcdCtrl.canvas.Mes("Miku,Miku");  //文字「Miku,Miku」をScrに白で描画; 文字を消去
  glcdCtrl.Draw();  //Scr画面をグラフィック液晶に描画 *3; mikuと文字が消去された

  delay(1000);

  
  //////////////////////////////////////////////////////
  glcdCtrl.canvas.color = 0;
  glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
  glcdCtrl.canvas.Pos(0,0);

  glcdCtrl.canvas.color = 1;
  glcdCtrl.canvas.Mes("Demo mode");
  glcdCtrl.canvas.Pos(0,10);
  glcdCtrl.canvas.Mes("myGLCD libraly ver2");
  glcdCtrl.Draw();
  delay(3000);
  //////////////////////////////////////////////////////
  
  
  glcdCtrl.canvas.color = 0;
  glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
  glcdCtrl.Draw();

  for(c = 0; c < 3000; c++)
  {
    glcdCtrl.canvas.color = 1;
    n = random(0, glcdCtrl.canvas.SizeX());
    m = random(0, glcdCtrl.canvas.SizeY());
    glcdCtrl.canvas.Dot(n, m);
    glcdCtrl.canvas.Dot(n+1, m);
    glcdCtrl.canvas.Dot(n+2, m);

    glcdCtrl.canvas.Dot(n, m+1);
    glcdCtrl.canvas.Dot(n+1, m+1);
    glcdCtrl.canvas.Dot(n+2, m+1);

    glcdCtrl.canvas.Dot(n, m+2);
    glcdCtrl.canvas.Dot(n+1, m+2);
    glcdCtrl.canvas.Dot(n+2, m+2);


    glcdCtrl.canvas.Pos(10, 20);
    glcdCtrl.canvas.color = 0;
    glcdCtrl.canvas.Mes("DemoMode");
    glcdCtrl.Draw();
  }
  ////////////////////////////////////////////////////
  
  glcdCtrl.canvas.color = 0;
  glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
  glcdCtrl.Draw();
  
  for(c = 0; c < 10; c++)
  {
    glcdCtrl.canvas.color = 1;
    glcdCtrl.canvas.Pos(0,0);
    glcdCtrl.canvas.Mes("TEST! TEST? TEST%");
    glcdCtrl.Draw();
    delay(500);

    glcdCtrl.canvas.color = 0;
    glcdCtrl.canvas.Boxf(0,0,127,20);

    glcdCtrl.canvas.color = 1;
    glcdCtrl.canvas.Pos(0,10);
    glcdCtrl.canvas.Mes("Can you see that?");
    glcdCtrl.Draw();
    delay(500);

    glcdCtrl.canvas.color = 0;
    glcdCtrl.canvas.Boxf(0,0,127,20);
  }

  ///////////////////////////////////////////////////////////////////////////
  glcdCtrl.canvas.color = 0;
  glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
  glcdCtrl.Draw();
  c = 0;
  for(m = 1; ; m++)
  {
    c++;
    if(c > 3) break;
    for(n = 0; n < 127 + 63; n++)
    {
      glcdCtrl.canvas.Pos(0,0);
      glcdCtrl.canvas.color = (m  + 1)% 2;
      glcdCtrl.canvas.Mes("Demo Mode");
      glcdCtrl.canvas.color = m % 2;
      glcdCtrl.canvas.Line(127 - n, 0, 127 - n + 40, 63);
      glcdCtrl.Draw();
      delay(1);
    }
  }
  
  
  /////////////////////////////////////////////////////////////////////////
  for(n = 0; n < 3; n++)
  {
    glcdCtrl.canvas.color = n % 2;
    glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
    glcdCtrl.Draw();
  }

  /////////////////////////////////////////////////////////////////////////
  
  
  glcdCtrl.canvas.color = 0;
  glcdCtrl.canvas.Boxf(0, 0, glcdCtrl.canvas.SizeX(), glcdCtrl.canvas.SizeY());
  glcdCtrl.Draw();

  for(c = 0; c < 20; c++)
  {
    n = random(0, 100);
    m = random(0, 60);

    glcdCtrl.canvas.color = 1;
    glcdCtrl.canvas.Pos(n,m);
    glcdCtrl.canvas.Celput(miku);
    glcdCtrl.canvas.Mes("Miku,Miku");
    glcdCtrl.Draw();

    glcdCtrl.canvas.color=0;
    glcdCtrl.canvas.Pos(n,m);
    glcdCtrl.canvas.Celput(miku);
    glcdCtrl.canvas.Mes("Miku,Miku");
  }
  //////////////////////////////////////////////////////////////////////////
  
}
*/

