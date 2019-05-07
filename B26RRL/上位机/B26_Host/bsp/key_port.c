#include "key_port.h"
#include "bsp_pwm.h"

extern unsigned long get_key_data;

unsigned long Key_Port_Read(unsigned char num){
	if(num == 1){
		if(get_key_data == KEY_LIGHT_VALUE){
                    return KEY_LIGHT_VALUE;
		}else{
                     return 0x00;
		}
	}else if(num == 2){
	       if(get_key_data == KEY_HOME_VALUE){
                     return KEY_HOME_VALUE;
		 }else{
                      return 0x00;
		 }
	}else if(num == 3){
	       if(get_key_data == KEY_OPEN_VALUE){
                     return KEY_OPEN_VALUE;
		 }else{
                      return 0x00;
		 }
	}else if(num == 4){
	       if(get_key_data == KEY_CLOSE_VALUE){
                      return KEY_CLOSE_VALUE;
		 }else{
                      return 0x00;
		 }
	}else if(num == 5){
	        if(get_key_data == KEY_HEAD_UP_VALUE){
                       return KEY_HEAD_UP_VALUE;
		 }else{
                       return 0x00;
		 }
	}else if(num == 6){
	        if(get_key_data == KEY_HEAD_DOWN_VALUE){
                       return KEY_HEAD_DOWN_VALUE;
		  }else{
                       return 0x00;
		  }
	}else if(num == 7){
	        if(get_key_data == KEY_LUMBAR_UP_VALUE){
                       return KEY_LUMBAR_UP_VALUE;
		  }else{
                       return 0x00;
		  }
	}else if(num == 8){
	        if(get_key_data == KEY_LUMBAR_DOWN_VALUE){
                       return KEY_LUMBAR_DOWN_VALUE;
		  }else{
                       return 0x00;
		  }
       }else if(num == 9){
	        if(get_key_data == KEY_TABLE_UP_VALUE){
                       return KEY_TABLE_UP_VALUE;
		  }else{
                       return 0x00;
		  }
       }else if(num == 10){
	        if(get_key_data == KEY_TABLE_DOWN_VALUE){
                       return KEY_TABLE_DOWN_VALUE;
		  }else{
                       return 0x00;
		  }
	}else{
              return 0X00;
	} 
}

