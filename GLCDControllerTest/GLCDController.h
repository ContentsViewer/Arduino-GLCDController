/*
  グラフィック液晶操作用関数セット
  最終更新日: 4.23.2016

   説明
     グラフィック液晶(SG12864ASLB-GB-G)を操作するための関数セットです

   特徴
     この関数でできること
       点を打つ, 線を引く, 短形を描画, 文字入力, 画像表示

   使用例
     画像描写 画像mikuと文字「miku」が点滅します.


  #include "GLCDController.h"

  GLCDController glcdCtrl;

  void setup() {
  //ピン設定
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

  //グラフィックディスプレイを使う前に必ずする
  glcdCtrl.Begin(param);
  }

  void loop() {
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
  }
       (注)
*        *1: 画像ファイルはdot絵である必要があります. 画像の大きさは縦8ピクセルor 16ピクセルor 32ピクセルである必要があります.
             画像の横の大きさは制限ありません. ただし描画速度が遅くなる, マイコンの  メモリを大量に消費する欠点があります.
             詳しい説明は"images.h"内を参照してください.

*        *2: Scrとは仮想画面です. 描画をする関数が描画する対象はScrです. 描画関数で描画しても液晶画面に描画されません.

*        *3: Scr画面を液晶画面に転写します. まとめて液晶画面に描画することで描画速度の向上, 液晶操作の簡易を実現しています.

*        *4: ほかのヘッダファイルがあるとき, 必ずこのヘッダファイルを先にincludeしてください.

   更新履歴:
     2015/12/9:
       celputScr内: l -> l_celputScr_myGLCD; 変数の重複宣言を防ぐため

     2.3.2016:
       説明欄更新

    4.23.2016:
        スクリプト修正
        文字表示の際Fontデータにない文字は'.'を表示するようにした

   詳しい情報:
     詳しい情報をほしい方は下記のサイトを参考にしてください.
       http://kanrec.web.fc2.com/contents/informatics/contents/Arduino/contents/myGLCD/contents/usage_myGLCD/index_usage_myGLCD.html
         注: リンクが切れていたときはスミマセン.
*/
#define __PROG_TYPES_COMPAT__  //prog_uint8_t, prog_uint32_tを宣言するのに必要
#include <avr/pgmspace.h>
#include "Font.h"
#include "Images.h"
#include "Arduino.h"
#include <stdlib.h>

class GLCDController
{

  public:
    class Param
    {
      public:
        byte pinsDB[8];
        byte pinRS;
        byte pinRW;
        byte pinE;
        byte pinCS1;
        byte pinCS2;
        byte pinRST;

        byte sizeX;
        byte sizeY;

        void CopyFrom(Param &from) {
          for (int i = 0; i < 8; i++) {
            this->pinsDB[i] = from.pinsDB[i];
          }

          this->pinRS = from.pinRS;
          this->pinRW = from.pinRW;
          this->pinE = from.pinE;
          this->pinCS1 = from.pinCS1;
          this->pinCS2 = from.pinCS2;
          this->pinRST = from.pinRST;
          this->sizeX = from.sizeX;
          this->sizeY = from.sizeY;

        }
        /*
                Param Clone()
                {
                  Param work;
                  for (byte i = 0; i < 8; i++)
                  {
                    work.pinsDB[i] = this->pinsDB[i];
                  }

                  work.pinRS = this->pinRS;
                  work.pinRW = this->pinRW;
                  work.pinE = this->pinE;
                  work.pinCS1 = this->pinCS1;
                  work.pinCS2 = this->pinCS2;
                  work.pinRST = this->pinRST;
                  work.sizeX = this->sizeX;
                  work.sizeY = this->sizeY;

                  return work;
                }
        */
    };

  private:
    Param param;

  public:
    int SizeX() {
      return param.sizeX;
    }

    int SizeY() {
      return param.sizeY;
    }

    void Begin(Param &param)
    {
      this->param.CopyFrom(param);

      //グラフィックディスプレイを使う前に必ずする
      InitGLCD();  // GLCD の初期化
      ClsGLCD();   // CLS
      InitScr();   //Screenを初期化
    }


    //---
    //
    //GLCD操作用関数
    //
    //---

    //チップの選択
    void ChipSelect(boolean cs)
    {
      if (cs == 0)
      {
        digitalWrite(param.pinCS1, HIGH); // cs = 0 chip 1
        digitalWrite(param.pinCS2, LOW);
      }
      else
      {
        digitalWrite(param.pinCS1, LOW);  // cs = 1 chip 2
        digitalWrite(param.pinCS2, HIGH);
      }
    }

    //ポートのセットと送信
    void WriteBUS(boolean rs, boolean rw, byte dat)
    {
      digitalWrite(param.pinRS, rs);  // RS をセット

      for (int i = 0; i < 8; i++)
      { // データをバスにセット
        digitalWrite(param.pinsDB[i], (dat >> i) & 0x01);
      }

      digitalWrite(param.pinE, HIGH); // イネーブルをラッチ
      digitalWrite(param.pinE, LOW);
    }

    //コマンドの送信
    void WriteCommand(byte dat)
    {
      WriteBUS(0, 0, dat);  // RS=0, RW=0
    }

    //データの送信
    void WriteData(byte dat)
    {
      WriteBUS(1, 0, dat);  // RS=1, RW=0
    }

    //アドレスのセット
    void SetAddress(byte col, byte row)
    {
      WriteBUS(0, 0, 0x40 | (col & 0x3F)); // set address (0-63)
      WriteBUS(0, 0, 0xB8 | (row & 0x07)); // set page (0-7)
    }

    //すでに表示されているデータを読み取る
    byte ReadData(void)
    {
      byte ret = 0;  // 戻り値用変数

      for (int i = 0; i < 8; i++) pinMode(param.pinsDB[i], INPUT); // DB0～DB7を入力モードに設定
      digitalWrite(param.pinRS, HIGH);
      digitalWrite(param.pinRW, HIGH);
      digitalWrite(param.pinE, HIGH);
      digitalWrite(param.pinE, LOW);
      digitalWrite(param.pinE, HIGH);

      for (int i = 0; i < 8; i++) ret += (digitalRead(param.pinsDB[i]) << i);
      digitalWrite(param.pinE, LOW);
      digitalWrite(param.pinRW, LOW);
      for (int i = 0; i < 8; i++) pinMode(param.pinsDB[i], OUTPUT); // DB0～DB7を出力モードに設定

      return (ret);
    }

    //GLCDの初期化
    void InitGLCD(void)
    {

      // ポート設定
      pinMode(param.pinRS, OUTPUT);
      pinMode(param.pinRW, OUTPUT);
      pinMode(param.pinE, OUTPUT);
      pinMode(param.pinCS1, OUTPUT);
      pinMode(param.pinCS2, OUTPUT);
      pinMode(param.pinRST, OUTPUT);
      for (int i = 0; i < 8; i++) pinMode(param.pinsDB[i], OUTPUT);

      // 初期状態として LOW に設定
      digitalWrite(param.pinRS, LOW);
      digitalWrite(param.pinRW, LOW);
      digitalWrite(param.pinE, LOW);
      digitalWrite(param.pinCS1, LOW);
      digitalWrite(param.pinCS2, LOW);
      digitalWrite(param.pinRST, HIGH); // Reset 解除

      delay(30);

      // chip 1
      ChipSelect(0);

      // Display Start Line = 0
      WriteCommand(0xC0);

      // Display On
      WriteCommand(0x3F);

      // chip 2
      ChipSelect(1);
      WriteCommand(0xC0);
      WriteCommand(0x3F);
    }

    //画面に表示されているものを消す, アドレスを左上に設定
    void ClsGLCD(void)
    {
      byte col, row, i;

      for (i = 0; i < 2; i++)
      {
        ChipSelect(i);        // チップを選択
        for (row = 0; row < 8; row++)
        {
          SetAddress(0, row);  // アドレスをセット
          for (col = 0; col < 64; col++)
          {
            WriteData(0);     // 0x00 を送信
          }
        }
      }
      SetAddress(0, 0);       // Return Home
    }

    //ディスプレイ,オンオフ
    void SwitchDisplay(byte i)
    {
      if (i == 0)
      {
        ChipSelect(0);
        WriteCommand(0x3E); // Display Off
        ChipSelect(1);
        WriteCommand(0x3E); // Display Off
      }
      else
      {
        ChipSelect(0);
        WriteCommand(0x3F); // Display On
        ChipSelect(1);
        WriteCommand(0x3F); // Display On
      }
    }

    //---
    //SCR操作用関数
    //  説明:
    //      液晶ディスプレイに描画する前の描画空間'Screen'
    //
    //---


  private:
    //0: dotをうっていない; 1: dotをうった
    byte *scrBuf = NULL;
    int scrBufCount = 0;

    //0: 内容を変更していない; 1: 内容を変更した
    byte *scrBufUpdated = NULL;
    int scrBufUpdatedCount = 0;

  public:
    //
    //関数 void InitScr(void)
    //  説明:
    //    Scrを初期化
    //
    void InitScr(void)
    {
      free(scrBuf);
      free(scrBufUpdated);

      scrBufCount = param.sizeX * param.sizeY / 8;
      scrBufUpdatedCount = param.sizeX;
      scrBuf = (byte *)calloc(scrBufCount, sizeof(byte));
      scrBufUpdated = (byte *)calloc(scrBufUpdatedCount, sizeof(byte));

      for (int i = 0; i < scrBufCount; i++)
      {
        scrBuf[i] = 0;
      }

      for (int i = 0; i < scrBufUpdatedCount; i++)
      {
        scrBufUpdated[i] = 0;
      }
    }


    //
    //変数 byte colorScr
    //  説明:
    //
    //  値:
    //    0: 何もなし
    //    1: 黒
    //
    byte colorScr = 0;

    //
    //関数 void PosScr(int x, int y)
    //  説明:
    //    描画位置を指定します
    //
    //  引数, 変数:
    //    int x, posScrX: 描画位置のx座標
    //    int y, posScrY: 描画位置のy座標
    //
    int posScrX = 0, posScrY = 0;
    void PosScr(int x, int y)
    {
      posScrX = x;
      posScrY = y;
    }

    //
    //関数 void DrawScr(void)
    //  説明:
    //    GLCD_scr_buf の内容をGLCDに出力
    //    Scrを液晶ディスプレイに描画します
    //
    void DrawScr(void)
    {
      for (byte i = 0; i < 2; i++)
      {
        ChipSelect(i);
        for (int j = 0; j < scrBufCount / 2; j++)
        {
          //chip1のとき
          if (i == 0)
          {
            //内容が更新されているときのみ実行
            if (0x01 & (scrBufUpdated[j % (param.sizeX / 2)] >> (j / (param.sizeX / 2))))
            {
              //書き込みアドレスの指定
              SetAddress(j % (param.sizeX / 2), j / (param.sizeX / 2));
              WriteData(scrBuf[2 * (j / (param.sizeX / 2)) * (param.sizeX / 2) + j % (param.sizeX / 2)]);

              //更新済みにする(フラグを消す)
              scrBufUpdated[j % (param.sizeX / 2)] = ~(~scrBufUpdated[j % (param.sizeX / 2)] | (0x01 << (j / (param.sizeX / 2))));
            }
          }

          //chip2のとき
          if (i == 1)
          {
            //内容が更新されているときのみ実行
            if (0x01 & (scrBufUpdated[(param.sizeX / 2) + (j % (param.sizeX / 2))] >> (j / (param.sizeX / 2))))
            {
              //書き込みアドレスの指定
              SetAddress(j % (param.sizeX / 2), j / (param.sizeX / 2));
              WriteData(scrBuf[(2 * (j / (param.sizeX / 2)) + 1) * (param.sizeX / 2) + j % (param.sizeX / 2)]);

              //更新済みにする(フラグを消す)
              scrBufUpdated[(param.sizeX / 2) + (j % (param.sizeX / 2))] = ~(~scrBufUpdated[(param.sizeX / 2) + (j % (param.sizeX / 2))] | (0x01 << (j / (param.sizeX / 2))));
            }
          }
        }
      }
    }

    //
    //関数 void DotScr(int x, int y)
    //  説明:
    //    scrBuf の指定された位置にdotを打ちます
    //
    //
    void DotScr(int x, int y)
    {
      //指定されている位置が画面内にあるときだけ実行
      if (x < param.sizeX && y < param.sizeY && x >= 0 && y >= 00)
      {
        byte temp;

        //書き込む前のデータを一時保存
        temp = scrBuf[(y / 8) * param.sizeX + x];

        //指定された位置をアドレスに変換, そのアドレスの指定された場所に
        //1を書き込む
        if (colorScr == 1) scrBuf[(y / 8) * param.sizeX + x] |= (0x01 << (y % 8));

        //0を書き込む
        if (colorScr == 0) scrBuf[(y / 8) * param.sizeX + x] = ~(~(scrBuf[(y / 8) * param.sizeX + x]) | (0x01 << (y % 8)));

        //データが更新されたときフラグを立てる
        if (temp != scrBuf[(y / 8) * param.sizeX + x])
        {
          scrBufUpdated[x] |= (0x01 << (y / 8));
        }
      }
    }


    int Abs(int a)
    {
      return (((a) > 0) ? (a) : -(a));
    }

    //
    //関数 void LineScr(int x0, int y0, int x1, int y1)
    //  説明:
    //    線を引きます
    //
    //  引数:
    //    int x0: 一方の端のx座標(-32768 ~ +32768)
    //    int y0: 一方の端のy座標
    //    int x1: もう片方の端のx座標
    //    int y1: もう片方の端のy座標
    //
    void LineScr(int x0, int y0, int x1, int y1)
    {
      int steep, t;
      int deltaX, deltaY;
      int x, y;
      int yStep, error;

      /// 差分の大きいほうを求める
      steep = (Abs(y1 - y0) > Abs(x1 - x0));
      /// ｘ、ｙの入れ替え
      if (steep)
      {
        t = x0; x0 = y0; y0 = t;
        t = x1; x1 = y1; y1 = t;
      }
      if (x0 > x1)
      {
        t = x0; x0 = x1; x1 = t;
        t = y0; y0 = y1; y1 = t;
      }
      deltaX = x1 - x0;  // 傾き計算
      deltaY = abs(y1 - y0);
      error = 0;
      y = y0;
      /// 傾きでステップの正負を切り替え
      if (y0 < y1) yStep = 1; else yStep = -1;
      /// 直線を点で描画
      for (x = x0; x <= x1; x++)
      {
        if (steep)
        {
          DotScr(y, x);
        }
        else
        {
          DotScr(x, y);
        }

        error += deltaY;

        if ((error << 1) >= deltaX)
        {
          y += yStep;
          error -= deltaX;
        }
      }
    }

    //
    //関数 void BoxfScr(int x0, int y0, int x1, int y1)
    //  説明:
    //    矩形を描写します
    //
    //  引数:
    //    int x0: 矩形の左上点 x座標
    //    int y0: 矩形の左上点 y座標
    //    int x1: 矩形の右下点 x座標
    //    int y1: 矩形の右下点 y座標
    //
    void BoxfScr(int x0, int y0, int x1, int y1)
    {
      int t;
      if (x1 < x0) //xの入れかえ
      {
        t = x0; x0 = x1; x1 = x0;
      }
      for (; x0 <= x1; x0++)
      {
        //直線を描く
        LineScr(x0, y0, x0, y1);
      }
    }

    //
    //画像表示(文字を含む)関数 CelPutScr(imgName)
    //  引数:
    //    imgName:
    //      配列,画像データを数値にしたもの
    //      最大x幅: 0~255; 最大y幅: 0~8 or 0~16 or 0~32
    //
    template <typename T, int COL>
    void CelPutScr(const T(&imagName)[COL])
    {
      for (int i = 0; i < COL; i++)
      {
        //画像の縦の長さを調べる
        byte row = sizeof(T);

        //縦の長さに応じて処理を分ける
        if (row == 1)
        {
          for (int j = 0; j < 8; j++)
          {
            if (0x01 & (pgm_read_byte_near(&imagName[i]) >> j))
            {
              DotScr(posScrX, posScrY + j);
            }
          }
        }
        else if (row == 2)
        {
          for (int j = 0; j < 16; j++)
          {

            if (0x01 & (pgm_read_word_near(&imagName[i]) >> j))
            {
              DotScr(posScrX, posScrY + j);
            }
          }
        }
        else if (row == 4)
        {
          for (int j = 0; j < 32; j++)
          {
            if (0x01 & (pgm_read_dword_near(&imagName[i]) >> j))
            {
              DotScr(posScrX, posScrY + j);
            }
          }
        }

        //次の列へ移動
        posScrX++;
      }
    }


    //一文字表示
    void PutCharScr(byte b)
    {
      if (b < 0x20 || b > 0x7f)
      {
        CelPutScr(font[0x2e - 0x20]);
      }
      else
      {
        CelPutScr(font[b - 0x20]);
      }

      //文字間隔を1ドット分あける
      posScrX++;
    }

    //文字列の表示
    void MesScr(char *c)
    {
      while (*c)
      {
        PutCharScr(*c++);
      }
    }

};
