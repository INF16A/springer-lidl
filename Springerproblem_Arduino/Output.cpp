#include <Arduino.h>
#include "Output.h"
#include "MemoryFree.h"
void out(const char* str) 
{
  Serial.print(str);
}

void outln(const char* str)
{
  Serial.print(str);
  Serial.print("   FREEMEM=");
  Serial.println(freeMemory());
}

void outInt(int in) 
{
  Serial.print(in);
}
