/*
1525050250

【作品】
ヘリコプター

【プログラムの使い方】
・プログラムを開始すると、ヘリコプターは着陸している状態で静止している。
・マウスの左ボタン押下で、ヘリコプターは、半径5の円軌道から半径9の円軌道へ
  らせん運動を行いながら上昇する。
  なお、一度のマウスの左ボタン押下で、ヘリコプターは中央部の建物の周りを飛行し続ける。
・マウスの左ボタン押下をもう一度実行すると、ヘリコプターの動きを一時停止できる。
・マウスの右ボタン押下で、ヘリコプターは、進行方向を軸に自転する。
・キーボードの『f』キーを押すと、半径9の円軌道を保ったまま徐々に降下した後地面に着陸し、静止する。

・オプションとして以下の機能を付与しており、キーボードの対応するキーを押すことによって、自由に視点を移動させることができる。
 ・『d』キー：視点右回転
 ・『a』キー：視点左回転
 ・『w』キー：視点上昇
 ・『x』キー：視点降下
 ・『e』キー：視点ズームイン（z軸負の負の方向へ移動）
 ・『c』キー：視点ズームアウト（z軸正の方向へ移動）
 ・『z』キー：視点リセット（視点を初期状態に戻す）
 ・『q』、『Q』、『ESC』キー：プログラム終了


【プログラムの説明】
・ヘリコプターを構成するに当たり、、
　（１）機体部分[ body ]（六面体2つ）
　（２）回転翼部分[ rotor ]（球1つとプロペラ（六面体）4つ）
　（３）後尾部分[ tailboom ]（四面体1つ）
　（４）後尾翼と後尾回転翼部分[ tailwing とtailrotor ] (六面体1つと球1つとプロペラ（六面体）4つ)
の計14個の立体を使用した。

・（１）機体部分では、五角柱を作成するために、六面体一つと、大きさを変えた六面体を180度回転させた立体を組み合わせている。
・（２）回転翼部分では、球の下位の階層として、プロペラ（六面体）4つをそれぞれ90度ずつ回転させた立体を組み合わせている。
　　　　また、球を回転させるように記述することで、プロペラも回転させている。
・（３）後尾部分は、機体と一体化するように四面体を平行移動させて設置している。
・（４）後尾翼部分や後尾回転翼部分も（３）、（２）と同様の構造である。

・ヘリコプターを構成する立体の色は、使用するライトの効果が分かりやすいように、glMaterialfvで白にしている。

・画面中央部分に、六面体と四面体を組み合わせて建物を構築し、ヘリコプターが建物の周りを旋回するようにしてある。

・y = -6.0 平面に地面[ ground ]を作成した。GL_QUADSを利用することで、縦横の長さが1の正方形のタイルをx軸、z軸に-10 ～ 10の範囲に描画、
　すなわち20×20枚の正方形のタイルを描画することで、地面を形成した。なお、地面の模様として、一枚の正方形を描くごとに色を変えている。

・ライトは3つ用いており、
　・赤色の点光源（GL_LIGHT0）を座標（12.0, 5.0, -6.0）に
　・青色の点光源（GL_LIGHT1）を座標（-12.0, 5.0, -6.0）に、
　・座標(0.0, 25.0, -25.0)から、 (0.0, 0.0, -5.0)方向へのスポットライト（GL_LIGHT2）を設置してある。
　スポットライトは、光源の位置、拡散光、環境光、鏡面光をそれぞれlightPosition, lightDiffuse, lightAmbient, lightSpecularで設定してある。
　また、絞りは100に設定し（GL_SPOT_CUTOFF）、中心からの減衰の度合いを0.1に設定してある（GL_SPOT_EXPONENT）。

・背景の色は水色にしている


□苦労した点
・1つのヘリコプターに対して、たくさんの部品が独立して運動するようにうまくRotatedやTranslatedをさせている点。

・視点の回転を三角関数sin、cosを利用し、角度を上下させるように工夫することによって実現した点。
　また、視点のズームイン/アウト機能は、z軸に対して負/正方向に移動すればよいので、
　ズーム用の変数z_lookatを用意し、z_lookatに0.5を引く/足すことで、機能を実現した点。

・マウスの左ボタン押下するたびに、変数sを1, 0, 1…と交互に変化させるように工夫した点（s = !s;）。
 また、このことにより、一度のクリックで飛行を続けさせ、飛行中にもう一度クリックすることにより一時停止することを実現できた点。

・キーボードの『f』キーを押した場合のみ、「着陸する動き」をさせるために、『f』キーを押したときに変数finish に1を立たせ、
　if文で「finish = 1」の時のみ降下させるようにした点。


□アピールポイント
・様々な立体を、単純な六面体を組み合わせることで作成することができた。

・ヘリコプターの後尾部分の小さいプロペラも実装してあり、実際のヘリコプターの細かい部分も表現している。

・ヘリコプターの回転翼のプロペラはy軸中心の回転、後尾回転翼のプロペラはz軸中心の回転を、機体の移動とは独立に行っており、
　かつ、ヘリコプターの機体全体としては、らせん運動をしつつ、右ボタン押下によりz軸中心の回転を行うという複雑な動きを実現している。

・離陸～建物の周りを飛行～着陸という一連のヘリコプター動きを実現することで、ストーリー性を表現した。

・ライトを3つ使用し、1つはスポットライト、残り二つは点光源とすることで、独特な色合いを表現している。

・360度好きな角度からヘリコプターの飛行を眺めることができる。
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLdouble vertex_table[][3] = {
	{ -1.5, -2.5, 1.5 },
	{ -1.5, -6.0, 1.5 },
	{ 1.5, -6.0, 1.5 },
	{ 1.5, -2.5, 1.5 },

	{ -1.5, -2.5, -1.5 },
	{ -1.5, -6.0, -1.5 },
	{ 1.5, -6.0, -1.5 },
	{ 1.5, -2.5, -1.5 }
};

GLdouble vertex_roof[][3] = {
	{ -4.0 ,0.0, 4.0 },
	{ 4.0, 0.0,  4.0 },
	{ 0.0, 6.0,  1.5 },		
	{ 0.0 , 0.0, -4.0 }
};

GLdouble vertex_body[][3] = {
	{ -0.3, 0.5, 0.5 },
	{ -1.2, -0.5, 0.5 },
	{ 1.5, -0.5, 0.5 },
	{ 1.5, 0.5, 0.5 },

	{ -0.3, 0.5, -0.5 },
	{ -1.2, -0.5, -0.5 },
	{ 1.5, -0.5, -0.5 },
	{ 1.5, 0.5, -0.5 }
};

GLdouble vertex_rotor[][3] = {
	{ 0.0, 0.0, 0.1 },
	{ 3.5, 0.0, 0.1 },
	{ 3.5, 0.05, 0.1 },
	{ 0.0, 0.05, 0.1 },

	{ 0.0, 0.0, -0.1 },
	{ 3.5, 0.0, -0.1 },
	{ 3.5, 0.05, -0.1 },
	{ 0.0, 0.05, -0.1 },
};

GLdouble vertex_tailboom[][3] = {
	{ 4.5, -0.5, 0.0 },
	{ 0.0, 0.0, 0.5 },
	{ 0.0, -1.4, 0.0 },
	{ 0.0, 0.0, -0.5 }
};

GLdouble vertex_tailwing[][3] = {
	{ -0.5, 0.0, 0.02 },
	{ 0.5, 0.0, 0.02 },
	{ 1.0, 0.5, 0.02 },
	{ 0.0, 0.5, 0.02 },

	{ -0.5, 0.0, -0.02 },
	{ 0.5, 0.0, -0.02 },
	{ 1.0, 0.5, -0.02 },
	{ 0.0, 0.5, -0.02 }

};

GLdouble vertex_tailrotor[][3] = {
	{ -0.05, 0.4, 0.01 },
	{ -0.05, 0.0, 0.01 },
	{ 0.05, 0.0, 0.01 },
	{ 0.05, 0.4, 0.01 },

	{ -0.05, 0.4, -0.01 },
	{ -0.05, 0.0, -0.01 },
	{ 0.05, 0.0, -0.01 },
	{ 0.05, 0.4, -0.01 },
};

int face_hexa[][4] = {
	{ 0, 1, 2, 3 },
	{ 4, 5, 1, 0 },
	{ 4, 0, 3, 7 },
	{ 1, 5, 6, 2 },
	{ 3, 2, 6, 7 },
	{ 7, 6, 5, 4 }
};

int face_tetra[][3] = {
	{ 0, 1, 2 },
	{ 3, 0, 2 }, 
	{ 0, 3, 1 },
	{ 1, 3, 2 }
};

GLdouble normal_hexa[][3] = {
	{ 0.0, 0.0, -1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 }
};

GLdouble normal_tetra[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 1.0, 1.0, 1.0 }
};

GLfloat light0pos[] = { 12.0, 5.0, -6.0, 1.0 };
GLfloat light1pos[] = { -12.0, 5.0, -6.0, 1.0 };

GLfloat red[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat green[] = { 0.0, 0.8, 0.0, 1.0 };
GLfloat blue[] = { 0.0, 0.0, 0.8, 1.0 };
GLfloat white[] = { 0.7, 0.7, 0.7, 1.0 };

/* 座標(0.0, 25.0, -25.0)にある光源から、 (0.0, 0.0, -5.0)方向へスポットライトを当てる */
static GLfloat lightPosition[4] = { 0.0, 25.0, -25.0, 1.0 }; //光源の位置
static GLfloat lightDiffuse[3] = { 1.0, 1.0, 1.0 }; //拡散光
static GLfloat lightAmbient[3] = { 0.75, 0.75, 0.75 }; //環境光
static GLfloat lightSpecular[3] = { 1.0, 1.0, 1.0 }; //鏡面光
GLfloat spotDirrection[] = { 0.0, 0.0, -5.0 }; //スポットライトを向ける方向

int s = 0, t = 0, finish = 0;

GLdouble lookat = 12.5, y_lookat = 4.5, z_lookat = 0.0;
double r1 = 0.0, r2 = 0.0, t1 = 5.0;
double t_y = -5.2, r_rotor = 0.0, r_rotor_t = 0.0;

void building_table(void) {
	int i, j;
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glNormal3dv(normal_hexa[i]);
		glColor3d(0.5, 0.0, 0.0);
		for (j = 0; j < 4; j++) {
			glVertex3dv(vertex_table[face_hexa[i][j]]);
		}
	}
	glEnd();
}

void building_roof(void)
{
	int i, j;
	glBegin(GL_TRIANGLES);
	for (j = 0; j < 4; ++j) {			// 各面
		glNormal3dv(normal_tetra[j]);
		glColor3d(0.0, 1.0, 0.0);
		for (i = 0; i < 3; ++i) {		// 各頂点
			glVertex3dv(vertex_roof[face_tetra[j][i]]);
		}
	}
	glEnd();
}

void body(void) {
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glNormal3dv(normal_hexa[i]);
		for (j = 0; j < 4; j++) {
			glVertex3dv(vertex_body[face_hexa[i][j]]);
		}
	}
	glEnd();
}

void rotor(void) {
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glNormal3dv(normal_hexa[i]);
		for (j = 0; j < 4; j++) {
			glVertex3dv(vertex_rotor[face_hexa[i][j]]);
		}
	}
	glEnd();
}

void tailboom(void)
{
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glBegin(GL_TRIANGLES);
	for (j = 0; j < 4; ++j) {			// 各面
		glNormal3dv(normal_tetra[j]);
		for (i = 0; i < 3; ++i) {		// 各頂点
			glVertex3dv(vertex_tailboom[face_tetra[j][i]]);
		}
	}
	glEnd();
}

void tailwing(void) {
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glNormal3dv(normal_hexa[i]);
		for (j = 0; j < 4; j++) {
			glVertex3dv(vertex_tailwing[face_hexa[i][j]]);
		}
	}
	glEnd();
}

void tailrotor(void) {
	int i, j;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glNormal3dv(normal_hexa[i]);
		for (j = 0; j < 4; j++) {
			glVertex3dv(vertex_tailrotor[face_hexa[i][j]]);
		}
	}
	glEnd();
}

void ground(void) {
	double height = -6.0;	// y = -6.0 平面に床を作成する

	static GLfloat ground[][4] = {	/* 床の色 */
		{ 0.6,0.6,0.6,1.0 },
		{ 0.3,0.3,0.3,1.0 }
	};
	
	int i, j;

	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for (j = -10; j < 10; j++) {		// 20×20枚の正方形のタイル（床）を作成
		for (i = -10; i < 10; i++) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);	// (i + j) AND 1 -->> すなわち、床のタイル一枚作る毎に、交互に色を変えている。
			glVertex3d((GLdouble)i, height, (GLdouble)j);				// &演算子は、二進数で比較する。左辺は1より、最下位ビットでの比較なので、
			glVertex3d((GLdouble)i, height, (GLdouble)(j + 1.0));		// 左辺（i+j）が1ずつ違えば、必然的に0と1の交互の比較となる。
			glVertex3d((GLdouble)(i + 1.0), height, (GLdouble)(j + 1.0));
			glVertex3d((GLdouble)(i + 1.0), height, (GLdouble)j);

		}
	}
	glEnd();
}

void idle(void)
{
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(30 * cos(lookat), y_lookat, 30 * sin(lookat) + z_lookat, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	ground();

	building_table();	/*** 中央部の建物 ***/
	glPushMatrix();
	 glTranslated(0.0, -2.9, -1.2);
	 building_roof();
	glPopMatrix();		/*** 中央部の建物 終了 ***/

	glPushMatrix();		/*ヘリコプターの初期設定*/
	 glTranslated(0.0, t_y, 0.0);		// 上昇 or 下降
	 glRotated(r1, 0.0, 1.0, 0.0);		//***** らせん運動（回転）
	 glTranslated(t1, 0.0, 0.0);		//***** らせん運動（平行移動）
	 glRotated(r2, 0.0, 0.0, 1.0);		// 進行方向を軸に自転
	 glRotated(-90, 0.0, 1.0, 0.0);		// 初期位置は右端

	  glPushMatrix();	/*** body（ヘリコプターの機体）***/
	   body();			// body_上部
	   glTranslated(0.0, -0.7, 0.0);
	   glRotated(180.0, 1.0, 0.0, 0.0);
	   glScaled(1.0, 0.4, 1.0);
	   body();			// body 下部
	  glPopMatrix();	/*** body 終了 ***/


	  glPushMatrix();	/*** 回転翼(ロータ)部分 ***/
	   glTranslated(1.0, 0.5, 0.0);
	   glRotated(r_rotor, 0.0, 1.0, 0.0);
	   if (s == 1) {
		   r_rotor += 30.0;
		   if (r_rotor >= 360) r_rotor = 0;   //r = (++r) % 360;
	   }

	   glutSolidSphere(0.2, 100, 100);	//S1 (ロータ接合部分の球)

	   glPushMatrix();	/* 回転翼(プロペラ)部分 */
	    rotor();		// rotor(回転翼)_1
	   glPopMatrix();

	   glPushMatrix();
	    glRotated(90.0, 0.0, 1.0, 0.0);
		rotor();		// rotor(回転翼)_2
	   glPopMatrix();

	   glPushMatrix();
	    glRotated(180.0, 0.0, 1.0, 0.0);
		rotor();		// rotor(回転翼)_3
	   glPopMatrix();

	   glPushMatrix();
	    glRotated(270.0, 0.0, 1.0, 0.0);
		rotor();		// rotor(回転翼)_4
	   glPopMatrix();

	  glPopMatrix();	/*** 回転翼部分(rotor) 終了 ***/


	  glPushMatrix();	/*** tialboom (後尾部分) ***/
	   glTranslated(1.5, 0.5, 0.0);
	   tailboom();
	  glPopMatrix();	/*** tailboom 終了 ***/


	  glPushMatrix();	/*** tailwing(後尾翼部分) ***/
	   glTranslated(5.5, -0.1, 0.0);
	   tailwing();

	   glPushMatrix();	/** テイルロータ接合部分（球） **/
	    glTranslated(0.2, 0.3, 0.1);
	    glRotated(r_rotor_t, 0.0, 0.0, 1.0);
	    if (s == 1) {
		    r_rotor_t += 40.0;
		    if (r_rotor_t >= 360) r_rotor_t = 0;   //r = (++r) % 360;
	    }

		glutSolidSphere(0.12, 100, 100);	//S1 (球)

	    glPushMatrix();	/* 後尾回転翼部分 */
		 tailrotor();		// tailrotor(後尾回転翼)_1
	    glPopMatrix();

	    glPushMatrix();
	     glRotated(90.0, 0.0, 0.0, 1.0);
	     tailrotor();		// tailrotor(後尾回転翼)_2
	    glPopMatrix();

	    glPushMatrix();
	     glRotated(180.0, 0.0, 0.0, 1.0);
	     tailrotor();		// tailrotor(後尾回転翼)_3
	    glPopMatrix();

	    glPushMatrix();
	     glRotated(270.0, 0.0, 0.0, 1.0);
	     tailrotor();		// tailrotor(後尾回転翼)_4
	    glPopMatrix();	/* 後尾回転翼部分終了 */

	   glPopMatrix();	/** ロータ接合部分終了 **/

	  glPopMatrix();	/*** tailwing 終了 ***/
	  

	 glPopMatrix();		/*ヘリコプターの描画終了*/


	if (s == 1) {		// 左クリック
		r1 += 0.3;

		if (r1 == 360)	r1 = 0.0;
		if (t1 <= 9.0)	t1 += 0.02;	// 半径9の円軌道をとるまでらせん運動

		if (finish == 1) {			// 'f'キーを押したとき、y = 5.2平面へ着陸
			if (t_y >= -5.2) t_y -= 0.005;
			else {
				s = 0;
				finish = 0;
			}
		}
		else {						// y = 6.0 平面へ上昇
			if (t_y <= 6.0) t_y += 0.005;
		}
	}

	if (t == 1) {		// 右クリック
		r2 += 0.5;
		if (r2 == 360)	r2 = 0.0;
	}

	glutSwapBuffers();

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			s = !s;
			glutIdleFunc(idle);
		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			t = 1;
			glutIdleFunc(idle);
		}
		else {
			t = 0;
			if (s == 0) glutIdleFunc(0);
		}
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd': lookat -= 0.1; break;		// 視点右回転
	case 'a': lookat += 0.1; break;		// 視点左回転
	case 'w': y_lookat += 0.5; break;	// 視点上昇
	case 'x': y_lookat -= 0.5; break;	// 視点降下
	case 'e': z_lookat -= 0.5; break;	// 視点ズームイン
	case 'c': z_lookat += 0.5; break;	// 視点ズームアウト
	case 'z': lookat = 12.5, y_lookat = 4.5, z_lookat = 0.0; break;	// 視野リセット

	case 'f': finish = 1;	// ヘリコプター着陸コマンド
		break;

	case 'q':				// プログラム終了コマンド
	case 'Q':
	case '\033': exit(0);
	default:
				break;
	}
}

void init(void)
{
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue);

/*** スポットライト ***/
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirrection); //スポットライトの向ける方向（デフォルト (0,0,-1.0)）
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 100.0);// スポットライトの絞り（デフォルト 180.0）
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.1);// スポットライトの中心からの減衰の度合い（デフォルト 0）

}

int main(int argc, char *argv[])
{
	printf("着陸 : 'f'\n終了 : 'q' or 'Q' or 'ESC key'");

	glutInitWindowSize(640, 480);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}
