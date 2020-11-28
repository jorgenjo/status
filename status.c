// Copy line ALT-6 // Paste line CTRL-U
// Install PIP: sudo apt-get install python3-pip

// Compile
// gcc -o -status status.c
// sudo chmod u+x status


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// ---------------------------------------------------------------------------

char* f_trim2(char *src, char* dest)
{
  int i;
  int c;


  c = 0;
  for(i=0; i < strlen(src); i++)
   {
     if ( (int)src[i] >= 32 ) 
      {
         dest[c] = src[i];
         c++;
      }
      dest[c] = 0;
   }
  return dest ;
}


// -----------------------------------------------------------------

void f_removeSubstring(char *s,const char *toremove)
{
  while( s=strstr(s,toremove) )
    memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}

// ---------------------------------------------------------------------


char * f_command(char str[],int v_line){

//  printf("%s", str);

  FILE *fp;
  char path[1035];
  char buf[1035] = "not found";
  char *ret;
  char *ret1;
  int line;

  fp = popen(str, "r");  

  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }


  ret = "JJ";
  line = 1;

  // sprintf(buf,"%s","not found");

//  buf[] = "not found";

  while (fgets(path, sizeof(path)-1, fp) != NULL) {
//    printf("%s\n", path);
    ret1 = path;
    if (line == v_line){
      sprintf(buf,"%s",path);
    }
    line = line + 1;
  }

  pclose(fp);

  ret = buf;


//  ret = path;

  return ret;

}

// -------------------------------------------------------------------------

int main(){
    int v_temperature;

    int number;
    int result;
    char delimiter;
    char c[] = "abcd";
    char *st_Old;
    char *st;
    char *st2;

    int i;
    int v_i=0;

    char st1[1035];

    char st10[1035] = "";


  printf("{\"software\":{");
//  printf("{");

  st = f_command("cat name.txt",1);
  f_trim2(st,st10);
  printf("\"Name\":\"%s\",",st10);


  st = f_command("hostname -I",1);
  st[strcspn(st, "\r\n\t\r\f\b\a\v")] = 0;
  f_trim2(st,st10);
  printf("\"Ip\":\"%s\",",st10);


  st = f_command("cat /sys/class/net/eth0/address",1);
  f_trim2(st,st10);
  printf("\"Mac\":\"%s\",",st10);

  st = f_command("php -v",1);
  f_trim2(st,st10);
  printf("\"Php\":\"%s\",",st10);

  st = f_command("mysql -V",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL){
    printf("\"Mysql\":\"%s\",",st10);
  }

  st = "";
  st = f_command("lsb_release -a",2);
  f_trim2(st,st10);
  f_removeSubstring(st10,"Description:");
  printf("\"OperatingSystem\":\"%s\",",st10);

//  st = f_command("lsb_release -a",4);
//  f_trim2(st,st10);
//  f_removeSubstring(st10,"Codename:");
//  printf("\"Codename\":\"%s\",",st10);

  st = "";
  st = f_command("npm -v",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found")==NULL) {
    printf("\"Npm\":\"%s\",",st10);
  }

  st = "";
  st = f_command("node -v",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL){
    printf("\"Nodejs\":\"%s\",",st10);
  }


  st = "";
  st = f_command("git --version",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    f_removeSubstring(st10,"git ");
    printf("\"Git\":\"%s\",",st10);
  }

  st = "";
  st = f_command("pip3 -V",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    f_removeSubstring(st10,"pip ");
    printf("\"Pip3\":\"%s\",",st10);
  }


  st = "";
  st = f_command("python3 -V",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    f_removeSubstring(st10,"Python ");
    printf("\"Python\":\"%s\",",st10);
  }

  st = "";
  st = f_command("homebridge -V",1);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    f_removeSubstring(st10,"Homebridge ");
    printf("\"Homebridge\":\"%s\",",st10);
  }




  st = "";
  st = f_command("docker -v",1);
//  printf("%s",st);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    printf("\"Docker\":\"%s\",",st10);
  }

  st = f_command("cat /sys/firmware/devicetree/base/model",1);
  f_trim2(st,st10);
  printf("\"Hardware\":\"%s\",",st10);

  st = f_command("apachectl -v",1);
  f_trim2(st,st10);
  f_removeSubstring(st10,"Server version:");
  printf("\"Webserver\":\"%s\",",st10);

  st = f_command("uptime -p",1);
  f_trim2(st,st10);
  f_removeSubstring(st10,"up ");
  printf("\"Uptime\":\"%s\",",st10);


  st = f_command("cat /sys/class/thermal/thermal_zone0/temp",1);
//  st = f_command("sudo /opt/vc/bin/vcgencmd measure_temp",1);
  f_trim2(st,st10);
  v_temperature = (atoi(st10)+500)/1000;
//  f_removeSubstring(st10,"temp=");
//  f_removeSubstring(st,"'C");
  printf("\"Temperature\":\"%d Degree Celcius\",",v_temperature);


  st = f_command("df -h / | tail -1 | tr -s ' ' | cut -d' ' -f4",1);
  f_trim2(st,st10);  
  printf("\"DiskFree\":\"%s\",",st10);

  st = f_command("df -h / | tail -1 | tr -s ' ' | cut -d' ' -f2",1);
  f_trim2(st,st10);
  printf("\"DiskSize\":\"%s\",",st10);



  st = "";
  st = f_command("free -h",2);
  f_trim2(st,st10);
  if (strstr(st10,"not found" ) == NULL) {
    char st16[22];
    int i;
    int j = 0;
    for(i=0;i<22;i++){
      if ( (st10[i] > 32) && (st10[i]<127)){
        st16[j] = st10[i];
        j++;
      }
    }
    st16[j] = '\0'; // End of char;

    f_removeSubstring(st16,"Mem:");
//    f_removeSubstring(st16," ");
    printf("\"Mem\":\"%s\",",st16);
//    printf("\"Mem\":\"%s\",",st10);
  }


//  st = "";
//  st = f_command("docker -v",1);
//  f_trim2(st,st10);
//  printf("\"Docker\":\"%s\",",st);
  

  st = "Rev 1.11";
  printf("\"Status\":\"%s\"",st);

  printf("}}");
//  printf("}");


//  if (strstr(st, "9.0") != NULL) {
//    printf("OS Debian %s stretch",st);
//  } else if (strstr(st, "8.0") != NULL) {
//    printf("OS Debian %s jessie", st );
//  } else {
//    printf("OS Unknown");
//  }

  /* close */
//  pclose(fp);

  return 0;


}
