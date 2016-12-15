	/*
		if(btn_is_pressed(BTN_LEFT_PIN) && isWirelessGood){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("LEFT btn_is_pressed \r\n");
			
			printf("Sending: %d\n\r",a);
          status = wireless_send(true, true, a);
          if(status != NRF24L01_TX_SUCCESS)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						printf("sent \n\r");
					}
          a++;
		}
		
		if(btn_is_pressed(BTN_RIGHT_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("RIGHT btn_is_pressed \r\n");
			
			printf("Sending: %d\n\r",b);
          status = wireless_send(true, true, b);
          if(status != NRF24L01_TX_SUCCESS)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						printf("sent \n\r");
					}
          b--;
		}
		
		if(btn_is_pressed(BTN_UP_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("UP btn_is_pressed \r\n");
			
			if(wireless_configure_device(individual_1_id, individual_2_id)){
				printf("Wireless Connect %d to %d successessfull \n\r", individual_1_id, individual_2_id);
				isWirelessGood = true;
			}else{
				printf("Wireless Connect %d to %d failed \n\r", individual_1_id, individual_2_id);
				isWirelessGood = false;
			}
		}
		
		if(btn_is_pressed(BTN_DOWN_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("DOWN btn_is_pressed \r\n");
			
			if(wireless_configure_device(individual_2_id, individual_1_id)){
				printf("Wireless Connect %d to %d successessfull \n\r", individual_2_id, individual_1_id);
				isWirelessGood = true;
			}else{
				printf("Wireless Connect %d to %d failed \n\r", individual_2_id, individual_1_id);
				isWirelessGood = false;
			}
		}

			*/