#include <stdio.h>
#include <xio.h>
#include <xil_io.h>

#include "xparameters.h"
#include "cam_ctrl_header.h"
#include "vmodcam_header.h"
#include "xuartlite.h"


#define blDvmaCR		0x00000000 // Control Reg Offset
#define blDvmaFWR		0x00000004 // Frame Width Reg Offset
#define blDvmaFHR		0x00000008 // Frame Height Reg Offset
#define blDvmaFBAR	0x0000000c // Frame Base Addr Reg Offset
#define blDvmaFLSR	0x00000010 // Frame Line Stride Reg Offeset
#define blDvmaHSR		0x00000014 // H Sync Reg Offset
#define blDvmaHBPR	0x00000018 // H Back Porch Reg Offset
#define blDvmaHFPR	0x0000001c // H Front Porch Reg Offset
#define blDvmaHTR		0x00000020 // H Total Reg Offset
#define blDvmaVSR		0x00000024 // V Sync Reg Offset
#define blDvmaVBPR	0x00000028 // V Back Porch Reg Offset
#define blDvmaVFPR	0x0000002c // V Front Porch Reg Offset
#define blDvmaVTR		0x00000030 // V Total Reg Offset

void main() {

	u8 initialize[2] = {0x80, 0x84};
	u8 forward_command[16] = {0x98, 0xD, 0x89, 0x1, 0x2C, 0x80, 0x0, 0x9C, 0x1, 0x90, 0x89, 0x0, 0x0, 0x0, 0x0, 0x99};

	u8 turn_left1[16] = {0x98, 0x1D, 0x89, 0x1, 0x2C, 0x0, 0x1, 0x9D, 0x0, 0x5A, 0x89, 0x1, 0x2C, 0x80, 0x0, 0x9C};
	u8 turn_left2[16] = {0x1, 0x90, 0x89, 0x1, 0x2C, 0xFF, 0xFF, 0x9D, 0xFF, 0xA6, 0x89, 0x0, 0x0, 0x0, 0x0, 0x99};
	u8 turn_left[32] = {0x98, 0x1D, 0x89, 0x1, 0x2C, 0x0, 0x1, 0x9D, 0x0, 0x5A, 0x89, 0x1, 0x2C, 0x80, 0x0, 0x9C, 0x1,
			0x90, 0x89, 0x1, 0x2C, 0xFF, 0xFF, 0x9D, 0xFF, 0xA6, 0x89, 0x0, 0x0, 0x0, 0x0, 0x99};


	u8 turn_right[32] = {152, 29, 137, 1, 44, 255, 255, 157, 255, 166, 137, 1, 44, 128, 0, 156,
			1, 144, 137, 1, 44, 0, 1, 157, 0, 90, 137, 0, 0, 0, 0, 153};
	u8 turn_right1[16] = {152, 29, 137, 1, 44, 255, 255, 157, 255, 166, 137, 1, 44, 128, 0, 156};
	u8 turn_right2[16] = {1, 144, 137, 1, 44, 0, 1, 157, 0, 90, 137, 0, 0, 0, 0, 153};

	u8 backward_command[32] = {152, 29, 137, 1, 44, 0, 1, 157, 0, 180, 137, 1, 44, 128, 0, 156, 1, 144, 137, 1, 44,
			255, 255, 157, 255, 76, 137, 0, 0, 0, 0, 153};
	u8 backward1[16] = {152, 29, 137, 1, 44, 0, 1, 157, 0, 180, 137, 1, 44, 128, 0, 156};
	u8 backward2[16] = {1, 144, 137, 1, 44, 255, 255, 157, 255, 76, 137, 0, 0, 0, 0, 153};

	u8 right_tri1[16] = {152, 53, 137, 1, 44, 255, 255, 157, 255, 136, 137, 1, 44, 128, 0, 156};
	u8 right_tri2[16] = {2, 88, 137, 1, 44, 255, 255, 157, 255, 136 ,137, 1, 44, 128, 0, 156};
	u8 right_tri3[16] = {2, 88, 137 ,1, 44, 255, 255, 157, 255, 136, 137, 1, 44, 128, 0, 156};
	u8 right_tri4[8] = { 2, 88, 137, 0, 0, 0, 0, 153};






	u8 left_tri1[16] = {152, 53, 137, 1, 44, 0, 1, 157, 0, 120, 137, 1, 44, 128, 0, 156};
	u8 left_tri2[16] ={2, 88, 137, 1 ,44 ,0 ,1 ,157 ,0 ,120, 137 ,1 ,44 ,128 ,0 ,156 };
	u8 left_tri3[16] = {2 ,88 ,137 ,1 ,44 ,0 ,1 ,157 ,0 ,120 ,137, 1 ,44 ,128 ,0 ,156 };
	u8 left_tri4[8] = {2 ,88 ,137 ,0 ,0 ,0 ,0 ,153};




	XUartLite UartLite;
	XUartLite_Initialize(&UartLite, XPAR_XPS_UARTLITE_0_DEVICE_ID);

	// Set iRobot into full mode
	XUartLite_Send(&UartLite, initialize, 1);
	XUartLite_Send(&UartLite, initialize + 1, 1);

	// Sleep for 2 seconds
	int i,j;
	for (j=0;j<2;j++)
		for (i=0;i<25000000;i++)
			asm("nop");

	//XUartLite_ResetFifos(&UartLite);
	//for (i=0; i < 32; i++)
	//{
//		XUartLite_Send(&UartLite, turn_right1, 16);
//		for (i=0; i < 2500000; i++)
//			{
//
//			}
//		XUartLite_Send(&UartLite, turn_right2, 16);

	//}
//	for (i=0; i < 25000000; i++)
//	{
//
//	}


	// Move forward

	//print("Done\n");
	//XUartLite_Send(XUartLite *InstancePtr, u8 *DataBufferPtr, unsigned int NumBytes);


	u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;
	int posX, posY;
	int color;
	//xil_printf("in main\n");
	for(posX = 0; posX<2560; posX++)
		for(posY = 0; posY<720; posY++)
			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*2560+posX), (posX/40)<<4);

	XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40); // hsync
	XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260); // hbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650); // htr
	XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5); // vsync
	XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25); // vbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745); // vfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750); // vtr
		
	XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500); // frame width
	XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0); // frame height
	XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
	XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00); // frame line stride
	XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003); // dvma enable, dfl enable

	//CamIicCfg(XPAR_CAM_IIC_0_BASEADDR, CAM_CFG_640x480P);
	CamIicCfg(XPAR_CAM_IIC_1_BASEADDR, CAM_CFG_1280x720P);
	//CamCtrlInit(XPAR_CAM_CTRL_0_BASEADDR, CAM_CFG_640x480P, 640*2);
	CamCtrlInit(XPAR_CAM_CTRL_1_BASEADDR, CAM_CFG_1280x720P, 0);
	Xuint16 read_value;

	int left = 0;
	int mid = 0 ;
	int right = 0;


	int top = 0;
	int under_top = 0;
	int center = 0;
	int above_bottom = 0;
	int bottom = 0;
	int center_top_square = 0;
	int bottom_left_square = 0;
	int bottom_right_square = 0;

	int prev_state = 0;
	int cur_state = 0;

	int threshold = 500;

	int pp_state2 = 0;
	int prev_state2 = 0;
	int cur_state2 = 0;

	int special_gesture = 0;
	int pp_state3 = 0;
	int prev_state3= 0;
	int cur_state3= 0;
	
	int delay = 40000000;

	while (1)
	{


		//	Dividing into regions
		u8 red;
		u8 green;
		u8 blue;
		for(posX = 50; posX < 250; posX++)//left region
		{
			for(posY = 288; posY < 576; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				left = left + red + green + (blue - 3);
			}
		}



		for(posX = 1050; posX < 1250; posX++)//right region
		{
			for(posY = 288; posY < 576; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				right = right + red + green + (blue - 3);
			}
		}

		for(posX = 540; posX < 740; posX++)//middle region
		{
			//for(posY = 335; posY < 385; posY++)
			for(posY = 288; posY < 576; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				mid = mid + red + green + (blue - 3);
			}
		}

		for(posX = 300; posX < 980; posX++)//top region
		{
			for(posY = 150; posY < 200; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				top = top + red + green + (blue - 3);
			}
		}

		for(posX = 300; posX < 980; posX++)
		{
			for(posY = 450; posY < 500; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				under_top = under_top + red + green + (blue - 3);
			}
		}

		for(posX = 300; posX < 980; posX++) 	// new center region
		{
			for(posY = 690; posY < 740 ;posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				center = center + red + green + (blue - 3);
			}
		}

		for(posX = 300; posX < 980; posX++)
					{
						for(posY = 900; posY < 950; posY++)
						{
							read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
							red = (read_value >> 8) & 0xF;
							green = (read_value >> 4) & 0xF;
							blue = (read_value >> 0) & 0xF;
							above_bottom = above_bottom + red + green + (blue - 3);
						}
					}
		for(posX = 300; posX < 980; posX++)
		{
			for(posY = 1250; posY < 1300; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				bottom = bottom + red + green + (blue - 3);
			}
		}

		for(posX = 540; posX < 740; posX++)
		{
			for(posY = 0; posY < 100; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				center_top_square = center_top_square + red + green + (blue - 3);
			}
		}

		for(posX = 0; posX < 200; posX++)
		{
			for(posY = 1340; posY < 1440; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				bottom_left_square = bottom_left_square + red + green + (blue - 3);
			}
		}
		for(posX = 1080; posX < 1280; posX++)
		{
			for(posY = 1340; posY < 1440; posY++)
			{
				read_value = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*1280+posX));
				red = (read_value >> 8) & 0xF;
				green = (read_value >> 4) & 0xF;
				blue = (read_value >> 0) & 0xF;
				bottom_right_square = bottom_right_square + red + green + (blue - 3);
			}
		}

		left = left - 86400+108000;
		mid = mid - 86400-28800;
		right = right - 144000-122400;
		top = top - 68000;
		under_top = under_top - 68000;
		center = center - 68000;
		above_bottom = above_bottom - 68000;
		bottom = bottom - 68000;
		center_top_square = center_top_square - 40000;
		bottom_right_square = bottom_right_square - 100000;
		bottom_left_square = bottom_left_square + 20000;




		//Special gesture detection
		if (left > threshold && mid <= threshold && right > threshold && special_gesture != 1)
		{
			//xil_printf("Special gesture\n");
			special_gesture = 1;
			pp_state3 = 0;
			prev_state3= 0;
			cur_state3= 0;

		}

		if(left > mid && left > right)
		{
//			xil_printf("LEFT \n");
			cur_state = 1;
		}
		else if(right > mid && left < right)
		{
//			xil_printf("RIGHT \n");
			cur_state = 2;
		}
		else if(left< mid && mid> right)
		{
//			xil_printf("MID \n");
			cur_state = 3;
		}

		int tmp = 0;
		if(mid > threshold && top > threshold && under_top > threshold)//close
				{
		//			xil_printf("close \n");
					tmp = 1;
				}

		else if(center > threshold && top <= threshold && under_top > threshold)//mid
				{
		//			xil_printf("mid \n");
					tmp = 2;
				}
		else if(center> threshold && top <= threshold && under_top <= threshold)//far
		{
//			xil_printf("far \n");
			tmp = 3;

		}

		else if(center <= threshold && bottom > threshold && above_bottom > threshold)
				{
			tmp = 4;
				}

		else if(center <= threshold && bottom > threshold && above_bottom <= threshold)
			{
			tmp= 5;
			}


		if(cur_state2 != tmp)
		{
			pp_state2 = prev_state2;
			prev_state2 = cur_state2;
			cur_state2 = tmp;
//			xil_printf("pp_state: %d, prev_state: %d, cur_state: %d \n", pp_state2, prev_state2, cur_state2);
		}


		int tmp_special = 0;
		if(center_top_square > threshold && bottom_left_square <= threshold && bottom_right_square <= threshold)//top of triangle
						{

							tmp_special= 1;
						}

		else if(center_top_square <= threshold && bottom_left_square >threshold && bottom_right_square <= threshold)//left of triangle
				{
					tmp_special= 2;
						}
		else if(center_top_square <= threshold && bottom_left_square <= threshold && bottom_right_square >threshold)//right of triangle
		{
			tmp_special= 3;

		}


		if (special_gesture == 0)
		{
			if((pp_state2 == 1 && prev_state2 == 2 && cur_state2 == 3)||(pp_state2 == 2 && prev_state2 == 3 && cur_state2 == 4) ||(pp_state2 == 3 && prev_state2 == 4 && cur_state2 == 5))
			{
				//xil_printf("Moving BACKWARD \n");
				XUartLite_Send(&UartLite, backward1, 16);
				for (i=0; i < 2500000; i++)
				{

				}
				XUartLite_Send(&UartLite, backward2, 16);
				for (i=0; i < delay; i++)
				{

				}

				pp_state2 = 0;
				prev_state2 = 0;
				cur_state2 = 0;

			}
			else if((pp_state2 == 3 && prev_state2 == 2 && cur_state2 == 1)||(pp_state2 == 4 && prev_state2 == 3 && cur_state2 == 2) ||(pp_state2 == 5 && prev_state2 == 4 && cur_state2 == 3))
			{
				//xil_printf("Moving FORWARD\n");

				for (i=0; i < 16; i++)
				{
					XUartLite_Send(&UartLite, &(forward_command[i]), 1);
				}
				for (i=0; i < delay; i++)
				{

				}
				pp_state2 = 0;
				prev_state2 = 0;
				cur_state2 = 0;

			}

			if((prev_state == 1 && (cur_state == 2 || cur_state == 3)) || (cur_state == 2 && prev_state == 3))
			{
				// Turn RIGHT

				XUartLite_Send(&UartLite, turn_right1, 16);
				for (i=0; i < 2500000; i++)
				{

				}
				XUartLite_Send(&UartLite, turn_right2, 16);
				for (i=0; i < delay; i++)
				{

				}

				prev_state = 0;
				cur_state = 0;
			}
			else if((prev_state == 2 && (cur_state == 1 || cur_state == 3)) || (cur_state == 1 && prev_state == 3))
			{
//				xil_printf("Moving left \n");
				XUartLite_Send(&UartLite, turn_left1, 16);
				for (i=0; i < 2500000; i++)
				{

				}
				XUartLite_Send(&UartLite, turn_left2, 16);
				for (i=0; i < delay; i++)
				{

				}


				prev_state = 0;
				cur_state = 0;
			}
		}
		else // SPECIAL MODE
		{
			if((cur_state3 != tmp_special) && tmp_special !=0){
				pp_state3 = prev_state3;
				prev_state3 = cur_state3;
				cur_state3 = tmp_special;
				//xil_printf("pp_state: %d, prev_state: %d, cur_state: %d \n", pp_state3, prev_state3, cur_state3);

			}
			if(pp_state3 == 1 && prev_state3 == 3 && cur_state3 == 2){
				//xil_printf("RIGHT TRIANGLE \n");
				special_gesture = 0;
				XUartLite_Send(&UartLite, right_tri1, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, right_tri2, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, right_tri3, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, right_tri4, 8);



				for (i=0; i < delay; i++)
				{

				}
			}

			else if(pp_state3 == 1 && prev_state3 == 2 && cur_state3 == 3){
				//xil_printf("LEFT TRIANGLE \n");
				special_gesture = 0;
				XUartLite_Send(&UartLite, left_tri1, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, left_tri2, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, left_tri3, 16);
				for (i=0; i < 2500000; i++){}
				XUartLite_Send(&UartLite, left_tri4, 8);



				for (i=0; i < delay; i++)
				{
				}
			}
		}

		left = 0;
		mid = 0;
		right = 0;
		top = 0;
		under_top = 0;
		center = 0;
		bottom = 0;
		above_bottom = 0;
		center_top_square = 0;
		bottom_left_square = 0;
		bottom_right_square = 0;
		prev_state = cur_state;

	}

}
