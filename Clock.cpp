/**The MIT License (MIT)
Copyright (c) 2017 by Radim Keseg
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Clock.h"
    
//public:
void Clock::SetUp(uint32_t color_hand_hour, uint32_t color_hand_mins, uint32_t color_hand_secs){
  this->color_hand_hour = color_hand_hour;
  this->color_hand_mins = color_hand_mins;
  this->color_hand_secs = color_hand_secs;
}
        
void Clock::Show(boolean clear_background, boolean mix_colors){
  uint32_t color = 0;
  int pos = 0;

  long stamp = millis();
  if(stamp - last_time_update > time_update_interval || stamp < last_time_update ){
    last_time_update = stamp;
    timeClient.updateTime();
  }

  if(strip == NULL) return;
  
  if(clear_background) strip->clear();
  
  pos = timeClient.getSecondsInt();
  pos = (pos +30)%60;
  if(mix_colors){
    color = strip->getPixelColor(pos);
    strip->setPixelColor(pos, mixColors(color, color_hand_secs));
  }else{
    strip->setPixelColor(pos, color_hand_secs);
  }
  
  pos = timeClient.getMinutesInt();
  pos = (pos +30)%60;
  if(mix_colors){
    color = strip->getPixelColor(pos);
    strip->setPixelColor(pos, mixColors(color, color_hand_mins));
  }else{
    strip->setPixelColor(pos, color_hand_mins);  
  }
  
  pos = ((timeClient.getHoursInt()%12)*5)+(timeClient.getMinutesInt()/12);
  pos = (pos +30)%60;
  if(mix_colors){
    color = strip->getPixelColor(pos);
    strip->setPixelColor( pos, mixColors(color, color_hand_hour));
  }else{
    strip->setPixelColor( pos, color_hand_hour);    
  }

  strip->show();  
}

void Clock::SetTimeOffset(int time_offset){
  timeClient.setTimeOffset(time_offset);
  timeClient.updateTime();
}
