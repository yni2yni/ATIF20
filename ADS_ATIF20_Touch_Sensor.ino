// ADS Touch Sensor Test Example Program (IC P/N:ATIF20 )
// Code: 
// Date: 2019.08.23  Ver.: 0.0.4
// H/W Target: ARDUINO UNO R3, S/W: Arduino IDE  1.8.9
// Author: Park, Byoungbae (yni2yni@hanmail.net)
// Note: More information? Please send to e-mail.
// Uno R3, A4:SDA, A5: SCL, Leonardo 2:SDA,3:SCL

#include <Wire.h>

#define LF        0x0A //New Line
#define CR        0x0D //Carriage  return
#define SP        0x20 //Space

#define Ch_enable1  0x01 //Touch Channel Enable/Disable (CS8~cs1)
#define Ch_enable2  0x02 //Touch Channel Enable/Disable 	(Cs16~cs9)
#define Ch_enable3  0x03 //Touch Channel Enable/Disable	(Cs20~cs17)
#define I2c_id		0x04 //I2C Address of ATIF20

#define Clock_ctrl  0x2A //Clock Control Register (init_cal_opt,Reserved, clk_sel, rb_sel)
#define Global_ctrl1 0x2C //Global Option Control Register1 
	 //(response_off_ctrl, response_ctrl, bf_mode, Software Reset)
#define State_count 0x2D //Cal_pre_scale
#define Global_ctrl2 0x2E //Global Option Control Register2
	//(imp_sel,Single/Multi 0=Multi ,Cal_Hold_time,Reserved, clock_off)
#define Cal_speed	 0x2F //Calibration Speed Control at BF mode
#define Cal_BS_speed 0x30 //Calibration Speed Control at BS mod

// Sensitivity level (threshold, Register Value X 0.025% = (1 Step=0.025%)							
#define Sensitivity1  	0x33 //ch1,Default: 0x1C X 0.025% = 0.70% (threshold)
#define Sensitivity2  	0x34 //ch2
#define Sensitivity3  	0x35 //ch3
#define Sensitivity4  	0x36 //ch4
#define Sensitivity5  	0x37 //ch5
#define Sensitivity6  	0x38 //ch6
#define Sensitivity7  	0x39 //ch7
#define Sensitivity8  	0x3A //ch8
#define Sensitivity9  	0x3B //ch9
#define Sensitivity10  	0x3C //ch10
#define Sensitivity11  	0x3D //ch11
#define Sensitivity12  	0x3E //ch12
#define Sensitivity13  	0x3F //ch13
#define Sensitivity14  	0x40 //ch14
#define Sensitivity15  	0x41 //ch15
#define Sensitivity16  	0x42 //ch16
#define Sensitivity17  	0x43 //ch17
#define Sensitivity18  	0x44 //ch18
#define Sensitivity19  	0x45 //ch19
#define Sensitivity20 	0x46 //ch20

#define Output1  0x62 //Touch Output Data Register (cs8~cs1)
#define Output2  0x63 //Touch Output Data Register (cs16~cs9)
#define Output3  0x64 //Touch Output Data Register (cs20~cs17)

#define mask1  0x76 //Mask1 : Reset Value 0x6D
#define mask2  0x77 //Mask2 : Reset Value 0x0A

// ============= ATIF20 I2C Slave Address ============================//
#define ATIF20_ID_GND  0x34 //0x68<<1 (7bit=0x34, 8bit=0x68, ID Pin=GND)
#define ATIF20_ID_VDD  0x2C //0x58<<1 (7bit=0x2C, 8bit=0x58, ID Pin=VDD)
// ===================================================================//
void  Init_ATIF20(void); //Initialize ATIF20

#define RESET_PIN 7 //Reset pin
#define EN_PIN    6 //I2C Enable Pin

void setup(){
  delay(200); //wait for 200[msec]
  
  Wire.begin();        // join i2c bus (address optional for master)
  Wire.setClock(400000);// 400Khz
  Serial.begin(115200);  // start serial for output (Speed)
  //put your setup code here, to run once:
 
  pinMode(RESET_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  
  Init_ATIF20(); //Initialize ATIF20
  delay(100); //wait for 200[msec]
    
}
void loop() {

  byte read_data[2]={0};
 
  Wire.beginTransmission(ATIF20_ID_VDD); // send ic slave address
  Wire.write(byte(Output1)); // sends register address 
  Wire.endTransmission(); // stop transmitting
  Wire.requestFrom(ATIF20_ID_VDD,3); // key data read (3 byte)
  read_data[0]=Wire.read();
  read_data[1]=Wire.read();
  read_data[2]=Wire.read();
  Wire.endTransmission(); // 
   
  Serial.write(10); 
  Serial.print("-------Touch Sensor Output Data  ---- > ");// Test Code
  delay(100);
     
  Serial.print(read_data[0],HEX); 
  Serial.write(SP); 
  Serial.print(read_data[1],HEX); 
  Serial.write(SP); 
  Serial.print(read_data[2],HEX); 
  Serial.write(SP); 
  Serial.write(LF);   
  Serial.write(CR);

  delay(100);   
}

void  Init_ATIF20(void)
{
   //------------------ Software Reset Enable (Set)----------------------
   Wire.beginTransmission(ATIF20_ID_VDD); // 
   Wire.write(byte(Global_ctrl1)); // 0x2Ch
   Wire.write(byte(0x4D)); // 
   Wire.endTransmission(); // 
   
// --------------- Hidden Register Start ---------------------------------
// user does not change the register. please contact to us.
// -----------------------------------------------------------------------
   Wire.beginTransmission(ATIF20_ID_VDD);// Start
   Wire.write(byte(0x05)); // Start Register address 0x05h
   Wire.write(byte(0x80)); // data, 0x05h
   Wire.write(byte(0x11)); // data, 0x06h
   Wire.write(byte(0x11)); // data, 0x07h
   Wire.write(byte(0x11)); // data, 0x08h
   Wire.write(byte(0x11)); // data, 0x09h
   Wire.write(byte(0x11)); // data, 0x0Ah
   Wire.write(byte(0x11)); // data, 0x0Bh
   Wire.write(byte(0x01)); // data, 0x0Ch
   Wire.write(byte(0x10)); // data, 0x0Dh
   Wire.write(byte(0xCE)); // data, 0x0Eh, Value
   Wire.write(byte(0x20)); // data, 0x0Fh
   Wire.write(byte(0xFF)); // data, 0x10h
   Wire.write(byte(0x92)); // data, 0x11h, 
   Wire.write(byte(0x8F)); // data, 0x12h
   Wire.write(byte(0x07)); // data, 0x13h
   Wire.write(byte(0x1F)); // data, 0x14h, Value
   Wire.write(byte(0x17)); // data, 0x15h
   Wire.write(byte(0x03)); // data, 0x16h, Value
   Wire.write(byte(0x64)); // data, 0x17h
   Wire.write(byte(0x2B)); // data, 0x18h
   Wire.write(byte(0x11)); // data, 0x19h
   Wire.write(byte(0x03)); // data, 0x1Ah, Value
   Wire.write(byte(0xFF)); // data, 0x1Bh
   Wire.write(byte(0x39)); // data, 0x1Ch
   Wire.write(byte(0x00)); // data, 0x1Dh
   Wire.endTransmission(); //   Enad

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x29)); // address, 0x29h
   Wire.write(byte(0x0C)); // data  //Fast BS Disable
   Wire.endTransmission(); // 

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x2B)); // address, 0x2Bh
   Wire.write(byte(0xC0)); // data (Sense Freq. Low)
   Wire.endTransmission(); // 
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x31)); // address , 0x31h
   Wire.write(byte(0x0D)); // data
   Wire.endTransmission(); // 

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x32)); // address, x32h
   Wire.write(byte(0x00)); // data
   Wire.endTransmission(); //   

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x47)); // address, 0x47h
   Wire.write(byte(0x00)); // data
   Wire.endTransmission(); // 

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x48)); // address, 0x48h
   Wire.write(byte(0x33)); // data
   Wire.endTransmission(); // 

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x49)); // address 0x49h
   Wire.write(byte(0x00)); // data, 0x49h
   Wire.write(byte(0x00)); // data, 0x4Ah
   Wire.write(byte(0x00)); // data, 0x4Bh
   Wire.write(byte(0x00)); // data, 0x4Ch
   Wire.write(byte(0x00)); // data, 0x4Dh
   Wire.write(byte(0x00)); // data, 0x4Eh
   Wire.write(byte(0x00)); // data, 0x4Fh
   Wire.write(byte(0x00)); // data, 0x50h
   Wire.write(byte(0x00)); // data, 0x51h
   Wire.write(byte(0x00)); // data, 0x52h   

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x54)); // address
   Wire.write(byte(0x00)); // data
   Wire.endTransmission(); // 

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x55)); // address
   Wire.write(byte(0x00)); // data
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(0x56)); // address 0x56h
   Wire.write(byte(0x02)); // data, 0x56h
   Wire.write(byte(0x08)); // data, 0x57h
   Wire.write(byte(0x02)); // data, 0x58h
   Wire.write(byte(0x08)); // data, 0x59h
   Wire.write(byte(0x00)); // data, 0x5Ah
   Wire.write(byte(0x00)); // data, 0x5Bh
   Wire.write(byte(0x20)); // data, 0x5Ch
   Wire.write(byte(0x62)); // data, 0x5Dh
   Wire.write(byte(0x00)); // data, 0x5Eh
   Wire.write(byte(0x00)); // data, 0x5Fh
   Wire.endTransmission(); //    
// --------------- Hidden Register End-------------------------------
// ---------------- user Register ---------------------//   

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Ch_enable1)); // 0x01h
   Wire.write(0xFF); // 0:Touch Key Disable, 1: Touch Key Enable
   Wire.write(0xFF); // 0:Touch Key Disable, 1: Touch Key Enable
   Wire.write(0x0F); // 0:Touch Key Disable, 1: Touch Key Enable
   Wire.endTransmission(); // 
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Clock_ctrl)); // 0x2Ah
   Wire.write(0x65); // 0x65
   Wire.endTransmission(); //      

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(State_count)); // 0x2Dh
   Wire.write(0xE6); // 0xFF
   Wire.endTransmission(); //

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Global_ctrl2)); // 0x2Eh
   Wire.write(0x80); // 0x80
   Wire.endTransmission(); //

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Cal_speed)); // 0x2Fh
   Wire.write(0x66); // 0x66
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Cal_BS_speed)); // 0x30h
   Wire.write(0x66); // 0x66
   Wire.endTransmission(); //
   
//------------ Sensitivity control  -----------------------------------
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity1)); // 0x33h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //      

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity2)); // 0x34h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity3)); // 0x35h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity4)); // 0x36h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity5)); // 0x37h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity6)); // 0x38h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity7)); // 0x39h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //   
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity8)); // 0x3Ah
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //  
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity9)); // 0x3Bh
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity10)); // 0x3Ch
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity11)); // 0x3Dh
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity12)); // 0x3Eh
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity13)); // 0x3Fh
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity14)); // 0x40h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity15)); // 0x41h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity16)); // 0x42h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity17)); // 0x43h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    

   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity18)); // 0x44h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity19)); // 0x45h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
   
   Wire.beginTransmission(ATIF20_ID_VDD);// 
   Wire.write(byte(Sensitivity20)); // 0x46h
   Wire.write(0x24); // HEX x 0.025 = 0.90%
   Wire.endTransmission(); //    
  
//------------------ Software Reset Disable (Clear) ---------------------
   Wire.beginTransmission(ATIF20_ID_VDD); // 
   Wire.write(byte(Global_ctrl1)); // 0x2Ch
   Wire.write(byte(0x4C)); // 
   Wire.endTransmission(); // 

//   Wire.beginTransmission(ATIF20_ID_VDD); // 
//   Wire.write(byte(mask1)); // 0x76h
//   Wire.write(byte(0x6D)); // 
//   Wire.endTransmission(); // 

//   Wire.beginTransmission(ATIF20_ID_VDD); // 
//   Wire.write(byte(mask2)); // 0x77h
//   Wire.write(byte(0x00)); // 
//   Wire.endTransmission(); //    
   
   }
// End
