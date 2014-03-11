#include <time.h>
#include <stdio.h>

int main()
{
  time_t now;
  
  now = time(0);
 struct tm *tnow = localtime(&now);
  printf("%d %d %d %d %d %d\n", 1900+tnow->tm_year,
         tnow->tm_mon+1,
         tnow->tm_mday,
         tnow->tm_hour,
         tnow->tm_min,
         tnow->tm_sec);
}
