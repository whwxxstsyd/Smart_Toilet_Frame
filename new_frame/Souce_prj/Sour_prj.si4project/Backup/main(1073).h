//  Function		:   Main Program head file
//  Date			:   2017/10/12
//--------------yjzhou
#ifndef _MAIN_H_
#define _MAIN_H_

#define uint_8	unsigned char
#define uint_16	unsigned int
#define int_8	signed char

#define NOP()	asm("nop")

#define	BJB
#define B1866GW
//#define B1886GW
//位操作
#define LongToBin(n) 	(((n >> 21) & 0x80) | \
						 ((n >> 18) & 0x40) | \
						 ((n >> 15) & 0x20) | \
						 ((n >> 12) & 0x10) | \
						 ((n >>  9) & 0x08) | \
						 ((n >>  6) & 0x04) | \
						 ((n >>  3) & 0x02) | \
						 ((n      ) & 0x01))
#define Bin(n) 			LongToBin(0x##n##l)


#define	XuanZhuan		//------接旋转按钮
#define	ChoiceTM1651
//----------------------------------------
//------------10	MS为基准
#define	Timer100MS		10
#define	Timer200MS		20
#define	Timer300MS		30

//------------1	S为基准
#define	T10S	10
#define	T20S	20
#define	T1Min	60
#define	T2Min	120
#define	T3Min	180
#define	T4Min	240
#define	T5Min	300
#define	T10Min	600
#define T15Min	900  
#define	T30Min	1800

//--------------
#define	DryingDutySzie			100
//#define	LightInduceAdVale		700
//#define	LightInduceAdVale		600
#define	LightInduceAdVale		800

//----------水泵控制
#define		WaterPump_set			PAOUT|=(1<<0)
#define		WaterPump_clr			PAOUT&=(~(1<<0))
//----------进水阀控制
#define		WaterOut				PAOUT|=(1<<1)		
#define		WaterIn					PAOUT&=(~(1<<1))
//----------烘干加热
#define		FanHeat_clr			    PAOUT|=(1<<2)		
#define		FanHeat_set				PAOUT&=(~(1<<2))
//----------座圈加热
#define		SeatHeat_clr			PAOUT|=(1<<3)		
#define		SeatHeat_set			PAOUT&=(~(1<<3))
//----------PUMPA
#define		PUMPA_set				P9OUT|=(1<<4)		
#define		PUMPA_clr				P9OUT&=(~(1<<4))
//----------PUMPB
#define		PUMPB_set				P5OUT|=(1<<5)		
#define		PUMPB_clr				P5OUT&=(~(1<<5))
//----------热风风机
#define		HotFan_set				P5OUT|=(1<<7)		     //新板子
#define		HotFan_clr				P5OUT&=(~(1<<7))
//----------自动冲水
#define		AutoWater_set			P5OUT|=(1<<6)			
#define		AutoWater_clr			P5OUT&=(~(1<<6))
//----------即热模块电源控制
#define		SpeedinessHeatPowerOn	P9OUT&=(~(1<<0))
#define		SpeedinessHeatPowerOff	P9OUT|=(1<<0)
//----------WIFI模块电源控制
#define		WifiPowerOn				P9OUT&=(~(1<<1))
#define		WifiPowerOff			P9OUT|=(1<<1)
//----------按键处理端口定义
#ifdef 		XuanZhuan
#define		KeySdaOut				P6DIR|=(1<<7)		
#define		KeySdaSet				P6OUT|=(1<<7)        
#define		KeySdaClr				(P6OUT&=~(1<<7))
#define		KeySdaIn				P6DIR&=(~(1<<7))
#define		KeySdaPin				(P6IN&0x80)
#define		ReadKeySdaVale			0x80
#define		KeySckSet				P6OUT|=(1<<6)        
#define		KeySckClr				(P6OUT&=~(1<<6))
#endif
//----------除臭风机
#define		ChuChou_set				P7OUT|=(1<<1)     
#define		ChuChou_clr				P7OUT&=(~(1<<1))
//----------冲水板信号控制
#define		WaterWashBoardSet		P7OUT|=(1<<2)
#define		WaterWashBoardClr		P7OUT&=(~(1<<2))
//----------IIC控制
#define		IIC_SDA_set				P7OUT|=(1<<4)		//IIC SDA
#define		IIC_SDA_clr				P7OUT&=(~(1<<4))
#define		IIC_SDA_pin				(P7IN&(1<<4))
#define		IIC_SDA_out				P7DIR|=(1<<4)		
#define		IIC_SDA_in				P7DIR&=(~(1<<4))
#define		IIC_SCL_set				P7OUT|=0x08		//IIC SCL
#define		IIC_SCL_clr				P7OUT&=0xf7		
//----------冲水灯
#define		xiaobianled_set			P7OUT|=(1<<7)
#define		xiaobianled_clr			P7OUT&=(~(1<<7))
//----------------------
#define		SendData_Low			P8OUT&=(~(1<<0))		//---c03
#define		SendData_Hight			P8OUT|=(1<<0) 
#define		InceptDataPin			(P8IN&0x02)			//--co2

//----------蜂鸣器
#define		speaker_set				P0OUT|=(1<<5)
#define		speaker_clr				P0OUT&=(~(1<<5))
//----------回音控制
#define		aftersound_set			P8OUT|=(1<<5)
#define		aftersound_clr			P8OUT&=(~(1<<5))


//------------显示屏命令字
#define 	set_write               0x40					//地址增量模式写数据
#define    	set_address_fix     	0x44	   				//地址固定模式写数据
#define	   	set_read            	0x42					//读按键命令
#define	   	dis_mode            	0x03					//显示模式设置
#define    	set_dis_on          	0b10001111  			//显示控制命令 open
#define    	set_dis_off        		0b10000111  			//显示控制命令 close
#define    	set_address         	0xc0					//设置显示数据地址：00H~0DH


//----------------8310led显示
#define		LedPowerOn				P2OUT|=(1<<2)
#define		LedPowerOff				(P2OUT&=~(1<<2))
#define		LedEconomizeOn			P2OUT|=(1<<0)
#define		LedEconomizeOff			(P2OUT&=~(1<<0))
#define		LedAutoWashOn			P2OUT|=(1<<1) 
#define		LedAutoWashOff			(P2OUT&=~(1<<1))

//----------水位检测
#define		LiquidLevelCheckPin		(P2IN&0x10)
//--------- 红外检测
#define		IRCheck					(P0IN&0x10)
//--------- 过零检测
#define		GuoLing_pin				(P2IN&0x08)
//----------入座检测
#define		ZhaoZuo_pin				(P0IN&0x40)
//----------冲水检测	霍尔检测
#define		ChongShui_pin			(P8IN&0x04)
	
//-------------------------定义按键
#ifdef 	XuanZhuan
#define nokey		0	//---健值
#define key_tunbu	2
#define key_nvxing	1
#define key_power	3 

//#define key_tunbu	0x80
//#define key_nvxing	0x20
//#define key_power	0x08
#define	key_test	4	//k1,k2,s1	power+nvyong
#define	key_zijian	5	//k1,k2,s2
#else
#define	nokey			0x000000	//无按键	
#define	key_shuiwen	0x000001	//k1,s1
#define	key_power		0x000002	//k2,s1
#define	key_zuowen		0x000008	//k1,s2
#define	key_tunbu		0x000010	//k2,s2
#define	key_shiya		0x000100	//k1,s3
#define	key_nvxing		0x000200	//k2,s3
#define	key_reciprocate	0x000800	//k1,s4
#define	key_drying		0x001000	//k2,s4
//#define	key_enfant		0x001000
#define	key_fengwen	0x010000	//k1,s5
#define	key_penkou		0x020000	//k2,s5
#define	key_dengkong	0x080000	//k1,s6
#define	key_jieneng		0x100000	//k2,s6
//#define	key_test	0x000003	//k1,k2,s1
#define	key_test		0x000202	//k1,k2,s1	power+nvyong
#define	key_zijian		0x000018	//k1,k2,s2
#endif

#ifdef 	ChoiceTM1651
//---------------------------IO口
#define	TM1651_Scl_On			P2OUT|=(1<<0) 
#define	TM1651_Scl_Off			(P2OUT&=~(1<<0))

#define	TM1651_Sda_On			P2OUT|=(1<<1)  
#define	TM1651_Sda_Off			(P2OUT&=~(1<<1))
#define TM1651_Sda_in			P2DIR&=(~(1<<1))
#define	TM1651_sda_out			P2DIR|=(1<<1)
#define	TM1651_sda_read		(P2IN&0x02)
#define	TM1651_sda_read_vale   0x02
//-------------------------数据结构
typedef struct{
	uint_8	initialdatabuffer[2];
	uint_8	dis_buf[4];
	uint_8	flag:1;
			}TM1651_uion;
extern TM1651_uion TM1651;
#endif



//----------------------旋转按键板定义
#define 	ReadKey		0x41		//-----读按键
#define 	WriteLed	0x42		//-----写LED
#define		StingBrightness		0x43		//-----设置亮度
#define		StingSpeed			0x44		//-----设置跑马灯速度。



typedef struct{
		uint_16	LedBuf[3];	
		uint_8	Brightness;		//-------分10级
		uint_8	SpeedCount;		//-------分10级		
		uint_8	DispalyMode;	//-----选择那种方式亮LED灯
								//----=0，可以同时点亮每一个灯。
								//----=1，选择渐亮渐灭模式，只能点亮同一色灯
								//----=2,跑马灯
		uint_8	ChoiceRGB;		//-----选择那种颜色
								//----=0红色
								//----=1绿色
								//----=2兰色

		uint_8	BitCount;
		uint_8	BtyeCount;
		uint_8	Index;
		uint_8	Data;
		uint_8	Buffer[7];
				//-------写LED	数据缓存
				//-------Buffer[0]	命令
				//-------Buffer[2]	LED1
				//-------Buffer[3]	LED2
		uint_8	Step;
		uint_8	ReadOrWrite;		//---=0写LED， =1读按键
		uint_8	Delay;
		uint_8	KeyData;
		
		}Rolling_CB;
extern  Rolling_CB Rolling;

extern	uint_8 eeprom[8];

typedef struct{

		uint_8	count_200u;
		uint_8	count_1ms;
		uint_8	count_10ms;
		uint_8	init;					//------上点初始化时间
		uint_8 	t_10ms_f:1;
		uint_8 	t_100ms_f:1;
		uint_8 	t_500ms_f:1;
		uint_8 	t_1s_f:1;
		uint_8  count_flash;
		}timer_uion;
extern  timer_uion timer;

typedef struct{
		uint_8	temperature;		//--------水温
		uint_8	DangWei;			//--------档位
		uint_8	pressure_f;			//--------水压使能
		uint_8	WaterIn_f:1;			//--------进水使能
		uint_8	shuiwei_count;		//--------水位检测计数
		uint_16	jinshuishijian;
		uint_8	TempDeal_time;
		uint_8	AnMoData;
		uint_8	AnMoCount;
		uint_8	JiRe_In_f:1;
		uint_16	delay1;
		uint_16	RX_delay;			//---------即热试接受信号时间超出时间无接受信号报警

		uint_8	InputTemp;
		uint_8	OutputTemp;
		uint_8	OutputTempBack;
		uint_8	OutputTempCount;		

		uint_16	StopHotDelay;
		uint_8	Hot_f:1;
		
		uint_8	WashTimer;			//-----清洗时间
		uint_8	WaterInTime;
		}Water_uion;
extern  Water_uion Water;

typedef struct{
		uint_8	temperature;		//-------座温实际温度	
		uint_8	DangWei;			//------座温档位
		uint_16	count1;				//------着座记时
		uint_16	count2;				//------着座记时
		uint_8	first_f:1;			//------
		uint_8	Heat_f:1;
		uint_16	SeatOnTimer;		//-------落座时间
		uint_8	Flag;				//---BIT0=1 表示着座过， BIT1=1 表示离座过
		
		}Seat_uion;
extern  Seat_uion Seat;


typedef struct{
		uint_16	Vale;				//------羽ｒ请D值	
		uint_8	Lamp_f:1;			//-------灯亮，
		uint_16	Timer;				//-------10分钟控制延时。	
		}LightInduce_CB;
extern  LightInduce_CB LightInduce;


typedef struct{
		uint_8	temperature;
		uint_8	DangWei;
		uint_8	DutyPwm;
		uint_8	DutyCount;
		
		uint_8	step;
		uint_16	time;
		uint_8	enable_f:1;
		//-----烘干冲洗为0烘干时冲水为1表示连续按烘干键不冲水
		uint_8	swash_f:1;	

		uint_8	WorkingTimer;
		uint_8	ADjustTime;	

		uint_8	HotStartTime;

		
		}Drying_uion;
extern  Drying_uion Drying;

typedef struct{
		uint_8	temperature;
		uint_16	time;
		uint_8	Index;

		}Entironment_CB;
extern  Entironment_CB Entironment;



typedef struct{
		uint_8	PGmove_f;
		uint_8	PGmove_dir:1;
		uint_8	PGanmo_dir:1;
		
		}PenGan_uion;
extern  PenGan_uion PenGan;
typedef struct{
		uint_16	value;
		uint_16	Delay;
		uint_8	MotorA_reset;
		uint_8	MotorB_reset;
		}Error_uion;
extern  Error_uion Error;

//-------------------------------
typedef struct{
//		uint_8	DangWei;	//-----水温		
		uint_8	pressure;	//----水压
		uint_8	PGLevel;	//----喷杆位置

		}TunBu_uion;
extern  TunBu_uion TunBu;

typedef struct{
//		uint_8	DangWei;
		uint_8	pressure;
		uint_8	PGLevel;
		
		}NvXing_uion;
extern  NvXing_uion NvXing;

typedef struct{
		uint_8	DangWei;
		uint_8	pressure;
		uint_8	PGLevel;
		uint_8	Dring_f:1;
		}Enfant_uion;
extern  Enfant_uion Enfant;			//----儿童
typedef struct{
		uint_8	DangWei;
		uint_8	pressure;
		uint_8	PGLevel;
				
		}TongBian_uion;
extern  TongBian_uion TongBian;
typedef struct{
		uint_8	step;
		uint_16		delay;
		uint_8	PGLevel;
		uint_16		delay1;
		}chongshui_uion;
extern  chongshui_uion chongshui;

typedef struct{
		uint_8	step;
		uint_16	delay1;
		uint_16	delay2;
		uint_8	enable_f:1;
		}penkou_uion;
extern  penkou_uion penkou;

typedef struct{
		uint_8	step;
		uint_16	delay;
		}fangwu_uion;
extern  fangwu_uion fangwu;

typedef struct{
		uint_8	step;
		uint_16	delay;
		uint_8	enable_f:1;	
		uint_8	SeatOpen_f:1;
		uint_8	CoverOpen_f:1;
		uint_8	SeatDirStatus;		//---座圈翻动方向	
		uint_8	CoverDirStatus;		//---座盖翻动方向
		uint_8	SpaceTime;			//---清状态间隔时间


		
		}CoverSeat_uion;
extern  CoverSeat_uion CoverSeat;

typedef struct{
		long int	vale;
		long int	back;
		uint_8	indx;
		uint_16	count1;		
		uint_8	count2;
		uint_8	flag1:1;
		uint_8	flag2:1;
		uint_8	updata_f:1;				
		}KEY_uion;
extern  KEY_uion KEY;

typedef struct{
		uint_8	ring_times;		
		uint_8	ring_time_set;
		uint_8	stop_time_set;
		uint_8	task_count;
		uint_8	ring_time;
		uint_8	stop_time;				
		}buzzer_uion;
extern  buzzer_uion buzzer;

typedef struct{
		uint_8	enable_f:1;	
		uint_8	LianXu_f:1;	
		uint_8	LianXuBuf;		//----=0取消连续清洗了
								//---bit0=1儿童转烘干
								//---bit1=1男用转烘干
								//---bit2=1女性转烘干		
		uint_8	step;
		uint_8	dring_step;
		uint_16	steptime;
		uint_8	Start_f:1;
		uint_16	time;
					
		}work_uion;
extern  work_uion work;


typedef struct{
		uint_8	Softpower_f:1;
		uint_16	Delay;

		}SoftPowerDeal_CB;
extern  SoftPowerDeal_CB SoftPowerDeal;
typedef struct{
		uint_8 water_gear;
		uint_8 seat_gear;
		uint_8 water_yeild;
		uint_8 wind_gear;
		uint_8 energy_disp:1;
		uint_8 power_disp:1;
}Icon_;

typedef struct{
		uint_8	power_f:1;
		uint_8	PowerEnd_flag;
		uint_8	PowerEnd_f:1;		
		uint_8	seat_f:1;
		uint_8	stop_f:1;
		uint_8	tunbu_f:1;
		uint_8	nvxing_f:1;
		uint_8	enfant_f:1;
		uint_8	QingXiQieHuan_f:1;
		uint_8	QiBeng_f:1;				//----气泵
		uint_8	dring_f:1;
		uint_8	DringTiaoJie_f:1;
		uint_8	penkou_f:1;
		uint_8	ShuiWenSet_f:1;
		uint_8	ZuoWenSet_f:1;
		uint_8	ShuiYaAnMo_f:1;
		uint_16	ShuiYaAnMo_timer;

		uint_8 	Auto_clear;
		uint_8	TunBuShuiYaTiaoJie_f:1;	
		uint_8	NvXingShuiYaTiaoJie_f:1;	
		uint_8	EnfantShuiYaTiaoJie_f:1;
		
		uint_8  Mode_select;			//妯″紡閫夋嫨鏍囧織浣?
		uint_8  Pres_select;			//妯″紡姘村帇閫夋嫨鏍囧織浣?
		uint_8  Work_index;
		uint_8  Comsum_set;
		uint_8  PG_gear;				//鍠锋潌浣嶇疆寰皟
		uint_8  Water_gear;				//s姘村帇寰皟
		uint_8	ZuoYu_f:1;			//-----座浴		
		uint_8	jieneng_f:1;			//------节能标志
		uint_8	jieneng_e:1;			//------节能使能标志
		uint_8	auto_f:1;
		uint_8	reciprocate_f:1;
		uint_8	dring_wf_f:1;
		uint_8	chongshuiban_f:1;
		uint_8	chongshui_f:1;
		uint_8	chongshui_e:1;		//----自动冲水使能		
		uint_8	cover_f:1;
		uint_8	zuoquan_f:1;
		uint_8	LengReAnMo_f:1;
		uint_8	dengkong_f:1;
		uint_8	ganying_f:1;
		uint_8	PG_zero_f:1;
		uint_8	Dry_zero_f:1;
		uint_8	chuchou_e:1;
		uint_8	chuchou_f:1;
		uint_8	fangwu_f:1;

		uint_8	test_f:1;
		uint_8	PcbTest_f:1;
		NvXing_uion Woem;      //  2019-7-19 鎶婄浉搴旂殑妯″紡缁撴瀯浣撴斁鍏ヨ繖閲岋紝缁熶竴鐢ㄨ繖涓粨鏋勪綋璁块棶
		TunBu_uion  Hip;
		Icon_   Icon;
		//Posotion_ pst;   //浣嶇疆缁撴瀯浣?
		} Status_uion;
extern  Status_uion Status;


typedef struct{
		uint_8	step;
		uint_16	time_h;
		uint_16	time_l;
		uint_8	start_f:1;
		uint_8	first_f:1;
		uint_8	already_f:1;
		uint_8	OK_f:1;
		uint_8	Bit_Count;
		uint_8	Byte_Count;
		uint_8	Recv_Data_Buf;
		uint_8	TFDelay;
		
		}IR_uion;
extern  IR_uion IR;


typedef struct{
		uint_8 ack_flag:1;
		}iic_uion;
extern  iic_uion iic;

//------------------液体箱处理


#define  LiquidCount	10
typedef struct{

		uint_8	Enable_f:1;		
		//------停止/使能标志
		uint_8	Auto_f:1;


		uint_8	Flag;
		uint_8	Start_f:1;		
		//-----=0初始化处理，=1正常加液处理
		uint_8	Frist_f:1;		
		//-----=1第一次初始化 =0已初始化过。
		
		uint_8	Step;
		uint_16	Delay;
		//------------	
		uint_8	Level_f;			
		//------液体箱液位检测
		uint_8	LevelCount;		
		//------液位检测次数
		uint_8	LevelFlash_f:1;	
		//------闪烁处理
		uint_8	ADDLiquidCount;		
		//------检测到无液提示后还可以清洗次数
		//--------
		uint_8	PenGanLeve;	
		//------喷杆档位	
		uint_8	TimeCount;		
		//------间隔计时
		uint_16		Time1SCount;	
		//------间隔计时
		//---------
		uint_8	WaterWash_f:1;	
		//------冲过水标志	
		uint_8	SetOff1Min;		
		//------1分钟计时
		uint_8	PumbEable_f:1;	
		//------气泵启动标志
		uint_16	PumbDuty;		
		//------气泵占空比
		uint_8	Stop_f:1;
			
		}LiquidDeal_CB;
extern  LiquidDeal_CB LiquidDeal;

typedef struct{
		uint_8	step;
		uint_16	time_h;
		uint_16	time_l;
		uint_8	start_f:1;
		uint_8	first_f:1;
		uint_8	already_f:1;
		uint_8	OK_f:1;
		uint_8	Bit_Count;
		uint_8	Byte_Count;
		uint_8	Recv_Data_Buf;
		uint_8	JpioTest;
		}FGIR_CB;
extern  FGIR_CB FGIR;

typedef struct{
		uint_8	Step;
		uint_8	Enable;
		uint_8	Start_f:1;
		uint_8	Count;
		uint_8	Bit_Count;
		uint_8	Byte_Count;
		uint_8	Data_Buf;
		uint_8	TF;	
		uint_8	Ok_f:1;			//----发送完数据
		
		
		}SendData_CB;
extern  SendData_CB SendData;



typedef struct{
		uint_8 	TxLong;
		uint_8	TxIndex;
		}Uart0Deal_CB;
extern  Uart0Deal_CB Uart0Deal;




//-------------------PCB出厂测试
typedef struct{
		uint_8 	step;
		uint_8	MotorCount;
		uint_8	LoadCount;

		
		uint_16 delay;
		uint_16 delay2;
		}PcbZiJian_uion;
extern  PcbZiJian_uion PcbZiJian;
//-----------------老化测试
typedef struct{
		uint_8 step;
		uint_16 delay;

		uint_8	LedLoop;
		uint_8	LedFlashTime;	
		uint_8	Count;		//---老化次数

		uint_16	Zyj1;
		uint_16	Zyj2;
		
		}test_uion;
extern  test_uion test;
//----------------整机出厂测试
typedef struct{
		uint_8 	Flag;
		uint_8 	Step;
		uint_16 	Delay;
		uint_8	CheckWifiSignal_f:1;

		}MachineTest_CB;
extern  MachineTest_CB MachineTest;

#define	uart0_size	8				//----------UART0数据长度		

extern uint_8	uart_flag_f;					//---------bit0=1	uart0接收完成
extern uint_8	rx0_buf[uart0_size];			//----------UART0接收缓存器

void  delay_us(uint_16 n);
void  buz_set(uint_8 loop,uint_8 delay_H,uint_8 delay_L);
void  MachineStatusUpdataRollingPcb(void);
void  Uart0_init(void);

#endif

