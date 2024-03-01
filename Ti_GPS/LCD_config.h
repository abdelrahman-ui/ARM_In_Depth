/*========================================================================================
===========================   - LCD_config.h		      ============================
===========================   - Created: 9/4/2021	      ============================
===========================   - Author: Abdelrahman_Magdy     ============================
===========================   - Version : _1_		      ============================
===========================   - Note :
					*-
					*-
========================================================================================*/ 

/*=======================================================================================
          
            * Configration Type : 
                                  - Prebuilt Config	:	NO
                                  - Link Time Config	:	NO
                                  - Post Build Config	:	NO
=========================================================================================*/

/*======================================================================================
=======================  guard of file will call on time in .c	========================
========================================================================================*/


#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H


#define LCD_PORT GPIOB

#define RS					  0	/* Define Register Select pin */

#define RW					  1	/* Define Register Select pin */

#define EN					  2     /* Define Register Select pin */


#endif //LCD_CONFIG_H