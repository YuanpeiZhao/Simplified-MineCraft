#ifndef __SOUND_H__
#define __SOUND_H__

#include <glm\glm.hpp>
#include <irrKlang/irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

void playBGM();
void playWaterFlow();
void playBird();
void soundDig();
void soundPut();
void setWaterFlowPos(glm::vec4 pos);
void setBirdPos(glm::vec4 pos);

#endif