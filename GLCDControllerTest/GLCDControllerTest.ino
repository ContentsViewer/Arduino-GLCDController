/*
*プログラム
*  最終更新日: 4.26.2016
*  説明:
*    GLCDControllerテスト用プログラムです.
*    グラフィック液晶ディスプレイSG12864ASLB-GB-Gが必要
*/
#include "GLCDController.h"

GLCDController glcdCtrl;

int n, m, c;
void setup() {
  GLCDController::Param param;
  param.pinsDB[0] = 10;
  param.pinsDB[1] = 9;
  param.pinsDB[2] = 8;
  param.pinsDB[3] = 7;
  param.pinsDB[4] = 6;
  param.pinsDB[5] = 5;
  param.pinsDB[6] = 4;
  param.pinsDB[7] = 3;
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
  
  glcdCtrl.color = 1;
  glcdCtrl.Pos(0, 0);
  glcdCtrl.PutChar('\r');
  glcdCtrl.Draw();
  
  
  glcdCtrl.color = 1;  //色を黒に指定
  glcdCtrl.Pos(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.Celput(miku);  //画像ファイル「miku」 *1 をScr *2 に描画
  glcdCtrl.Mes("Miku,Miku");  //文字「Miku,Miku」をScrに描画
  glcdCtrl.Draw();  //Scr画面をグラフィック液晶に描画 *3

  delay(2000);

  glcdCtrl.color = 0;  //色を白に指定
  glcdCtrl.Pos(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.Celput(miku);  //画像ファイル「miku」 *1 をScr *2 に白で描画; mikuを消去
  glcdCtrl.Mes("Miku,Miku");  //文字「Miku,Miku」をScrに白で描画; 文字を消去
  glcdCtrl.Draw();  //Scr画面をグラフィック液晶に描画 *3; mikuと文字が消去された

  delay(1000);

  
  //////////////////////////////////////////////////////
  glcdCtrl.color = 0;
  glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
  glcdCtrl.Pos(0,0);

  glcdCtrl.color = 1;
  glcdCtrl.Mes("Demo mode");
  glcdCtrl.Pos(0,10);
  glcdCtrl.Mes("myGLCD libraly ver2");
  glcdCtrl.Draw();
  delay(3000);
  //////////////////////////////////////////////////////
  
  
  glcdCtrl.color = 0;
  glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
  glcdCtrl.Draw();

  for(c = 0; c < 3000; c++)
  {
    glcdCtrl.color = 1;
    n = random(0, glcdCtrl.SizeX());
    m = random(0, glcdCtrl.SizeY());
    glcdCtrl.Dot(n, m);
    glcdCtrl.Dot(n+1, m);
    glcdCtrl.Dot(n+2, m);

    glcdCtrl.Dot(n, m+1);
    glcdCtrl.Dot(n+1, m+1);
    glcdCtrl.Dot(n+2, m+1);

    glcdCtrl.Dot(n, m+2);
    glcdCtrl.Dot(n+1, m+2);
    glcdCtrl.Dot(n+2, m+2);


    glcdCtrl.Pos(10, 20);
    glcdCtrl.color = 0;
    glcdCtrl.Mes("DemoMode");
    glcdCtrl.Draw();
  }
  ////////////////////////////////////////////////////
  
  glcdCtrl.color = 0;
  glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
  glcdCtrl.Draw();
  
  for(c = 0; c < 10; c++)
  {
    glcdCtrl.color = 1;
    glcdCtrl.Pos(0,0);
    glcdCtrl.Mes("TEST! TEST? TEST%");
    glcdCtrl.Draw();
    delay(500);

    glcdCtrl.color = 0;
    glcdCtrl.Boxf(0,0,127,20);

    glcdCtrl.color = 1;
    glcdCtrl.Pos(0,10);
    glcdCtrl.Mes("Can you see that?");
    glcdCtrl.Draw();
    delay(500);

    glcdCtrl.color = 0;
    glcdCtrl.Boxf(0,0,127,20);
  }

  ///////////////////////////////////////////////////////////////////////////
  glcdCtrl.color = 0;
  glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
  glcdCtrl.Draw();
  c = 0;
  for(m = 1; ; m++)
  {
    c++;
    if(c > 3) break;
    for(n = 0; n < 127 + 63; n++)
    {
      glcdCtrl.Pos(0,0);
      glcdCtrl.color = (m  + 1)% 2;
      glcdCtrl.Mes("Demo Mode");
      glcdCtrl.color = m % 2;
      glcdCtrl.Line(127 - n, 0, 127 - n + 40, 63);
      glcdCtrl.Draw();
      delay(1);
    }
  }
  
  
  /////////////////////////////////////////////////////////////////////////
  for(n = 0; n < 3; n++)
  {
    glcdCtrl.color = n % 2;
    glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
    glcdCtrl.Draw();
  }

  /////////////////////////////////////////////////////////////////////////
  
  
  glcdCtrl.color = 0;
  glcdCtrl.Boxf(0, 0, glcdCtrl.SizeX(), glcdCtrl.SizeY());
  glcdCtrl.Draw();

  for(c = 0; c < 20; c++)
  {
    n = random(0, 100);
    m = random(0, 60);

    glcdCtrl.color = 1;
    glcdCtrl.Pos(n,m);
    glcdCtrl.Celput(miku);
    glcdCtrl.Mes("Miku,Miku");
    glcdCtrl.Draw();

    glcdCtrl.color=0;
    glcdCtrl.Pos(n,m);
    glcdCtrl.Celput(miku);
    glcdCtrl.Mes("Miku,Miku");
  }
  //////////////////////////////////////////////////////////////////////////
  
}


