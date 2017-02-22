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
  Serial.println(param.Clone().pinRS);
  randomSeed(analogRead(4));
  n = 0;
  m = 0;
  c = 0;
}

void loop() {
  /*
  glcdCtrl.colorScr = 1;
  glcdCtrl.PosScr(0, 0);
  glcdCtrl.PutCharScr('\r');
  glcdCtrl.DrawScr();
  */
  /*
  glcdCtrl.colorScr = 1;  //色を黒に指定
  glcdCtrl.PosScr(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.CelPutScr(miku);  //画像ファイル「miku」 *1 をScr *2 に描画
  glcdCtrl.MesScr("Miku,Miku");  //文字「Miku,Miku」をScrに描画
  glcdCtrl.DrawScr();  //Scr画面をグラフィック液晶に描画 *3

  delay(2000);

  glcdCtrl.colorScr = 0;  //色を白に指定
  glcdCtrl.PosScr(0, 0); //描画ポジションを(0,0)に指定
  glcdCtrl.CelPutScr(miku);  //画像ファイル「miku」 *1 をScr *2 に白で描画; mikuを消去
  glcdCtrl.MesScr("Miku,Miku");  //文字「Miku,Miku」をScrに白で描画; 文字を消去
  glcdCtrl.DrawScr();  //Scr画面をグラフィック液晶に描画 *3; mikuと文字が消去された

  delay(1000);
*/
  /*
  //////////////////////////////////////////////////////
  glcdCtrl.colorScr = 0;
  glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
  glcdCtrl.PosScr(0,0);

  glcdCtrl.colorScr = 1;
  glcdCtrl.MesScr("Demo mode");
  glcdCtrl.PosScr(0,10);
  glcdCtrl.MesScr("myGLCD libraly ver2");
  glcdCtrl.DrawScr();
  delay(3000);
  //////////////////////////////////////////////////////
  
  
  glcdCtrl.colorScr = 0;
  glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
  glcdCtrl.DrawScr();

  for(c = 0; c < 3000; c++)
  {
    glcdCtrl.colorScr = 1;
    n = random(0, glcdCtrl.sizeX);
    m = random(0, glcdCtrl.sizeY);
    glcdCtrl.DotScr(n, m);
    glcdCtrl.DotScr(n+1, m);
    glcdCtrl.DotScr(n+2, m);

    glcdCtrl.DotScr(n, m+1);
    glcdCtrl.DotScr(n+1, m+1);
    glcdCtrl.DotScr(n+2, m+1);

    glcdCtrl.DotScr(n, m+2);
    glcdCtrl.DotScr(n+1, m+2);
    glcdCtrl.DotScr(n+2, m+2);


    glcdCtrl.PosScr(10, 20);
    glcdCtrl.colorScr = 0;
    glcdCtrl.MesScr("DemoMode");
    glcdCtrl.DrawScr();
  }
  ////////////////////////////////////////////////////
  
  glcdCtrl.colorScr = 0;
  glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
  glcdCtrl.DrawScr();
  
  for(c = 0; c < 10; c++)
  {
    glcdCtrl.colorScr = 1;
    glcdCtrl.PosScr(0,0);
    glcdCtrl.MesScr("TEST! TEST? TEST%");
    glcdCtrl.DrawScr();
    delay(500);

    glcdCtrl.colorScr = 0;
    glcdCtrl.BoxfScr(0,0,127,20);

    glcdCtrl.colorScr = 1;
    glcdCtrl.PosScr(0,10);
    glcdCtrl.MesScr("Can you see that?");
    glcdCtrl.DrawScr();
    delay(500);

    glcdCtrl.colorScr = 0;
    glcdCtrl.BoxfScr(0,0,127,20);
  }

  ///////////////////////////////////////////////////////////////////////////
  glcdCtrl.colorScr = 0;
  glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
  glcdCtrl.DrawScr();
  c = 0;
  for(m = 1; ; m++)
  {
    c++;
    if(c > 3) break;
    for(n = 0; n < 127 + 63; n++)
    {
      glcdCtrl.PosScr(0,0);
      glcdCtrl.colorScr = (m  + 1)% 2;
      glcdCtrl.MesScr("Demo Mode");
      glcdCtrl.colorScr = m % 2;
      glcdCtrl.LineScr(127 - n, 0, 127 - n + 40, 63);
      glcdCtrl.DrawScr();
      delay(1);
    }
  }
  
  
  /////////////////////////////////////////////////////////////////////////
  for(n = 0; n < 3; n++)
  {
    glcdCtrl.colorScr = n % 2;
    glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
    glcdCtrl.DrawScr();
  }

  /////////////////////////////////////////////////////////////////////////
  
  
  glcdCtrl.colorScr = 0;
  glcdCtrl.BoxfScr(0, 0, glcdCtrl.sizeX, glcdCtrl.sizeY);
  glcdCtrl.DrawScr();

  for(c = 0; c < 20; c++)
  {
    n = random(0, 100);
    m = random(0, 60);

    glcdCtrl.colorScr = 1;
    glcdCtrl.PosScr(n,m);
    glcdCtrl.CelPutScr(miku);
    glcdCtrl.MesScr("Miku,Miku");
    glcdCtrl.DrawScr();

    glcdCtrl.colorScr=0;
    glcdCtrl.PosScr(n,m);
    glcdCtrl.CelPutScr(miku);
    glcdCtrl.MesScr("Miku,Miku");
  }
  //////////////////////////////////////////////////////////////////////////
  */
}


