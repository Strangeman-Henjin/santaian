
#define PI 3.1415926535
#ifndef DANMAKU
#define DANMAKU

//#include "Header.h"
#include "Effect.h"
class Danmaku{

	/*
	ProcessDanmaku,ddan
	*/
public:
#define DANMAKULIMIT 5000
#define DANMAKUCOUNT 20
	Effect eff;
	void Danmaku::ClearDanmaku(){//弾幕データをすべてクリアする
		int clear;
		for (clear = 1; clear < DANMAKULIMIT; clear++){
			dan[clear].x = 0;
			dan[clear].y = 0;
			dan[clear].vecx = 0;
			dan[clear].danshu = 0;
			dan[clear].color = 0;
			dan[clear].imgangle = 0;
			dan[clear].imggapp = 0;
			dan[clear].flamebetween = 0;
			dan[clear].graze = false;
			dan[clear].fb = 0;
			dan[clear].np = 0;
			dan[clear].pp = 0;
			dan[clear].vecy = 0;
			ddan[clear].kanshu = 0;
			ddan[clear].usef = 0;
			ddan[clear].fugou = 0;
			ddan[clear].ready = 0;
			ddan[clear].crosskakudo = 0;
			ddan[clear].crossr = 0;
			ddan[clear].boundcount = 0;
			ddan[clear].karakazeready = 0;
		}
	dan[0].np = 1;
	tail = 1;
	dancount = 0;
	};
	
	void Danmaku::Input_Address(Danmaku * danmaku){
		for (int d = 0; d < 15; d++){
			for (int color = 0; color < 10; color++){
				danimg[d][color] = danmaku->danimg[d][color];
			}
		}
	}
	Danmaku::Danmaku(){
    //弾幕画像登録
	dcolor.white = 0;
	dcolor.red = 1;
	dcolor.orange = 2;
	dcolor.yellow = 3;
	dcolor.green = 4;
	dcolor.water = 5;
	dcolor.blue = 6;
	dcolor.purple = 7;
	dcolor.pink = 8;
	
	//カラー登録
	c.red = GetColor(250,10,10);
	c.orange = GetColor(255, 127, 39);
	c.yellow = GetColor(225, 225, 10);
	c.green = GetColor(10, 10, 250);
	c.water = GetColor(0, 162, 232);
	c.blue = GetColor(10,250,10);
	c.purple = GetColor(200, 200, 10);
	c.white = GetColor(250,250,250);
	
	c.black = GetColor(0,0,0);
	
	//Danmakuクラスの変数初期化
	ClearDanmaku();
	fase = 1;
	//描画調整数の設定
	dgapp[0] = 2;
	dgapp[1] = 2;
	dgapp[2] = 2;
	dgapp[3] = 2;
	dgapp[4] = 7;
	dgapp[5] = 2;

	dgapp[6] = 4;
	dgapp[7] = 4;
	dgapp[8] = 4;
	dgapp[9] = 4;

	dgapp[10] = 5;
	dgapp[11] = 6;

	dgapp[12] = 8;
	dgapp[13] = 10;
	dgapp[14] = 22;

	dgapp[17] = 4;	
	//弾幕の当たり判定の設定
	danhit[0] = 1;
	danhit[1] = 1;
	danhit[2] = 1;
	danhit[3] = 1;
	danhit[4] = 2;
	danhit[5] = 1;
	danhit[6] = 2;
	danhit[7] = 2;
	danhit[8] = 2;
	danhit[9] = 2;
	danhit[10] = 3;
	danhit[11] = 3;
	danhit[12] = 4;
	danhit[13] = 7;
	danhit[14] = 6;
	danhit[17] = 3;
	dancount = 0;
	SetTransColor(0, 0, 0);
	};
	int PasteDanmaku(){
		int r, p;
		r = 0;
		p = dan[0].np;
		SetDrawArea(20, 15, 404, 465);
		while (p != tail && r == 0 && dancount != 0) {
			if (dan[p].danshu == 15 || dan[p].danshu == 16) {
				struct lazer {
					double x;
					double y;
					double vec;
				};
				if (dan[p].x < -200 || dan[p].x > 680 || dan[p].y < -200 || dan[p].y > 680) {
					//画面外にはみ出したら削除
					DeleteDan(p);
				}
				int rr = 0;
				DrawRotaGraph((int)(dan[p].x), (int)(dan[p].y), 1.0, dan[p].imgangle, danimg[dan[p].danshu][dan[p].color], TRUE, FALSE);

				//DrawModiGraph((int)(l1.x), (int)(l1.y), (int)(l2.x), (int)(l2.y), (int)(l3.x), (int)(l3.y), (int)(l4.x), (int)(l4.y) ,danimg[dan[p].danshu][dan[p].color], TRUE);
			}
			else {
				if (dan[p].x < 0 || dan[p].x > 480 || dan[p].y < 0 || dan[p].y > 480) {
					//画面外にはみ出したら削除
					DeleteDan(p);
				}
				else {
					if (dan[p].imgangle == 0) {						
						if (DrawGraph((int)(dan[p].x - dan[p].imggapp), (int)(dan[p].y - dan[p].imggapp), danimg[dan[p].danshu][dan[p].color], true) != 0) { r = -1; }
					}
					else {
						if (DrawRotaGraph((int)(dan[p].x - dan[p].imggapp), (int)(dan[p].y - dan[p].imggapp), 1.0, dan[p].imgangle, danimg[dan[p].danshu][dan[p].color], true, 0) != 0) { r = -1; }
					}
				}
			}
			p = dan[p].np;
		}
		SetDrawArea(0, 0, 639, 479);
		if (r == -1){
			r = -1;
		}
		return r;
	}
	void DeleteDan(int p){
		dan[p].x = -10;
		dan[p].y = -10;
		dan[dan[p].pp].np = dan[p].np;
		dan[dan[p].np].pp = dan[p].pp;
		dancount--;
		if ((dancount == 0 && dan[p].np != tail)) {
			DanmakuRefresh();
		}
	}
	void DeleteDanshu(int dshu) {//特定の弾幕種のみ消去します。
		int p = dan[0].np;
		while (p != tail) {
			if (dan[p].danshu == dshu) {
				DeleteDan(p);
			}
			p = dan[p].np;
		}
	}
	void DeleteDanmakuWithEffect(int p){//弾幕消去をエフェクト込みで行います。
		DeleteDan(p);
	}
	void SetKarakkazeEffect(int p,int kakudo){
		if (ddan[p].karakazeready == 0){
			ddan[p].karakazeready = 30;
			dan[p].vecx = kakudo;
		}
	}
	void EndKarakkazeEffect(int p){
		int k = (int)(dan[p].vecx);//vecxにて設定されていた角度を元に戻す。
		k -= 40;
		k += GetRand(80);
		dan[p].vecx = cos(k * PI / 180) * 2;
		dan[p].vecy = sin(k * PI / 180) * -2;
	}
	void DanmakuRefresh(){
		struct {
			double x;
			double y;
			double vecx;
			double vecy;
			int danshu;
			short color;
			double imgangle;
			int imggapp;
			double fb;
			double flamebetween;
			bool graze;
		}refdan[DANMAKULIMIT] = {};
		struct {
			int fugou;
			int usef ;
			int ready ;
			int kanshu ;
			double crosskakudo ;
			double crossr ;
			int boundcount;
			int karakazeready;
		}reftdan[DANMAKULIMIT] = {};
		int p,pp,endf;
		p = 1;
		pp = dan[0].np;
		while (pp != tail && pp < DANMAKULIMIT - 1 && p < tail + 1){
			refdan[p].x = dan[pp].x;
			refdan[p].y = dan[pp].y;
			refdan[p].vecx = dan[pp].vecx;
			refdan[p].vecy = dan[pp].vecy;
			refdan[p].danshu = dan[pp].danshu;
			refdan[p].color = dan[pp].color;
			refdan[p].imggapp = dan[pp].imggapp;
			refdan[p].imgangle = dan[pp].imgangle;
			refdan[p].flamebetween = dan[pp].flamebetween;
			refdan[p].fb = dan[pp].fb;
			refdan[p].graze = dan[pp].graze;
			reftdan[p].fugou = ddan[pp].fugou;
			reftdan[p].kanshu = ddan[pp].kanshu;
			reftdan[p].ready = ddan[pp].ready;
			reftdan[p].usef = ddan[pp].usef;
			reftdan[p].crosskakudo = ddan[pp].crosskakudo;
			reftdan[p].crossr = ddan[pp].crossr;
			reftdan[p].boundcount = ddan[pp].boundcount;
			reftdan[p].karakazeready = ddan[pp].karakazeready;
			p++;
			pp = dan[pp].np;
		}
		if (p >= tail + 1){
			p = 0;
			dan[p].np = 1;
		}
		ClearDanmaku();
		if(p != 1){
			dancount = p - 1;
			endf = 0;
			tail = p;
			pp = 1;
		}else{
			dancount = 0;
			pp = tail;
			tail = 1;
		}
		while(pp != tail){
			dan[pp].x = refdan[pp].x;
			dan[pp].y = refdan[pp].y;
			dan[pp].vecx = refdan[pp].vecx;
			dan[pp].vecy = refdan[pp].vecy;
			dan[pp].danshu = refdan[pp].danshu;
			dan[pp].color = refdan[pp].color;
			dan[pp].imggapp = refdan[pp].imggapp;
			dan[pp].imgangle = refdan[pp].imgangle;
			dan[pp].fb = refdan[pp].fb;
			dan[pp].flamebetween = refdan[pp].flamebetween;
			dan[pp].graze = refdan[pp].graze;
			ddan[pp].fugou = reftdan[pp].fugou;
			ddan[pp].kanshu = reftdan[pp].kanshu;
			ddan[pp].ready = reftdan[pp].ready;
			ddan[pp].usef = reftdan[pp].usef;
			ddan[pp].crosskakudo = reftdan[pp].crosskakudo;
			ddan[pp].crossr = reftdan[pp].crossr;
			ddan[pp].boundcount = reftdan[pp].boundcount;
			ddan[pp].karakazeready = reftdan[pp].karakazeready;
			dan[pp].pp = pp - 1;
			dan[pp].np = pp + 1;
			pp++;
		}
		if(pp > 10){
			pp = 0;
		}
	}
	//virtual int Danmaku::ProcessDanmaku(int flame,int scene) = 0;
	//virtual int Danmaku::ProcessBossDanmaku(int flame, int scene, int jikinum, int x, int y) = 0;
	void Setdanmaku_Wave(int x, int y, double vec, int danshu, int dancolor, int ready, int skakudo, int kazu){//点(x,y)を中心とした円形の波状弾幕を作成します。
		int zoubunkakudo = 360 /  kazu;
		int setendf = 0;
		if (danshu == dshu.mayu && skakudo == 0){
			skakudo += 1;
		}
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if(dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while(setendf == 0){
			radiun = ((kakudogoukei % 360) == 0 ? 1 : (kakudogoukei % 360)) * PI / 180;
			dan[p].x = x;
			dan[p].y = y;
			dan[p].vecx = vec * cos(radiun);
			dan[p].vecy = vec * sin(radiun) * -1;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
				dan[p].imgangle = radiun;
			}else{
				dan[p].imgangle = 0;
			}
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if(kakudogoukei >= 360 + skakudo - zoubunkakudo){
				setendf = 9;
			}else{
				kakudogoukei += zoubunkakudo;
				p++;
			}
		}
		tail = p + 1;
		dancount += kazu;
		SetDanmakuSE(0, 0, 1);
	}
	void Setdanmaku_Wave2(int x, int y, int kazu, int skakudo = 1, double vec = 1, int danshu = 7, int dancolor = 0, int ready = 0 ,int waveorder = 0 ,double order1 = 0) {//弾幕内容を省略して設定する場合

		int zoubunkakudo = 360 / kazu;
		int setendf = 0;
		if (skakudo == 0) {
			skakudo += 1;
		}
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50) {
			DanmakuRefresh();
		}
		if (dancount == 0 && tail == 1) {
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}
		else {
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while (setendf == 0) {
			radiun = (kakudogoukei % 360) * PI / 180;
			switch (waveorder) {
			case 0://普通弾幕
				radiun = (kakudogoukei % 360) * PI / 180;
				dan[p].x = x;
				dan[p].y = y;
				dan[p].vecx = vec * cos(radiun);
				dan[p].vecy = vec * sin(radiun) * -1;
				if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14) {
					dan[p].imgangle = radiun;
				}
				else {
					dan[p].imgangle = 0;
				}
				break;
			case  1://波状楕円弾幕 vecがX軸の大きさとなりorder1がY軸の大きさとなる。
				dan[p].x = x;
				dan[p].y = y;
				dan[p].vecx = vec * cos(radiun);
				dan[p].vecy = order1 * sin(radiun) * -1;
				if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14) {
					dan[p].imgangle = radiun;
				}
				else {
					dan[p].imgangle = 0;
				}
				break;
			case  2://ツイスト弾幕 order1が角度radiunに対して乗算される。
				dan[p].x = x;
				dan[p].y = y;
				dan[p].vecx = vec * cos(radiun) + vec * cos(order1 * PI / 180);
				dan[p].vecy = (vec * sin(radiun) + vec * sin(order1 * PI / 180)) * -1;
				if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14) {
					dan[p].imgangle = (radiun + order1 * PI / 180);
				}
				else {
					dan[p].imgangle = 0;
				}
				break;
			case  3://回転波状弾幕 vecが円の半径の増分(vecx)、order1が円周を回転する角度になります(vecy)。そしてcrossrが現在の円の半径、crosskakudoが現在の円周の角度位置を示します。
				dan[p].x = x;
				dan[p].y = y;
				ddan[p].crossr = 0;
				ddan[p].crosskakudo = kakudogoukei;
				dan[p].vecx = vec;
				dan[p].vecy = order1;
				dan[p].imgangle = 0;
				break;
			case  4://交差回転波状弾幕 vecが円の半径の増分(vecx)、order1が円周を回転する角度増分になります(vecy)。そして偶数弾だけ回転方向が逆になります。そしてxが現在の円の半径、yが現在の円周の角度位置を示します。
				dan[p].x = x;
				dan[p].y = y;
				ddan[p].crossr = 0;
				ddan[p].crosskakudo = kakudogoukei;
				dan[p].vecx = vec;
				if (p % 2 == 0) {
					dan[p].vecy = order1 * -1;
				}
				else {
					dan[p].vecy = order1;
				}
				dan[p].imgangle = 0;
				break;
			case 5://波状収束弾幕　order1が初期配置される円周上の半径。移動方向が波状弾幕とは逆になる。
				dan[p].x = x + cos(radiun) * order1;
				dan[p].y = y + sin(radiun) * order1;
				dan[p].vecx = cos(radiun) * vec * -1;
				dan[p].vecy = sin(radiun) * vec;
				dan[p].imgangle = radiun * -1;
				break;
			}
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if (kakudogoukei == 360 + skakudo - zoubunkakudo) {
				setendf = 9;
			}
			else {
				kakudogoukei += zoubunkakudo;
				p++;
			}
		}
		tail = p + 1;
		dancount += kazu;
		SetDanmakuSE(0, 0, 1);
	}
	void Setdanmaku_Wave(int x, int y, double vec, int danshu, int dancolor, int ready, int skakudo, int kazu, int waveorder, double order1){//点(x,y)を中心とした特殊な波状弾幕を作成します。1...daen,　2...twist,　3...round,　4...crossround,　order1は各特殊に必要な変数を設定します。
		int zoubunkakudo = 360 / kazu;
		int setendf = 0;
		if (skakudo == 0){
			skakudo += 1;
		}
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if (dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}
		else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while (setendf == 0){
			radiun = (kakudogoukei % 360) * PI / 180;
			switch (waveorder){
			case  1://波状楕円弾幕 vecがX軸の大きさとなりorder1がY軸の大きさとなる。
				dan[p].x = x;
				dan[p].y = y;
				dan[p].vecx = vec * cos(radiun);
				dan[p].vecy = order1 * sin(radiun) * -1;
				if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
					dan[p].imgangle = radiun;
				}
				else{
					dan[p].imgangle = 0;
				}
				break;
			case  2://ツイスト弾幕 order1が角度radiunに対して乗算される。
				dan[p].x = x;
				dan[p].y = y;
				dan[p].vecx = vec * cos(radiun) + vec * cos(order1 * PI / 180);
				dan[p].vecy = (vec * sin(radiun) + vec * sin(order1 * PI / 180)) * -1;
				if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
					dan[p].imgangle = (radiun + order1 * PI / 180);
				}
				else{
					dan[p].imgangle = 0;
				}
				break;
			case  3://回転波状弾幕 vecが円の半径の増分(vecx)、order1が円周を回転する角度になります(vecy)。そしてcrossrが現在の円の半径、crosskakudoが現在の円周の角度位置を示します。
				dan[p].x = x;
				dan[p].y = y;
				ddan[p].crossr = 0;
				ddan[p].crosskakudo = kakudogoukei;
				dan[p].vecx = vec;
				dan[p].vecy = order1;
				dan[p].imgangle = 0;
				break;
			case  4://交差回転波状弾幕 vecが円の半径の増分(vecx)、order1が円周を回転する角度増分になります(vecy)。そして偶数弾だけ回転方向が逆になります。そしてxが現在の円の半径、yが現在の円周の角度位置を示します。
				dan[p].x = x;
				dan[p].y = y;
				ddan[p].crossr = 0;
				ddan[p].crosskakudo = kakudogoukei;
				dan[p].vecx = vec;
				if (p % 2 == 0){
					dan[p].vecy = order1 * -1;
				}
				else{
					dan[p].vecy = order1;
				}
				dan[p].imgangle = 0;
				break;
			case 5://波状収束弾幕　order1が初期配置される円周上の半径。移動方向が波状弾幕とは逆になる。
				dan[p].x = x + cos(radiun) * order1;
				dan[p].y = y + sin(radiun) * order1;
				dan[p].vecx = cos(radiun) * vec * -1;
				dan[p].vecy = sin(radiun) * vec;
				dan[p].imgangle = radiun * -1;
				break;
			
			}
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if (kakudogoukei == 360 + skakudo - zoubunkakudo){
				setendf = 9;
			}
			else{
				kakudogoukei += zoubunkakudo;
				p++;
			}
		}
		tail = p + 1;
		dancount += kazu;
		SetDanmakuSE(0, 0, 1);
	}
	void Setdanmaku_Wave(int x, int y, double vec, int danshu, int dancolor, int ready, int skakudo, int kazu, int waveorder, int order1, int order2){//点(x,y)を中心とした特殊な波状弾幕を作成します。1...point,2...cleam order1,2は各特殊に必要な変数を設定します。
		int zoubunkakudo = 360 / kazu;
		int setendf = 0;
		if (danshu == dshu.mayu && skakudo == 0){
			skakudo += 1;
		}
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if (dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}
		else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while (setendf == 0){
			radiun = (kakudogoukei % 360) * PI / 180;
			switch (waveorder){
			case 2://収束クリーム弾幕
				dan[p].x = x + cos(radiun) * order2;
				dan[p].y = y + sin(radiun) * order2 * -1;
				dan[p].vecx = vec * cos((double)(order1) * PI / 180) * -1;
				dan[p].vecy = vec * sin((double)(order1)* PI / 180);
				break;
			case 3://波状回転収束弾幕 order1が円の初期半径、order2が半径のFlame単位での減分、vecが角度減分になります。
				dan[p].x = x + cos(radiun) * order1;
				dan[p].y = y + sin(radiun) * order1;
				ddan[p].crossr = order1;
				ddan[p].crosskakudo = kakudogoukei;
				dan[p].vecx = vec;
				dan[p].vecy = order2;
				break;
			}
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
				dan[p].imgangle = radiun;
			}
			else{
				dan[p].imgangle = 0;
			}
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if (kakudogoukei == 360 + skakudo - zoubunkakudo){
				setendf = 9;
			}
			else{
				kakudogoukei += zoubunkakudo;
				p++;
			}
		}
		tail = p + 1;
		dancount += kazu;
		SetDanmakuSE(0, 0, 1);
	}
	void Setdanmaku_Daenwave(int x, int y, double vecx, double vecy, int danshu, int dancolor, int ready, int skakudo, int kazu){//点(x,y)を中心とした楕円形の波状弾幕を作成します。vecxが横半径、vecyが縦半径にあたります。
		int zoubunkakudo = (int)(360 /  kazu);
		int setendf = 0;
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if(dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while(setendf == 0){
			radiun = (kakudogoukei % 360) * PI / 180; 
			dan[p].x = x;
			dan[p].y = y;
			dan[p].vecx = vecx * cos(radiun);
			dan[p].vecy = vecy * sin(radiun) * -1;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
				dan[p].imgangle = radiun;
			}
			else{
				dan[p].imgangle = 0;
			}
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if(kakudogoukei == 360 + skakudo - zoubunkakudo){
				setendf = 9;
			    }else{
					 kakudogoukei += zoubunkakudo;
					 p++;
			         }
		}
		tail = p + 1;
		dancount += kazu;
	}
	void Setdanmaku_Pointwave(int x, int y, int flametime, int danshu, int dancolor, int ready, int skakudo, int pointx, int pointy, int r, int kazu){//flametime = ポイント(pointx,pointy)を中心とした波状位置に何フレームで到達するか
		int zoubunkakudo = (int)(360 /  kazu);
		int setendf = 0;
		int kakudogoukei = skakudo;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if(dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun,dx,dy;
		while(setendf == 0){
			dan[p].x = x;
			dan[p].y = y;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 9 && danshu != 13 && danshu != 14){
				dan[p].imgangle = skakudo * PI / 180;
			}else{
				dan[p].imgangle = 0;
			}
			radiun = (kakudogoukei % 360) * PI / 180;
			dx = pointx + r * cos(radiun);
			dy = pointy + r * sin(radiun);
			dan[p].vecx = (dx - x) / flametime;
			dan[p].vecy = (dy - y) / flametime;
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if(kakudogoukei == 360 + skakudo - zoubunkakudo){
				setendf = 9;
			    }else{
					 kakudogoukei += zoubunkakudo;
					 p++;
			         }
		}
		tail = p + 1;
		dancount += kazu;
	};
	void Setdanmaku_Ko(int x, int y, double vec, int danshu, int dancolor, int ready, int skakudo, int ekakudo, int kazu){
		//点(x,y)を中心とした扇状の弾幕を作成します。skakudoは扇の左端、ekakudoは扇の右端とします。
		if (danshu == dshu.mayu && (skakudo < 360 && ekakudo > 360) || (skakudo > 360 && ekakudo < 360) || (skakudo > 360 && ekakudo > 0) || (skakudo < 0 && ekakudo > 0)){
			skakudo += 1;
			ekakudo += 1;
		}
		if (ekakudo < skakudo){
			int k = ekakudo;
			ekakudo = skakudo;
			skakudo = k;
		}
	    int kakudo = (ekakudo - skakudo) / (kazu - 1);
		int kakukei = skakudo;
		int setendf = 0;
		int p;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if(dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}else{
			//それ以外はtailに配置
			p = tail;
		}
		double radiun;
		while(setendf == 0){
			radiun = ((kakukei % 360) == 0 ? 1 : (kakukei % 360)) * PI / 180;
			dan[p].x = x;
			dan[p].y = y;
			dan[p].vecx = vec * cos(radiun);
			dan[p].vecy = vec * sin(radiun) * -1;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			dan[p].imgangle = radiun;
			ddan[p].ready = ready;
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			if(kakukei >= ekakudo){
				setendf = 9;
			}else{
				p++;
				kakukei += kakudo;
			}
		}
		tail = p + 1;
		dancount += kazu;
		SetDanmakuSE(0, 0, 3);
	}
	void Setdanmaku_ChainRendan(int x, int y, double vec, double kakudo, int danshu, int dancolor, int ready ,int kazu, int danmakubetween){
		//角kakudo方向の連続弾幕を作成します。fbとvecは一番最後に発射される弾幕を基準とします。
		//danmakubetweenは連続して発射される弾幕の発射間隔(フレーム単位)を表します。
		if (kazu == 0){
			return;
		}
		int p,d;
		double radiun = kakudo * PI / 180;
		if (dancount + kazu > DANMAKULIMIT - 50){
			DanmakuRefresh();
		}
		if(dancount == 0 && tail == 1){
			//一発目の弾幕はdan[1]に配置
			p = 1;
			
		}
		else{
			p = tail;
		}
		for(d = 1;d < kazu + 1;d++){
			dan[p].x = x;
			dan[p].y = y;
			dan[p].vecx = vec * cos(radiun);
			dan[p].vecy = vec * sin(radiun) * -1;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if(danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 13 && danshu != 14){
				dan[p].imgangle = radiun;
			}else{
				dan[p].imgangle = 0;
			}
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			ddan[p].ready = (d - 1) * danmakubetween + ready;
			p++;
		}
		tail = p;
		dancount += kazu;
		SetDanmakuSE(0, 0, 4);
	}
	void Setdanmaku_ArrowRendan(int x, int y, double kakudo, int danshu, int dancolor, int ready, int kazu, double fastestvec, double slowestvec) {/*角kakudo方向の一斉発射弾幕を作成します。fbとvecは一番最後に発射される弾幕を基準とします。
		//発射される弾幕は角度と発射タイミングは同一ですがスピードが異なります。
		//fastestspeedは同時に発射される弾幕のうち最も速いスピード、slowestspeedは同じく最も遅いスピード(他のSetdanmakuにおけるvec)となります。*/
		int p, d;
		double radiun = kakudo * PI / 180;
		if (dancount + kazu > DANMAKULIMIT - 50) {
			DanmakuRefresh();
		}
		if (dancount == 0 && tail == 1) {
			//一発目の弾幕はdan[1]に配置
			p = 1;
		}
		else {
			//それ以外はtailに配置
			p = tail;
		}
		double speed = 0;
		if (kazu == 2) {
			speed = slowestvec;
		}
		else {
			speed = (double)(fastestvec - slowestvec) / (kazu - 1);
		}
		for (d = 1; d < kazu + 1; d++) {
			dan[p].x = x;
			dan[p].y = y;
			dan[p].danshu = danshu;
			dan[p].color = dancolor;
			dan[p].imggapp = dgapp[danshu];
			if (danshu != 0 && danshu != 2 && danshu != 6 && danshu != 7 && danshu != 13 && danshu != 14) {
				dan[p].imgangle = radiun;
			}
			else {
				dan[p].imgangle = 0;
			}
			dan[p].graze = false;
			dan[p].pp = p - 1;
			dan[p].np = p + 1;
			//速度ずらし連弾
				/*
				vec = (int)(vec / d);
				*/
			ddan[p].ready = ready;
			dan[p].vecx = slowestvec * cos(radiun);
			dan[p].vecy = slowestvec * sin(radiun) * -1;
			p++;
			slowestvec += speed;
		}
		tail = p;
		dancount += kazu;
		SetDanmakuSE(0, 0, 5);
	}
	void Setdanmaku_Line(int sx, int sy, int ex, int ey, double vec, int danshu, int dancolor, int ready, int kazu, int lineorder,int order1,int order2){
		/*LineOrder一覧
			0.karten　直線から垂直に線形のまま移動します。order1では左右の指定(1が右方向、-1が左方向)、order2が上下の指定(1が下方向、-1が上方向）となります。
			1.target　線上の弾幕が一点に向かって移動します。
			2.
		*/
	}
	int Getkakudo_Homing(double sx,double sy,double ex,double ey){//点(sx,sy)から見た点(ex,ey)の角度を返します。
		double dx = ex - sx;
		double dy = ey - sy;
		return (int)(atan2(dy, dx) * 180 / PI);
	}
	void ChangeDanmakuExpress(int sp, int ep, int changeorder, double order1, double order2){
		int d;
		for (int p = sp; p < ep; p++){
			switch (changeorder){
			case 0://(order1)フレームだけ待機 wait
				ddan[p].ready = (int)(order1);
				break;
			case 1://order1角度方向へorder2の速度で方向転換	target
				dan[p].vecx = order2 * cos(order1 * PI / 180);
				dan[p].vecy = order2 * sin(order1 * PI / 180) * -1;
				p = p;
				break;
			case 2://元の移動方向＋order1度方向へorder2の速度でツイスト twist
				d = (int)(atan2(dan[p].vecy, dan[p].vecx) * 180 / PI);
				dan[p].vecx = order2 * cos((order1 + d) * PI / 180);
				dan[p].vecy = order2 * sin((order1 + d) * PI / 180) * -1;
				break;
			case 3://spからepまでの波状円の円周上を回転。order1がフレームあたりの回転角度、order2がフレームあたりの増分半径とする。round
				ddan[p].crossr = 0;
				ddan[p].crosskakudo = atan2(dan[p].vecy * -1, dan[p].vecx) * 180 / PI;
				dan[p].vecy = order1;
				dan[p].vecx = order2;
				break;
			}
		}
	}
	void ProcessBound(int p){//指定された弾幕のバウンド処理を行います。
		int kakudo;
		bool b;
		b = false;
		if (dan[p].x + dan[p].vecx > 410)
		{
			b = true;
			dan[p].vecx *= -1;
			dan[p].x = 410;
			kakudo = (int)(dan[p].imgangle * 180 / PI);
			if (dan[p].vecy > 0){
				dan[p].imgangle = (180 - kakudo) * PI / 180;
			}
			else{
				dan[p].imgangle = (540 - kakudo) * PI / 180;
			}
		}
		if (dan[p].x - dan[p].vecx < 10)
		{
			b = true;
			dan[p].x = 10;
			dan[p].vecx *= -1;
			kakudo = (int)(dan[p].imgangle * 180 / PI);
			if (dan[p].vecy > 0){
				dan[p].imgangle = (180 - kakudo) * PI / 180;
			}
			else{
				dan[p].imgangle = (540 - kakudo) * PI / 180;
			}
		}
		if (dan[p].y - dan[p].vecy < 5)
		{
			b = true;
			dan[p].y = 5;
			dan[p].vecy *= -1;
			kakudo = (int)(dan[p].imgangle * 180 / PI);
			dan[p].imgangle = (360 - kakudo) * PI / 180;
		}
		if (dan[p].y + dan[p].vecy > 475)
		{
			b = true;
			dan[p].y = 475;
			dan[p].vecy *= -1;
			kakudo = (int)(dan[p].imgangle * 180 / PI);
			dan[p].imgangle = (360 - kakudo) * PI / 180;
		}
		if (b) {
			ddan[p].boundcount++;
		}
	}
	void SetDanmakuSE(int order, int danshu, int formation) {//SetDanmakuで設置された弾幕と同時にSEを鳴らします。orderは基本0ですがオーダーメイドの場合のみ指定されます。
		if (order == 0) {
			if (danshu == 0) {
				switch(formation) {
			case 1://Wave
				order = 7;
				break;
			case 2://Pointwave
				order = 8;
				break;
			case 3://Ko
				order = 2;
				break;
			case 4://ChainRendan
				order = 5;
				break;
			case 5://ArrowRendan
				order = 6;
				break;
				}
			}
			else {
				
			}
			if (SEdan == false) {
				switch (order) {
				case 1://ジュウゥゥゥゥ…
					eff.RequestSE(eff.se.dan1);
					break;
				case 2://キリリキリリ…
					eff.RequestSE(eff.se.dan2);
					break;
				case 3://ﾊﾟｧﾝ…
					eff.RequestSE(eff.se.dan3);
					break;
				case 4://ヒュウドオオン
					eff.RequestSE(eff.se.dan4);
					break;
				case 5://バアン！
					eff.RequestSE(eff.se.dan5);
					break;
				case 6://パチュウオオン
					eff.RequestSE(eff.se.dan6);
					break;
				case 7://ジングル
					eff.RequestSE(eff.se.dan7);
					break;
				case 8://ブォォン
					eff.RequestSE(eff.se.dan8);
					break;
				}
			}
			else {
				SEdan = false;

			}
		}
		else{
			if (danshu != 0) {
				switch (danshu) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
				case 15:
					break;
				case 16:
					break;
				case 17:
					break;
				case 18:
					break;
				case 19:
					break;
				case 20:
					break;
				}
			}
			switch (order) {
			case 1://ジュウゥゥゥゥ…
				eff.RequestSE(eff.se.dan1);
				break;
			case 2://キリリキリリ…
				eff.RequestSE(eff.se.dan2);
				break;
			case 3://ﾊﾟｧﾝ…
				eff.RequestSE(eff.se.dan3);
				break;
			case 4://ヒュウドオオン
				eff.RequestSE(eff.se.dan4);
				break;
			case 5://バアン！
				eff.RequestSE(eff.se.dan5);
				break;
			case 6://パチュウオオン
				eff.RequestSE(eff.se.dan6);
				break;
			case 7://ジングル
				eff.RequestSE(eff.se.dan7);
				break;
			case 8://ブォォン
				eff.RequestSE(eff.se.dan8);
				break;
			}
			SEdan = true;
		}
	}
	
	
	double rx;
	double ry;//rx,ryともに返答用の変数
	double Danmaku::GetY(double x, int usef, int kanshu){
		/*一次・二次関数のY座標を得る関数です。
		kは kanshu = 0の時は一次関数、kanshu = 1の時は二次関数の添え字になります。
		*/


		switch (kanshu){
		case 0://一次関数Y = aX + b
			ry = Ichiji[1][usef] * x + Ichiji[2][usef];
			break;
		case 1://二次関数Y = a(X - p)²+ q
			ry = Niji[1][usef] * pow(x - Niji[2][usef], 2.0) + Niji[3][usef];
			break;
		default:
			ry = -9999;
			break;
		}
		return ry;
	}
	double Danmaku::GetY(double x, int usef, int kanshu, int fugou){
		/*円・楕円関数からY座標を得る関数です。fugouが-1の時は中心点より上・左寄りに、1の時は下・右寄りになります。
		またkは、kanshu = 2の時は円関数、kanshu = 3の時は楕円関数の添え字になります。
		*/


		switch (fugou){
		case 1:
			break;
		case -1:
			break;
		default:
			return -9999;

		}
		double sq;
		switch (kanshu){

		case 2://円関数(X - a)²+(Y - b)²=r²
			ry = sqrt(pow(En[3][usef], 2.0) - pow(x - En[1][usef], 2.0))*fugou + En[2][usef];
			break;
		case 3://楕円関数(X - a)²/p²+(Y - b)²/q² = 1
			sq = pow(Daen[4][usef], 2.0) - pow(Daen[4][usef] * (x - Daen[1][usef]), 2.0) / pow(Daen[3][usef], 2.0);
			if (sq < 0){
				ry = -9999;
			}
			else{
				ry = sqrt(sq)*fugou + Daen[2][usef];
			}
			break;
		default:
			ry = -9999;
			break;
		}

		return ry;
	}
	double Danmaku::GetX(double y, int usef){
		/*一次関数のX座標を得る関数です。
		kは 0 ～　***　～999までは一次関数の添え字になります。
		*/
		return (y - Ichiji[2][usef]) / Ichiji[1][usef];
	}
	double Danmaku::GetX(double y, int usef, int kanshu, int fugou){
		/*二次・円・楕円関数からX座標を得る関数です。fugouが-1の時は中心点より上・左寄りに、1の時は下・右寄りになります。
		またkは kanshu = 1の時は二次関数、kanshu = 2の時は円関数、kanshu = 3の時は楕円関数の添え字になります。
		*/

		double sq;
		switch (fugou){
		case 1:
			break;
		case -1:
			break;
		default:
			return -9999;
		}
		switch (kanshu){
		case 1:
			rx = sqrt((y - Niji[3][usef]) / Niji[1][usef]) * fugou + Niji[2][usef];
			break;
		case 2://円関数(X - a)²+(Y - b)²=r²
			rx = sqrt(pow(En[3][usef], 2.0) - pow(y - En[2][usef], 2.0))*fugou + En[1][usef];
			break;
		case 3://楕円関数(X - a)²/p²+(Y - b)²/q² = 1
			sq = pow(Daen[3][usef], 2.0) - pow(Daen[3][usef] * (y - Daen[2][usef]), 2.0) / pow(Daen[4][usef], 2.0);
			if (sq < 0){
				rx = -9999;
			}
			else{
				rx = sqrt(sq)*fugou + Daen[1][usef];
			}
			break;
		default:
			rx = -9999;
			break;
		}
		return rx;
	}
	void Danmaku::GetXYRadtoScal(int kakudo,int usef,int kanshu,double &x,double &y) {//角度を関数を元にXY座標(スカラー値)に変換します。kanshu[2.円関数,3.楕円関数]
		switch (kanshu) {
		case 2://円関数
			x = En[3][usef] * cos(kakudo * PI / 180) + En[1][usef];
			y = En[3][usef] * cos(kakudo * PI / 180) + En[2][usef];
			break;
		case 3://楕円関数
			x = Daen[3][usef] * cos(kakudo * PI / 180) + Daen[1][usef];
			y = Daen[4][usef] * cos(kakudo * PI / 180) + Daen[2][usef];
			break;
		default:
			break;
		}
	}
	void Danmaku::UseKansu(double &x, double &y, int usef, int kanshu, int kakudo){
		switch (kanshu){
		case 2://円関数
			x = cos(kakudo * PI / 180) * En[3][usef] + En[1][usef];
			y = sin(kakudo * PI / 180) * En[3][usef] + En[2][usef];
			break;
		case 3://楕円関数
			x = cos(kakudo * PI / 180) * En[3][usef] + En[1][usef];
			y = sin(kakudo * PI / 180) * En[4][usef] + En[2][usef];
			break;
		}
	}
	void Danmaku::Clearkansu(){
		ck.ichiji = 0;
		ck.niji = 0;
		ck.en = 0;
		ck.daen = 0;
		for (int kk = 0; kk < 30; kk++){
			Ichiji[1][kk] = 0;
			Ichiji[2][kk] = 0;
			Niji[1][kk] = 0;
			Niji[2][kk] = 0;
			Niji[3][kk] = 0;
			En[1][kk] = 0;
			En[2][kk] = 0;
			En[3][kk] = 0;
			Daen[4][kk] = 0;
			Daen[1][kk] = 0;
			Daen[2][kk] = 0;
			Daen[3][kk] = 0;
		}
	}
	int Danmaku::Inputkansucount(int k, int kanshu){
		/*関数の数をkにします。基本的に減ることはないです。0 = 成功、-1 =　失敗
		初期化する際はClearkansuを使用します。0 = 一次関数, 1 = ニ次関数, 2 = 円関数, 3 = 楕円関数
		*/
		switch (kanshu){
		case 0:
			ck.ichiji = k;
			break;
		case 1:
			ck.niji = k;
			break;
		case 2:
			ck.en = k;
			break;
		case 3:
			ck.daen = k;
			break;
		default:
			return -1;

		}
		return 0;
	}
	void Danmaku::Inputkansu(char* stagename){
		int f;
		f = _chdir("data");
		f = _chdir("Stage");
		f = _chdir(stagename);
		Clearkansu();
		int file = FileRead_open("CalcData.csv");
		char* ctx = "";
		TCHAR data[70] = "";
		int datalen = sizeof(data);
		int endflg = 0;
		int kanshu;
		while (endflg == 0){
			ZeroMemory(data, datalen);
			f = FileRead_gets(data, 70, file);
			if (FileRead_eof(file) != 0){ endflg = 100; }
			kanshu = atoi(strtok_s(data, ",", &ctx));
			switch (kanshu){
			case 1://一次関数
				ck.ichiji++;
				Ichiji[1][ck.ichiji] = atof(strtok_s(NULL, ",", &ctx));
				Ichiji[2][ck.ichiji] = atof(strtok_s(NULL, ",", &ctx));
				break;
			case 2://二次関数
				ck.niji++;
				Niji[1][ck.niji] = atof(strtok_s(NULL, ",", &ctx));
				Niji[2][ck.niji] = atof(strtok_s(NULL, ",", &ctx));
				Niji[3][ck.niji] = atof(strtok_s(NULL, ",", &ctx));
				break;
			case 3://円関数
				ck.en++;
				En[1][ck.en] = atof(strtok_s(NULL, ",", &ctx));
				En[2][ck.en] = atof(strtok_s(NULL, ",", &ctx));
				En[3][ck.en] = atof(strtok_s(NULL, ",", &ctx));
				break;
			case 4://楕円関数
				ck.daen++;
				Daen[1][ck.daen] = atof(strtok_s(NULL, ",", &ctx));
				Daen[2][ck.daen] = atof(strtok_s(NULL, ",", &ctx));
				Daen[3][ck.daen] = atof(strtok_s(NULL, ",", &ctx));
				Daen[4][ck.daen] = atof(strtok_s(NULL, ",", &ctx));
				break;
			}
		}
		f = _chdir("..");
		f = _chdir("..");
		f = _chdir("..");
	}
	int Danmaku::DirectInputkansu_ichiji(double a, double b){
		/*
		プログラムから一次関数を登録する関数です。返り値は登録された一次関数の添え字です。
		添え字はY = aX + bに該当します。関数の数は自動的に更新されます。
		*/
		ck.ichiji++;
		Ichiji[1][ck.ichiji] = a;
		Ichiji[2][ck.ichiji] = b;
		return ck.ichiji;
	}
	int Danmaku::DirectInputkansu_en(double a, double b, double r){
		/*
		プログラムから円関数を登録する関数です。返り値は登録された円関数の添え字です。
		添え字は(Y - a)²+(X - b)² = r²に該当します。関数の数は自動的に更新されます。
		*/
		ck.en++;
		En[1][ck.en] = a;
		En[2][ck.en] = b;
		En[3][ck.en] = r;

		return ck.en;
	}
	int Danmaku::DirectInputkansu_en_3point(int px1, int py1, int px2, int py2, int px3, int py3) {
		struct dessin {
			int num;
			int x;
			int y;
			int k;
		};
		dessin des[4];
		struct EN {
			double l;
			double m;
			double n;
		};
		EN ven[4];
		double L, M, N;//X ^ 2 + Y ^ 2 + XL + YM + N = 0
		double a, b, r;//(X - a) ^2 + (Y - b) ^2 = r ^ 2				
		double l, ll, m, n, nn;
		N = pow(des[1].x, 2.0) + pow(des[1].y, 2.0);
		des[1].x = px1;
		des[1].y = py1;
		des[2].x = px2;
		des[2].y = py2;
		des[3].x = px3;
		des[3].y = py3;
		for (int e = 1; e < 4; e++) {
			ven[e].l = des[e].x;
			ven[e].m = des[e].y;
			ven[e].n = pow(des[e].x, 2.0) + pow(des[e].y, 2.0);
		}
		nn = ven[3].n;
		ven[3].l *= -1;
		ven[3].m *= -1;
		ven[3].n *= -1;
		for (int e = 1; e < 3; e++) {
			ven[e].l += ven[3].l;
			ven[e].m += ven[3].m;
			ven[e].n += ven[3].n;
		}
		l = ven[2].l;
		ll = ven[1].l;
		m = ven[1].m;
		n = ven[1].n;
		ven[2].l *= ven[1].l;
		ven[2].m *= ven[1].l;
		ven[2].n *= ven[1].l;
		ven[1].l *= l;
		ven[1].m *= l;
		ven[1].n *= l;

		ven[1].m -= ven[2].m;
		ven[1].n -= ven[2].n;
		M = ven[1].n / ven[1].m * -1;
		ven[1].m = m * M + n;
		L = ven[1].m  * -1 / ll;
		N += ven[3].l * L + ven[3].m * M + nn;
		if (pow(L, 2.0) + pow(M, 2.0) - N * 4 < 0) {
			//return -1;
		}
		a = L / -2;
		b = M / -2;
		r = sqrt(pow(a - des[1].x, 2.0) + pow(b - des[1].y, 2.0));
		return DirectInputkansu_en(a, b, r);
	}
	int Danmaku::DirectInputkansu_niji(double a, double p, double q){
		/*
		プログラムから二次関数を登録する関数です。返り値は登録された二次関数の添え字です。
		添え字はY = a(X - p)² + qに該当します。関数の数は自動的に更新されます。
		*/
		ck.niji++;
		Niji[1][ck.niji] = a;
		Niji[2][ck.niji] = p;
		Niji[3][ck.niji] = q;
		return ck.niji;
	}
	int Danmaku::DirectInputkansu_daen(double a, double b, double p, double q){
		/*
		プログラムから楕円関数を登録する関数です。返り値は登録された楕円関数の添え字です。
		添え字は(X - a)²/p²+(Y - b)²/q² = 1に該当します。関数の数は自動的に更新されます。
		*/
		ck.daen++;
		Daen[1][ck.daen] = a;
		Daen[2][ck.daen] = b;
		Daen[3][ck.daen] = p;
		Daen[4][ck.daen] = q;
		return ck.daen;
	}

	struct Count_kansu{
		int ichiji;
		int niji;
		int en;
		int daen;
	};
	struct Count_kansu ck;
	//関数の数を記録する構造体です。
    struct COLOR{
	    static int red;
		static int yellow;
		static int green;
		static int blue;
		static int purple;
		static int black;
		static int white;
		static int pink;
		static int water;
		static int orange;
		static int glay;
	};
	COLOR c;
	struct DCOLOR{
		static short red;
		static short yellow;
		static short green;
		static short blue;
		static short purple;
		static short black;
		static short white;
		static short pink;
		static short water;
		static short orange;
		static short glay;
	};
	DCOLOR dcolor;
	struct WAVEORDER{
		static short daen;//XY軸で異なる楕円状の軌道が設定されます。次の引数にY軸の速度が設定されます(vecはX軸のものとする)。
		static short twist;//初期位置から捻じ曲がるように軌道が設定されます。次の引数に捻じ曲げる角度が設定されます。
		static short round;//弾幕が同じ円周に沿って回転しながら広がっていく起動を設定します。次の引数にフレーム単位での回転角度が設定されます(この時の弾幕処理は特殊で、vecxが円の半径の増分、vecyが回転角度の増分となります)。さらにvecは波状円半径の増分になります。
		static short crossround;//弾幕が同じ円周上を交差しながら回転し、広がっていく軌道を設定します。引数とvecx,vecyの役割はroundと同様ですが偶数弾のみ逆回転となります。
		static short cleam;//twistが内向きになる軌道が設定されます。order1に捻じ曲がる角度、order2に初期位置となる円の半径が設定されます(この場合最初に発射されだ波状弾幕を消去しつつ新たなクリーム波状弾幕を設定する仕組みである。さらに引数のx,y座標は収束していく円の中心座標とする)。
		static short point;//指定ポイントを中心とした円へと移動する波状弾幕を設定します。order1には指定ポイント円への角度、order2には指定ポイント円の半径を指定します。
		static short reverse;//波状収束弾幕。初期配置が円周上に設置され、円中央に向かうように弾幕外装する。
		static short capture;//波状回転収束弾幕。初期配置の円周上から、回転しつつ円中央に向かうよう弾幕処理を行う。
	};
	WAVEORDER worder;
	struct CHANGEORDER{
		static short wait;
		static short target;
		static short twist;
		static short round;
	};
	CHANGEORDER changeorder;
	struct DAN{
    //最低限必要な弾幕情報です。そのほかの情報はGameクラス内のメソッドで使います。
		double x;//弾幕位置のＸ座標。小数点以下も記録するが引数として使う時はint型として呼び出される。
		double y;//弾幕位置のＹ座標。小数点以下も記録するが引数として使う時はint型として呼び出される。
		double vecx;//Ｘ軸方向への移動速度。1フレーム更新あたりとする。また関数弾幕の時はvecxが角度増分となり、vecyへ加算することで角度を変更する。
		double vecy;//Y軸方向への移動速度。1フレーム更新あたりとする。また関数弾幕の時はvecyが現在角度となり、GetXYRadtoScalで座標に変換する。
		int danshu;//弾幕の種類
		int color;//弾幕の色
		double imgangle;//弾幕画像の貼り付け角度を示す変数です。ラジアン型とし、弾幕の種類によっては計算されません(0,2,6,7,13,14)
		int imggapp;//あたり判定は弾幕の中心点から計算するため、DrawGraphでは半径距離分左上に描画する。
		double flamebetween;//弾幕更新頻度。フレーム更新を何回スキップするかを表す。
		double fb;//ProcessDanmakuにおいて1以上の時は更新されず、0になるとflamebetweenからコピーされる。
		bool graze;//グレーズしたかどうかを判定する変数です。falseの時はグレーズをカウントし、trueにします。
		int np;//次のポインタ
		int pp;//前のポインタ
	};
	DAN dan[DANMAKULIMIT];
	struct tdan{//必要に応じて使われる弾幕情報です。
		int usef;//使用する関数のポインタ
		int fugou;//二次、円、楕円関数使用時の符号。-1だと左上寄りになり、1だと右下寄りになります。
		int kanshu;//関数の種類を示す変数。GetX,GetY関数を使用するときに一次～楕円関数を区別します。
		int ready;//Rendan関数などで弾幕の発射までのカウントや一時停止してから再度移動するまでのカウントを示します。
		double crosskakudo;
		double crossr;
		int boundcount;//画面内でバウンドした回数を示す変数です。
		int karakazeready;//空っ風エフェクト発生直後に設定される停止カウントです。これが0になると指定された角度±40度の角度へランダムに弾幕機動が変更されます。
		/*
		char * ordername1;//
		double order1;
		char * ordername2;//
		double order2;
		char * ordername3;//
		double order3;
		*/
	};
	tdan ddan[DANMAKULIMIT];
	static int danimg[DANMAKUCOUNT][10];
	struct DANSHU{
		static short tubu;
		static short kome;
		static short hoshi;
		static short hahen;
		static short uroko;
		static short kunai;
		static short ring;
		static short middle;
		static short twin;
		static short onpu;
		static short key;
		static short knife;
		static short mayu;
		static short large;
		static short big;
		static short lazer;
		static short biglazer;
		static short heart;
		static short plate;
		static short bigplate;
	};
	DANSHU dshu;
	/*            white:0 red:1 blue:2 yellow:3 green:4 pink:5 purple:6 water:7 orange:8 glay:9 black:10
	int tubu;//0
	int kome;//1
	int hoshi;//2
	int hahen;//3
	int uroko;//4
	int kunai;//5

	int ring;//6
	int middle;//7
	int twin;//8
	int onpu;//9
		
	int key;//10
	int knife;//11

	int mayu;//12
	int large;//13
	int big;//14
	
	int lazer;//15
	int biglazer;//16
	int heart;//17

	short plate;//18
	short bigplate;//19
	};
	*/
	
	//弾幕画像の変数。Danmakuコントラクタで画像が読み込まれ、この変数に設定される。

	static short dgapp[DANMAKUCOUNT];
    	//弾幕画像を張り付けるときの調整数。Danmakuコントラクタで設定される。
    
	static short danhit[DANMAKUCOUNT];//弾幕のあたり判定を行うための変数。判定はレーザー弾幕を除き円で行う。変数はその円の半径とする。Danmakuコントラクタで設定される。
	short dancount;//弾幕数を保持する変数です。
	short fase;//フェーズ変数
	short prefase;//更新前のフェーズを記録し、フェーズの変化を判定する。
	static short tail;//ProcessDanmakuにおいて保存・利用されるdan配列の終端
	double Ichiji[3][30];//1.a, 2.b        Y = aX + b 
	double En[4][30];//1.a, 2.b, 3.r       (X - a)^2 + (Y - b)^2 = r^2
	double Niji[4][30];//1.a, 2.p, 3.q     Y = a(X - p)^2 + q 
	double Daen[5][30];//1.a, 2.b, 3.p 4.q {(X - a)^2 } / p^2 + {(Y - b)^2} / q^2 = 1
	static bool SEdan;//SetDanmakuの前にSEが予約されたかを示す変数です。SetDanmakuSEでこれがtrueの場合はSEを鳴らしません。
};
int Danmaku::COLOR::black = 0;
int Danmaku::COLOR::blue = 0;
int Danmaku::COLOR::green = 0;
int Danmaku::COLOR::purple = 0;
int Danmaku::COLOR::red = 0;
int Danmaku::COLOR::white = 0;
int Danmaku::COLOR::yellow = 0;
int Danmaku::COLOR::pink = 0;
int Danmaku::COLOR::water = 0;
int Danmaku::COLOR::orange = 0;
short Danmaku::DCOLOR::white = 0;
short Danmaku::DCOLOR::red = 1;
short Danmaku::DCOLOR::orange = 2;
short Danmaku::DCOLOR::yellow = 3;
short Danmaku::DCOLOR::green = 4;
short Danmaku::DCOLOR::water = 5;
short Danmaku::DCOLOR::blue = 6;
short Danmaku::DCOLOR::purple = 7;
short Danmaku::DCOLOR::pink = 8;
short Danmaku::DCOLOR::glay = 9;
short Danmaku::DCOLOR::black = 10;
short Danmaku::DANSHU::tubu = 0;
short Danmaku::DANSHU::kome = 1;
short Danmaku::DANSHU::hoshi = 2;
short Danmaku::DANSHU::hahen = 3;
short Danmaku::DANSHU::uroko = 4;
short Danmaku::DANSHU::kunai = 5;
short Danmaku::DANSHU::ring = 6;
short Danmaku::DANSHU::middle = 7;
short Danmaku::DANSHU::twin = 8;
short Danmaku::DANSHU::onpu = 9;
short Danmaku::DANSHU::key = 10;
short Danmaku::DANSHU::knife = 11;
short Danmaku::DANSHU::mayu = 12;
short Danmaku::DANSHU::large = 13;
short Danmaku::DANSHU::big = 14;
short Danmaku::DANSHU::lazer = 15;
short Danmaku::DANSHU::biglazer = 16;
short Danmaku::DANSHU::heart = 17;
short Danmaku::DANSHU::plate = 18;
short Danmaku::DANSHU::bigplate = 19;
short Danmaku::WAVEORDER::daen = 1;
short Danmaku::WAVEORDER::twist = 2;
short Danmaku::WAVEORDER::round = 3;
short Danmaku::WAVEORDER::crossround = 4;
short Danmaku::WAVEORDER::reverse = 5;
short Danmaku::WAVEORDER::capture = 3;
short Danmaku::WAVEORDER::cleam = 1;
short Danmaku::WAVEORDER::point = 2;
short Danmaku::CHANGEORDER::wait = 1;
short Danmaku::CHANGEORDER::target = 2;
short Danmaku::CHANGEORDER::twist = 3;
short Danmaku::CHANGEORDER::round = 4;
bool Danmaku::SEdan = false;

int Danmaku::danimg[DANMAKUCOUNT][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
short Danmaku::dgapp[DANMAKUCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
short Danmaku::danhit[DANMAKUCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
short Danmaku::tail = 0;
#endif