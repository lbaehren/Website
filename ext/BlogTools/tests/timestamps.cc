#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main (void)
{
  char buffer[SIZE];
  char *tzone;
  time_t timestamp;
  
  // Get and print timestamp
  timestamp = time(NULL);
  printf("%i\n", (int) timestamp);
  
  // Format string
  const char* format = "%a %e %b %Y %r %Z %n";
  
  // Print time in my default timezone (NZDT)
  strftime(buffer, SIZE, format, localtime(&timestamp));
  fputs(buffer, stdout);
  
  // Print UTC time
  tzone="TZ=UTC";
  putenv(tzone);
  strftime(buffer, SIZE, format, localtime(&timestamp));
  fputs(buffer, stdout);
  
  // Print time is the Eastern USA
  tzone="TZ=EST";
  putenv(tzone);
  strftime(buffer, SIZE, format, localtime(&timestamp));
  fputs(buffer, stdout);
  
  return 0;
}
