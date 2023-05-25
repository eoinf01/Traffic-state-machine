#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>


//Student Name: Eoin Fehily
//Student Number: R00191977

struct State
{
  unsigned long Out;
  unsigned long Time;
  unsigned long Next[4];
};
typedef const struct State STyp;

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3

STyp FSM[4] = {
    {0x21, 3000, {goN, waitN, goN, waitN}},
    {0x22, 500, {goE, goE, goE, goE}},
    {0x0C, 3000, {goE, goE, waitE, waitE}},
    {0x14, 500, {goN, goN, goN, goN}}};

unsigned long S; // index to the current state

unsigned long Input = 0;

// cc.byexamples.com calls this int kbhit(), to mirror the Windows console
//  function of the same name.  Otherwise, the code is the same.
int inputAvailable()
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
  return (FD_ISSET(0, &fds));
}

int main()
{
  char data[200];
  int oldOutput = 0;

  S = goN;
  while (1)
  {
    /* add in  here your emulation of the code */
    if(FSM[S].Out != oldOutput){
      printf("Current Output: \n");
      if(FSM[S].Out & 1){
        printf("GREEN NORTH\n");
      }
      if(FSM[S].Out & 2){
        printf("YELLOW NORTH\n");
      }
      if(FSM[S].Out & 4){
        printf("RED NORTH\n");
      }
      if(FSM[S].Out & 8){
        printf("GREEN EAST\n");
      }
      if(FSM[S].Out & 16){
        printf("YELLOW EAST\n");
      }
      if(FSM[S].Out & 32){
        printf("RED EAST\n");
      }
    }

    oldOutput = FSM[S].Out;

    usleep(FSM[S].Time);

    /* TODO replace the following line with a printf of the current value of lights
            The value of the lights is in FSM[S].Out */

    //  printf("%lu",FSM[S].Out);

    //  SysTick_Wait10ms(FSM[S].Time);   // no need of this line in initial testing
    // use usleep() instead of Syst=Tick_Wait

    // Input = SENSOR;             // read sensors the input value is set in the
    //  if statement below
    if (inputAvailable())
    {
      Input = 0;
      scanf("%s", data);
      printf("you entered %s\n", data);
      if(*data == 'n'){
        Input = 2;
      }
      else if (*data == 'e')
      {
        Input = 1;
      }
      else if(*data == 'b'){
        Input = 3;
      }
      else{
        Input = 0;
      }
      
      
      /* TODO  Set the input value to 00 or 01 or 10 or 11 binary i.e. 0,1,2,3 decimal depending on the input.
               For example If the user enters N set Input to 2 decimal i.e. 10 binary. */
      
    }
    S = FSM[S].Next[Input]; // keep this line as is
  }
}
