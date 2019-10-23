#include "Function_deal.h"

//    ���ܺ���
//**********************/

void Close_all_function(void)
{
	Status.Icon.power_disp = 0;  //�رյ�Դͼ��
	Status.Icon.energy_disp = 0;	//�رս���
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	work.step = 0;
	Status.reciprocate_f = 0;
}

void TunBuWashEnable(void)
{
	if(Status.Mode_select == 0)  //����ǵ�һ��ѡ����ϴ����
	{
		Status.Mode_select = 1;   //1Ϊ��ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 1)) //������ǵ�һ�ν���������������ڽ�������Ĺ���
	{
		Status.Mode_select = 1;    //������ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
		Status.QingXiQieHuan_f = 1;  //��ϴ�л�
	}
	work.enable_f = 1;    		//ʹ�ܹ���
	work.step = 0;   			//������0
	if(Status.dring_f == 1)   //���ʹ���˺��
	{
		Status.dring_f = 0;   //�رպ��
		Drying.step = 0;
	}	
	Status.LengReAnMo_f = 0;
	Status.ShuiYaAnMo_f = 0;
	Status.reciprocate_f = 0;
	Status.fangwu_f = 0;
	Drying.swash_f = 0;
	Water.WashTimer = T1Min;
}


void NvXingWashEnable(void)
{
	if(Status.Mode_select == 0)  //����ǵ�һ��ѡ��ϴ����
	{
		Status.Mode_select = 2;   //2Ϊ��ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 2)) //������ǵ�һ�ν���������������ڽ�������Ĺ���
	{
		Status.Mode_select = 2;    //���븾ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
		Status.QingXiQieHuan_f = 1;  //��ϴ�л�
	}
	work.enable_f = 1;    		//ʹ�ܹ���
	work.step = 0;   			//������0
	if(Status.dring_f == 1)   //���ʹ���˺��
	{
		Status.dring_f = 0;   //�رպ��
		Drying.step = 0;
	}	
	Status.LengReAnMo_f = 0;
	Status.ShuiYaAnMo_f = 0;
	Status.reciprocate_f = 0;
	Status.fangwu_f = 0;
	Drying.swash_f = 0;
	Water.WashTimer = T1Min;
}


void ChuChouDeal(void)
{	
	if(Status.test_f==0)
	{
		if(Status.power_f == 1)
		{
			if(Status.chuchou_e&&Status.chuchou_f&&(Status.dring_f==0)&&(Status.PowerEnd_f==1))
			{
				ChuChou_set;
			}
			else
			{
				ChuChou_clr;
			}
		}
		else
		{
			ChuChou_clr;
		}	
	}
}


//---------------------------��ˮ���ˮ����
void ChongShuiBanDeal	(void)
{
	if(Status.chongshuiban_f)	
	{		
		WaterWashBoardSet;
		chongshui.delay1++;
		if(chongshui.delay1 > 200)		//----200*10ms=2000ms
		{
			chongshui.delay1 = 0;
			Status.chongshuiban_f = 0;
		}
	}
	else
	{
		WaterWashBoardClr;
	}
}

//***************************************/
//	void Wash_deal(uint_8 select)
//	
//	��˵��ڲ���
//
//***************************************/
void Wash_deal(uint_8 select)
{

	if(PenGan.PGmove_f == 0 && Status.Mode_select != 0 && Status.reciprocate_f == 0)
	{
		PenGan.PGmove_f = 1;	//��˵���ʹ��
		Status.PG_gear = Status.Pres_select;  //�Ȱѹ���ѡ��λ��ֵ����λ���ٶԵ�λ���в���	
		
		if((select & 0x20) == 0x20)  //λ�õ��� +
		{
			Status.PG_gear++;		//���λ��+
		}
		if((select & 0x10) == 0x10)  //λ�õ��� -
		{
			Status.PG_gear--;		//���λ��-
		}
	}
	
}

//***************************************/
//void Water_change(uint_8 select)
//	
//	ˮѹ���ڲ���
//
//***************************************/
void Water_change(uint_8 select)  
{
	if(Water.pressure_f == 0 && Status.Mode_select != 0)	
	{
		Water.pressure_f = 1;
		Status.Water_gear = select;		//ֱ�Ӱ�ˮѹֵ��ֵ��ִ�б���
	}
}


//***************************************/
//void Gear_deal(uint_8 select)
//	��λ����ѡ����
//
//***************************************/
uint_8 Gear_deal(uint_8 select)
{
	uint_8 temp = 0;
	temp = select & 0x0f;
}


//********************************************/
//
//�������~
//
//******************************************/
void Zuo_Check(void)
{
	if(ZhaoZuo_pin == 0)  //��⵽����
	{
		Seat.count1++;
		Seat.count2 = 0;
		if(Seat.count1 > 10)
		{
			//------------100MS������Ч
			Entironment.time = T30Min;
			CoverSeat.delay = T5Min;
			CoverSeat.enable_f = 1;
			Status.chuchou_f = 1;		//-----��������ʹ��
			Status.jieneng_e = 0;		//�رս���
			Seat.Flag |= 0x01;
			if(Status.seat_f == 0)
			{
				Status.seat_f = 1;
				Status.power_f = 1;		//������־λ��1
				//SpeedinessHeatPowerOn;
				//WifiPowerOn;
				//CO2_clr_seat;
				Status.fangwu_f = 1;	//���۱�־λ��1
				fangwu.step = 0;		
				penkou.step = 0;		//��ڲ����� 0
				//penkou.enable_f=0;
				Status.penkou_f = 0;		
				buz_set(1,30,30);	
			}
			if(Seat.count1 > 1000)		//---------����10S�Զ���ˮ����
			{
				Seat.count1 = 1000;	
				if(Seat.first_f == 0)
				{
					Seat.first_f = 1;
					if(Status.auto_f == 1)
					{
						Status.chongshui_e = 1; 
					}
				}				
			}		
		}
	}
	else
	{
		//------------����2S��Ч
		Seat.count2++;
		Seat.SeatOnTimer = T2Min;
		
		if(Seat.count2 > 200)		//--400*10=4000MS
		{
			Seat.count1 = 0;
			Drying.swash_f = 0;
			Status.chuchou_e = 1;
			Seat.Flag |= 0x02;
			if(Status.seat_f)			//-----
			{
				Status.seat_f = 0;	
				LiquidDeal.WaterWash_f = 0;
				LiquidDeal.SetOff1Min = T1Min;
				//CO2_set_seat;
				Seat.first_f = 0;
				Status.stop_f = 1;
				Status.tunbu_f = 0;
				Status.nvxing_f = 0;
				Status.enfant_f = 0;
				work.LianXu_f = 0;
				work.LianXuBuf = 0;
				Enfant.Dring_f = 0;	
				work.step = 0;
				if(Status.dring_f)
				{
					Status.dring_f = 0;	
					Drying.step = 0;
				}
				Status.ShuiYaAnMo_f = 0;
				Status.reciprocate_f = 0;
				Status.dring_wf_f = 0;
				Status.ZuoYu_f = 0;
				Status.LengReAnMo_f = 0;
				if(penkou.enable_f)
				{
					penkou.step=0;
					Status.penkou_f = 0;
				}					
			}
		}
		//----------����6S�Զ���ˮ
		if(Seat.count2 > 600)		
		{
			if(MachineTest.Flag == 0)
			{
				if(Status.auto_f)
				{
					if(Status.chongshui_e)
					{
						Status.chongshui_e = 0;
						Status.chongshui_f = 1;
						Status.chongshuiban_f = 1;
					}
				}
			}
		}
		//---����1�ӹس���
		if(Seat.count2 > 6000)		
		{
			Status.chuchou_f = 0;	
		}

		//----------����10���ӽ������ģʽ
		if(Seat.count2 > 60000)			//----10*60*1000/10		
		{
			if(Status.jieneng_f)
			{
				Status.jieneng_e = 1;
			}
			Seat.count2 = 60000;
		}
	}
}







