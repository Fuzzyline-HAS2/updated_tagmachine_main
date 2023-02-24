void NeopixelInit()
{
  for (int i = 0; i < NeopixelNum; ++i)
  {
    pixels[i].begin();
  }
  for (int i = 0; i < NeopixelNum; ++i)
  {
    pixels[i].lightColor(color[WHITE]);
  }
}

void NeoBlink(int neo, int neoColor, int cnt, int blinkTime){
    for(int i = 0; i < cnt; i++){                          //0.5*10=5초동안 점멸
        pixels[neo].lightColor(color[BLACK]); //전체 off
        pixels[neo+3].lightColor(color[BLACK]);
        delay(blinkTime);            
        pixels[neo].lightColor(color[neoColor]); //전체 적색on
        pixels[neo+3].lightColor(color[neoColor]);
        delay(blinkTime);                   //전체 적색on
    }
}

void AllNeoOn(int neoColor){
    for (int i = 0; i < NeopixelNum; ++i)
        pixels[i].lightColor(color[neoColor]);
}

void LineNeoDown(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < NumPixels[LINE]; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 0; i < cnt; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[LINE].show();
  pixels[LINE_SUB].show();
}
void LineNeoUp(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < NumPixels[LINE]; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 16; i > 16 - cnt; i--){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[LINE].show();
  pixels[LINE_SUB].show();
}
void RoundNeoEffect(int neocolor)
{
  pixels[ROUND].clear();
  pixels[ROUND_SUB].clear();
  pixels[ROUND].show();
  pixels[ROUND_SUB].show();

  for(int i = 0; i < NumPixels[ROUND]/2; i++)
  {
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].show();
    pixels[ROUND_SUB].show();
    delay(100);
  }
}
void RoundNeoEffectDown(int neocolor)
{
  for(int i = NumPixels[ROUND]/2; i >= 0; i--)
  {
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].show();
    pixels[ROUND_SUB].show();
    delay(100);
  }
}

void RoundNeoToggle(int neoColor, int toggle){
  if(toggle%2 == 1){
    pixels[ROUND].lightColor(color[neoColor]);
    pixels[ROUND_SUB].lightColor(color[neoColor]);
  }
  else{
    pixels[ROUND].lightColor(color[BLACK]);
    pixels[ROUND_SUB].lightColor(color[BLACK]);
  }
}
void LineNeoToggle(int neoColor, int toggle){
  if(toggle%2 == 1){
    pixels[LINE].lightColor(color[neoColor]);
    pixels[LINE_SUB].lightColor(color[neoColor]);
  }
  else{
    pixels[LINE].lightColor(color[BLACK]);
    pixels[LINE_SUB].lightColor(color[BLACK]);
  }
}

void RoundNeoUp(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < 30; i++){
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 0; i < cnt; i++){
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[ROUND].show();
  pixels[ROUND_SUB].show();
}