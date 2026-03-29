 /* A linux shell emulator written in C for ESPs
project made by eula, open source */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_system.h"

//results in search
const char *lsres = "ls echo /home\ncat whoami reboot\nclear\n";

/* file infrastructure */
const char *ls = "/ls";
/* end of file infrastructure */

void app_main(){
//uart_set_echo_mode(UART_NUM_0, UART_ECHO_ENABLE);
printf(" LinuxESP\n===1.0.0===\n\n");
for(;;){
char wcons[200];
if(fgets(wcons, sizeof(wcons), stdin) != NULL){
wcons[strcspn(wcons, "#\n\r")] = 0;
if(strcmp(wcons, "ls") == 0){
printf("%s", lsres);
} else if(strncmp(wcons, "echo", 4) == 0){
char *strst = strchr(wcons, '\"');
char *stren = strrchr(wcons, '\"');
if(strst != NULL && stren != NULL && strst != stren){
strst++;
*stren = '\0';
printf("%s\n", strst);
}
} else if(strcmp(wcons, "whoami") == 0){
printf("root\n");
} else if(strcmp(wcons, "clear") == 0){
printf("\033[H\033[J");
} else if(strcmp(wcons, "reboot") == 0){
  printf("\033[H\033[J");
  vTaskDelay(pdMS_TO_TICKS(100));
  esp_restart();
} else if(strncmp(wcons, "cat", 3) == 0){
  char *flst = wcons + 4;
  if(strcmp(flst, "/home")!=0 && strcmp(flst, "/")!=0){
    printf("file %s\n", flst);
  } else{
    printf("cat: %s: Is a directory\n", flst);
  }
}
 else{
printf("bash: %s :command not found\n", wcons);
}
}
vTaskDelay(pdMS_TO_TICKS(12));
}
} 
