# Breakout PCB for RFM12B radio transceiver 

<img src="https://raw2.github.com/uChip/RFM12B_BOB/master/RFM12B_BOB.png" alt="RFM12B Breakout Board" height="270" width="200">___<img src="https://raw2.github.com/uChip/RFM12B_BOB/master/RFM12B_BOB.jpg" alt="RFM12B Breakout Board in action" height="300" width="200">

Eagle CAD PCB designs for radio transceiver breakout board. 
Converts the RFM12B radio transceiver from SMT to 0.1" breadboard format.  This board uses the same pinout as the [JeeLabs RFM12B breakout board] (http://www.digitalsmarties.net/products/rfm12b-board) for compatibility.  

See the following link for Arduino drivers for the RFM12B  
  * https://github.com/LowPowerLab/RFM12B

A modified version of the RFM12B drivers that allows interchange between RFM69s and RFM12Bs is available in my github (forked from https://github.com/aanon4/RFM12B).

Hookup of the breakout board to 5V Arduino SPI connection.  All board components populated.  Solder-jumpers left open.  

	Arduino			RFM12B BOB  
	  5V	-->		  5V  
	  GND	<-->	  GND  
	  D11	-->		  SDI  
	  D12	<--		  SDO  
	  D13	-->		  SCK  
	  D10	-->		  SEL  
	  D2	<--		  IRQ  
	  		<--		  3V3  
 
Hookup of the breakout board to 3.3V Arduino SPI connection.  On PCB populate only radio module, antenna, C2 and C3.  Short the pads on the solder-jumpers.  

	Arduino			RFM12B BOB  
	  NC	 		  5V  
	  GND	<-->	  GND  
	  D11	-->		  SDI  
	  D12	<--		  SDO  
	  D13	-->		  SCK  
	  D10	-->		  SEL  
	  D2	<--		  IRQ  
 	  3.3V	-->		  3V3  


## Order PCBs  

You can order this PCB directly from OSH Park.  Click on the following link.  
  * Radio Breakout - http://oshpark.com/shared_projects/MwhnLfdu 

See Bill of Materials file in repo for parts list.  

## Status  
  * PCB layout has been tested to be functional.   

## File Formats  

Design files are in "CadSoft EAGLE PCB Design Software" .brd and .sch formats.  
A free version of the software can be downloaded from www.cadsoftusa.com.  

## Distribution License  

You may use this PCB design however you like but no liability is accepted.  
