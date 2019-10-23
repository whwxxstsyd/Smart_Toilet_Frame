#include "Moto_deal.h"


Motor_uion MotorA;
Motor_uion MotorB;
Motor_uion *motor_select[2];

PenGan_uion PenGan;
penkou_uion penkou;

#define arrySize(x)  (sizeof(x) / sizeof(x[0]))

#define	WangFu_18mm		160
#define	WangFu_2mm		20     //��������������ľ���
#define	Reciprocate_speed	100  //����������˶����ٶ�


	
//----------------��˵�� P5.4.3.2.1 ABCD
uint_8 StepMotor_B[8] = {0x10,0x18,0x08,0x0c,0x04,0x06,0x02,0x12};

//----------------��ɵ���ӿ� p6.5,4,3,2
uint_8 StepMotor_C[8] = {0x20,0x30,0x10,0x18,0x08,0x0c,0x04,0x24};

//-------ˮ·������   P8.7.6.4.3 ABCD
uint_8 StepMotor_A[8] = {0x80,0xc0,0x40,0x50,0x10,0x18,0x08,0x88};


const uint_16 PengGang[2][6]={
//{1170,1296,1422,1548,1674,1800},							//�β���ϴ���λ�� 0��λ 1,2,3,4,5��
{1200,1494,1557,1622,1686,1750},
{1200,1494,1557,1622,1686,1750},						 	//Ů����ϴ���λ�� 0��λ 1,2,3,4,5��
};


//ˮѹ�趨��Χ
const uint_16 WaterPressure[2][6]={
{2000,2050,2050,2100,2280,2360},					//�β���ϴ���λ�� 0��λ 1,2,3,4,5��
{800,750,750,600,410,0},						 	//Ů����ϴ���λ�� 0��λ 1,2,3,4,5��
};


//------------------------ˮ·������
#define 	CskMin			0
#define		CskZJ			4
#define		CskAddLiquid	9
#define 	CskMax			10

const uint_16 CSK_table[]=
{
	0,		//-------0	��Сλ��
	225,	//-------1	Ů��3
	450,	//-------2	Ů��2
	765,	//-------3	Ů��1
	1339,	//-------4	�Խ��
	2025,	//-------5	����1
	2340,	//-------6	����2
	2565,	//-------7	����3
	2790,	//-------8	����MAX
	3364,	//-------9	��Һ��
	3544,	//-------10	����г�
};


#define 	SSMin		0
#define 	SSRestIndex	1
#define 	SSMax		2

const uint_16 SS_table[]=
{
	100,				// 0
	150,				//100,				// ��ת
	1900,				//3332,			// 2					//--��λ	
};




//----------------------------
//--�˿����ýṹ���ʼ��
//--Motor_sum �������
//----------------------------
Port_set p_set[Motor_sum]  =  {	
	{
	    StepMotor_A_IO,  		//��ʼ����IO��	��ˮ���
		StepMotorAStop,			//��ʼ�����0
		StepMotor_A,			//��ʼ���������λ
		CSK_table,				//��Ӧ�����λ��ѡ��
	},
	{
	    StepMotor_B_IO, 		//��ʼ����IO��	��˵��			
		StepMotorBStop,
		StepMotor_B,
		SS_table,
	}
};


//--------------�����������ָ�뺯��ԭ��------------
//
//-���룺 ����������ƽṹ�� Motor_uion���������ѡ�� motor
//
//-����� ��
//---------------------------------------------------
void Motor_Control(Motor_uion *p,uint_8 motor)
{
	
	if(p->enable_f == 1)						//������б�־
	{
		if(p->Index != p->SumCountSet)			 //�����������ĵ�ǰλ�ò�����Ŀ���趨��λ��
		{			
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;					//���IO�ڳ�ʼ��0
			GPIO_OUT(p->pInit->port) |=  p->pInit->phase[p->XiangWei];		//�ٰѵ������λ��ֵ��IO��			
			if(p->cw_f  ==  1)			//�����ת��־λ��1						
			{
				if(p->XiangWei < 7)			//���������λ++				
				p->XiangWei++;
				else						//������λ��Χ�����¸�ֵ
				p->XiangWei = 0;
				p->Index++;
			}
			else						//���������ת
			{
				if(p->XiangWei > 0)			//��λ�Լ�
				{
					p->XiangWei--;
				}
				else						//������¸�ֵ
				{
					p->XiangWei = 7;
				}
				if(p->Index > 0)
				{
					p->Index--;
				}
			}
		}
		else								//���������λ
		{
			p->enable_f = 0;				//���ʧ��
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;   //���IO���ֹͣ
			p->end_f  =  1;				//��λ
		}
	}
	else
	{
		if(Status.PcbTest_f == 0)	//���PCB�Լ���ɺ�
		{
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;	//IO���0								
			p->XiangWei  =  0; //��λ��0
		}
	}
}


/********************************/
//	����ѡ������Ż�ȡ����������ֵ
// 0 ��ˮ���   1 ��˵��
/********************************/
uint_16 Slt_Table(uint_8 num)
{
	uint_16 temp;
	if(num == 0)
	{
		temp = arrySize(CSK_table) - 1;
	}
	else
	{
		temp = arrySize(SS_table) - 1; 
	}
	return temp;
}

/********************************************/
//		��������ϵ縴λ
//Motor_uion:���벽������ṹ�� 
//count����������ĸ���������Ŀֻ�з�ˮ�������˵��
//**t:  ȡ��ַ�ĵ�ַ->*(Motor[0])->Motor[0] = MortorB => *MortorB  got it!
//��ˮ�����λ�Ĳ������ȸ�λ����ת���Խ��
//��˵����λ����ֱ��������ʼ��
/*********************************************/
void Power_up_reset(Motor_uion **t)
{
	//ѭ������ʼ�����	
	uint_8 i = 0;
	Motor_uion *p = *t;	  //���ﶨ��һ���ɱ����ṹ�壬������Ŵ������ĵ���ṹ��
	//�������10ms��ִ��
	if(Status.PowerEnd_f == 0)   //�ϵ��־λ
	{
		if(timer.t_1s_f == 1)    //10���ʱ
		{
			timer.init++;	
			timer.t_1s_f = 0;
		}		
		if(timer.init > 10)
		{
			timer.init = 10;   
		}	
		for (i = 0; i < 2; i++)
		{		
			switch(p->State)
			{
				case 0:							
				p->pInit = &p_set[i];		//��ʼ������ӿڽṹ��Ķ˿ڡ���λ��														
				p->cw_f = 0;							//ͳһ��ת  ������Ӳ�����䲻ͬ����Щ����Ǹ�λ�Ƿ�ת  ������Ҫע�⣩
				p->Index = p->pInit->position[Slt_Table(i)]; 	//��ǰλ������Ϊ���
				p->SumCountSet = p->pInit->position[0];		//Ŀ��λ��������С ʵ��������λ��
				p->State++;
				p->end_f = 0;			
				p->enable_f = 1;		//ʹ�ܱ�־λ��1													
				break;	
				case 1:
				if(p->end_f == 1 )	//ת��Ŀ��λ��֮��														
				{
					if(i == 0)	//�Է�ˮ�����������
					{
						p->enable_f = 0;
						p->end_f = 0;										
						p->DelayTime = 0;
						p->State++;				
					}
					else		//��˵����ɸ�λ
					{
						p->end_f = 0;										
						p->enable_f = 0;
						p->Compelet_flag = 0x01;
						p->select = 1;             //�������ѡ��1Ϊ��˵��
					}
				}
				break;
				case 2:	//�������÷�ˮ���ֹͣ����100ms
					p->DelayTime++;
					if(p->DelayTime >= 10)
					{
						p->DelayTime = 0;
						p->State++;	
					}
				break;
				case 3:
					//���������Ҫת����λ��				
					p->cw_f = 1;							//��ת				
					p->SumCountSet = p->pInit->position[CskZJ]; 	//Ŀ��λ������Ϊ�Խ��
					p->enable_f = 1;					//ʹ�ܣ���ʼת��
					p->State++;	
				break;
				case 4:
					if(p->end_f == 1)	//ת��Ŀ��λ��֮��														
					{	
						p->end_f = 0;	
						p->enable_f = 0;
						p->Compelet_flag = 0x10;
						p->select = 0;    //�������ѡ��λ0 Ϊ��ˮ���
					}
				break;
			}
			p++;   //����ṹ��+1  //����ѭ����ɺ� P�ǵ���2��
		}		
		if(((p-1)->Compelet_flag || (p-2)->Compelet_flag == 0x11) && (timer.init==10))   //���������λ����Լ�����10��
		{
			Status.PowerEnd_f = 1;				//�ϵ縴λ��ɱ�־λ��1
			(p-1)->Compelet_flag = 0;			//�������ɱ�־λ��1
			(p-2)->Compelet_flag = 0;
			Status.PG_zero_f=1;		
			Status.Dry_zero_f=1;		
			buz_set(1,30,30);				//��һ��
		}
	}
}


/*****************************************/
//   ѡ��λ��ˮѹ
//���� :   motor ��0 ��ˮ��� 1 ��˵�� 
// s1�� s2  �� ��Ӧ�ı��������ݵ�����
//���λ��ֵ
//*****************************************/
uint_16 Slet_position(uint_8 motor, uint_8 s1, uint_8 s2, uint_8 s3)
{
	uint_16 temp;
	if(motor == 0)
	{
		if(s3 == 1)
		{
			s3 = 0;
			temp = CSK_table[CskZJ];    //����ֱ�Ӹ�ֵ�Խ�ڵ�λ��
		}
		else
		{
		temp = WaterPressure[s1][s2];   //����ǵ���ˮѹ
		}
	}
	else
	{
		temp = PengGang[s1][s2];		//����ǵ������λ��
	}
}

/*****************************************************************/
//��������趨λ�þ��룬���ݹ��ܲ�ͬ���趨
//Motor_uion *t ��������ṹ�壬Status_uion ״̬�趨�ṹ��
//
/*******************************************************************/
void Motor_set_position(Motor_uion *t, Status_uion *p)
{
	//Ŀ���趨λ�õĻ�ȡ��Slet_position���
	t->SumCountSet = Slet_position(t->select, p->Mode_select, p->Pres_select, p->Auto_clear);

	if(t->select == 0)    //���ǶԷ�ˮ�����λ�ÿ��� 
	{
		if(t->Index == t->SumCountSet)
		{
			t->enable_f = 0;
			t->end_f = 1;
		}
		else
		{
			t->enable_f = 1;
			t->end_f = 0;
			if(t->Index > t->SumCountSet)
				t->cw_f = 0;
			else
				t->cw_f = 1;
		}
	}
	else			//��˵�����ٶȿ���
	{
		if(t->Index == t->SumCountSet)
		{
			t->enable_f = 0;
			t->end_f = 1;
		}
		else
		{
			t->enable_f = 1;
			t->end_f = 0;
			if(t->Index > t->SumCountSet)
			{
				if(t->cw_f == 1)
				{
					t->Index += PenGanFanXianBuShang;
				}
				else
				{
					t->cw_f = 0;
				}
			}
			else
			{
				if(t->cw_f==0)
				{
					t->Index -= PenGanFanXianBuShang;
				}
				else
				{
					t->cw_f = 1;
				}			
			}
		}
	}
}


/*****************************************************************/
//    �����˶�����ģ��
//˵���� ��˵���������˶����ͷ�ˮ�����ˮѹ��Ħ����������Ľṹ��ѡ��
//���ܣ�ѭ����ģʽװ�����ṹ�壬��ִ��
//�˹��ܶ�Ӧ ��ϴ��Ů��
//��ˮ����� ǰһ��״̬Ӧ��0��ˮѹ
/*******************************************************************/
void Reciprocate_fun(Motor_uion *t, Status_uion *p)
{	
	uint_16 Now_temp = 0;     //����һ����ǰ���趨��Ŀ��λ��
	uint_16 Dis_temp = 0;		//����һ����Ҫ�����Ŀ��λ��

	Now_temp = Slet_position(t->select, p->Mode_select, p->Pres_select, p->Auto_clear);		//��ֵ��ǰ״̬��Ŀ��λ��
	Dis_temp = Slet_position(t->select, p->Mode_select, (p->Pres_select+4), p->Auto_clear);	//�趨�����˶���Ŀ��λ��

	/************************************************/
	//�����ǶԽ��������˶�ǰ��λ���ж�

	//������ǰλ��С��ǰ״̬��Ŀ��λ��
	if(((t->Index <= Now_temp - WangFu_2mm) && (t->select == 1)) ||		//������˵��ѡ��
		((t->Index <= Now_temp ) && (t->select == 0)))					//���Ƿ�ˮ���ѡ��
	{
		t->SumCountSet = Dis_temp;   //λ�ø�ֵ�����Ŀ��λ�ñ���
		if((t->cw_f == 0) && (t->select == 1))
		{
			t->Index -= Reciprocate_speed;	//��˵����ֵ��������
		}		
		t->cw_f = 1;			//��ת
		t->enable_f = 1;		//��ʼ����
		t->end_f = 0;
	
	}
	//������ǰλ�ô���ǰ״̬��Ŀ��λ��
	if(((t->Index >= Dis_temp) && (t->select == 1)) ||
		((t->Index >= Dis_temp) && (t->select == 0)))
	{
		if((t->cw_f == 1) && (t->select == 1))		//����˵�����в���
		{
			t->SumCountSet = Now_temp - WangFu_2mm;
			t->Index += Reciprocate_speed;
		}
		else				//�Է�ˮ������в���
		{
			t->SumCountSet = Now_temp;
		}
		t->cw_f = 0;
		t->enable_f = 1;
		t->end_f = 0;

	}
	//������ǰλ�õ���ǰ״̬��Ŀ��λ��
	if(t->Index == t->SumCountSet)
	{
		t->SumCountSet = Dis_temp;
		if((t->cw_f == 1) && (t->select == 1))
		{
			t->Index += Reciprocate_speed;
		}	
		t->cw_f = 0;
		t->enable_f = 1;
		t->end_f = 0;
	}
}

/****************************************************************/
//		�����ϴ����ģ��
//���룺����ṹ�壬�͹��ܱ�־λ�ṹ��
//
/***************************************************************/
void Motor_work_prosess(Motor_uion **t, Status_uion *s)
{
	Motor_uion *p = *t;	  //���ﶨ��һ���ɱ����ṹ�壬������Ŵ������ĵ���ṹ��
	//��Ĭ�� p ���� ��ˮ���   p+1���� ��˵��
	//work step
	switch(work.step)
	{
		case 0:
			work.steptime = 0;  //��������ʱ���ʱ 
			if ((p+1)->enable_f == 0)
			{
				s->QiBeng_f = 0;
				if (s->QingXiQieHuan_f == 1)
				{
					work.step = 5;		//�������ϴ�л�  ��������һ��
				}
				else
				{
					work.step++;
				}
			}
			break;
		case 1:
			Motor_set_position(p,s);    //�����Ƿ�ˮ������÷�ˮ��λ��
			//Water.WaterIn_f = 1;   	//�Ƿ�����ת��λ�ٽ�ˮ�����Ǳ�ת�߽�ˮ��
			//Water.Hot_f = 1;
			work.step++;
			break;
		case 2:
			//�ȴ���ת��λ
			if(p->end_f == 1)
			{
				p->end_f = 0;
				p->enable_f = 0;
				work.step++;
			}
			break;
		case 3:
			//-----���ý�ˮ
			Water.WaterIn_f = 1;   	
			Water.Hot_f = 1;
			work.steptime = 0;
			work.step++;
			break;
		case 4://�Խ�2��
			if(++work.steptime > 150)
			{
				work.steptime = 0;
				work.step ++;
			}
			break;
		case 5:  //�������л�����ʱ���л����Խ��
			s->Auto_clear = 1;
			Motor_set_position(p,s);
			work.step++;
			break;
		case 6:
			//�ȴ���ˮ����ת��λ
			if(p->end_f == 1)
			{
				p->end_f = 0;
				p->enable_f = 0;
				Water.WaterIn_f=1;
				Water.Hot_f=1;
				work.step++;
			}
			break;
		case 7:
			if(s->QingXiQieHuan_f == 1)  //������л���ϴ������
			{
				work.step++;     //ֱ��������һ��
			}
			else
			{
				if(++work.steptime >= 10)    //-------0.1S
				{
					work.steptime = 0;
					work.step ++;
				}
			}
			break;
			/************�����Ƿ�ˮ�ڳ�ʼ��********************/
		case 8:
			Motor_set_position((p+1),s);   //����ڵ����ʼ��
			work.step++;
		break;
		case 9:
			//-----------------------------�ȴ������˵�λ			
			if((p+1)->end_f == 1)
			{
				(p+1)->end_f = 0;
				(p+1)->enable_f = 0;
				work.step++;
			}
			break;
		case 10: //����Ҫת�����λ������ϴ2�����ת����Ӧ��λ����ֹ��λ��С������ģ��ֹͣ����
			Motor_set_position(p,s);    //�����Ƿ�ˮ������÷�ˮ��λ��
			Water.WaterIn_f = 1;
			Water.Hot_f = 1;
			work.step++;
			break;
		case 11:
			//work.time++;
			if(p->end_f==1)
			{
				work.steptime = 0;
				p->end_f = 0;
				p->enable_f = 0;
				work.Start_f = 1;
				work.time = Water.WashTimer;
				work.step++;
			}
			break;
			
	}
	
	


}




/************************
  �������������������	
***********************/
void	Motor_A_B_C_program(void)
{
//	if(work.enable_f&Status.Dry_zero_f)
/*	if(work.enable_f)	
	{
		if(LiquidDeal.Enable_f == 0)		
		{
			if(Status.tunbu_f||Status.nvxing_f||Status.enfant_f)
			{
			//-------------------���ܴ���
				if (Status.auto_f && (Status.test_f == 0))
				{
					Status.chongshui_e = 1;
				}	
				Status.PG_zero_f = 0;
				DealCSKandSS();
			}
			else
			{
				DealCSKandSS_end();
			}
		}
	}
	else
	{
		if((Status.tunbu_f == 0)&&(Status.nvxing_f == 0)&&(Status.dring_f == 0))
		Status.stop_f = 0;
	}	*/
}






void DringPwmDeal(void)
{
	if(Status.PcbTest_f == 0)
	{
		Drying.DutyCount++;
		if(Drying.DutyCount>DryingDutySzie)
		{
			Drying.DutyCount = 0;
		}
		if(Drying.DutyCount<Drying.DutyPwm)
		{
			FanHeat_set;
		}
		else
		{
			FanHeat_clr;
		}
	}
}










