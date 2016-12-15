#include "game_ui_define.h"


//getting character code/ sending
static bool handShake = false;

void player_handler(Pokemon *pkm, Pokemon *opp){
	
	uint32_t data;
	wireless_com_status_t status;

	pkm->charCode = MY_POKEMON;//!!!!!!!!!!!!!!!!!!!!!
	while(!handShake){
		printf("Sending: %d\n\r",ME);
          status = wireless_send(true, true, MY_POKEMON);
          if(status != NRF24L01_TX_SUCCESS)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						printf("sent \n\r");
					}
		if(WIRELESS_RX_ALERT){
			
				WIRELESS_RX_ALERT = false;

				status = wireless_get(true, &data);

				printf("received data: %d\n", data);
			
				if(status != NRF24L01_RX_SUCCESS || data > POKEMMON_COUNT)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						handShake = true;
						opp->charCode = data;//!!!!!!!!!!!!!!!!!!!!!
					}
		}
	}
}

void waiting_room(Pokemon *pkm, Pokemon *opp){
	
	lcd_clear_screen(LCD_COLOR_BLACK );

	printf("lalallalalalala\n\r");
	
	switch(ME){
		case PLAYER_1:
			player_handler(pkm, opp);
			break;
		case PLAYER_2:
			player_handler(pkm, opp);
			break;
		default:
			select_player_screen();
			break;
	}
	
}

