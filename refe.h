#ifndef _REFEH_
#define _REFEH_
using namespace std;
//Banding�ϰ���
static const int OB_BANDING = 88;
static const int BANDING_HEIGHT = 80;
static const int BANDING_INTERVAL = 40;
static const string PIC_BANDING = "HelloWorld.png";
//Wall�ϰ���
static const int OB_WALL  = 99;
static const string PIC_WALL = "bga.png";
static const int MAX_WALL_HEIGHT = 100;
static const int MIN_WALL_HEIGHT = 50;
static const int WALL_WIDTH = 30;
static const int MIN_WALL_INTERVAL = 300;
static const int MAX_WALL_INTERVAL = 700;

//Missile�ϰ���
static const int OB_MISSILE = 111;
static const string PIC_MISSILE = "DQIV.png";
static const int MAX_MISSILE_OFFSET = 40;
//һ���ϰ���
static const int MI_FIREBALL = 5;
static const int MAX_INTERVAL = 70;		//�ϰ��������
static const int INIT_POSITION = 0;    //�ϰ�����ʼˢ��λ��

static const int groundHeight=30;//����߶�
static const int TAG_HERO = 99;

static const int HERO_BUFF_NORMAL = 10;
static const int HERO_BUFF_INVINCIBLE = 20;
static const int HERO_BUFF_SPEEDUP = 30;

static const int HERO_STATUS_NOMAL = 100;
static const int HERO_STATUS_JUMP = 200;
static const int HERO_STATUS_INJURED = 300;

//groundˢ�����
static const string PIC_GROND = "";
static const int TAG_GROUND = 1000;
static const int GROUND_MIN_INTERVAL = 600;           //�����С���
static const int GROUND_MAX_INTERVAL = 1600;
static const int GROUND_MIN_LENGTH = 1500;			//�����С����
static const int GROUND_MAX_LENGTH = 3000;

//Map ˢ��
static const int TAG_MAP = 123;
static const string PIC_AMAP = "bga.png";
static const string PIC_BMAP ="bgb.png";

#endif 