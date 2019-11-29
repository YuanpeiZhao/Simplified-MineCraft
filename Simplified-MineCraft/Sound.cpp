#include <irrKlang/irrKlang.h>
#include "Sound.h"
#include <glm/glm.hpp>

using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();
ISound* soundWaterFlow;
ISound* soundBird;

void playBGM()
{
	SoundEngine->play2D("audio/BGM.mp3", true);
}

void playWaterFlow()
{
	soundWaterFlow = SoundEngine->play3D("audio/Ocean.ogg", vec3df(0, 0, 0), true, false, true);
	soundWaterFlow->setMinDistance(2.0f);
}

void setWaterFlowPos(glm::vec4 pos)
{
	soundWaterFlow->setPosition(vec3df(pos.x, pos.y, pos.z));
}

void playBird()
{
	soundBird = SoundEngine->play3D("audio/Birds_screaming_loop.ogg", vec3df(0, 0, 0), true, false, true);
	soundBird->setMinDistance(1.0f);
}

void setBirdPos(glm::vec4 pos)
{
	soundBird->setPosition(vec3df(pos.x, pos.y, pos.z));
}

void soundDig()
{
	SoundEngine->play2D("audio/dig.mp3", false);
}

void soundPut()
{
	SoundEngine->play2D("audio/put.mp3", false);
}