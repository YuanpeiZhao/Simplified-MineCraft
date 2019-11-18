#include <irrKlang/irrKlang.h>

using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();

void playBGM()
{
	SoundEngine->play2D("audio/BGM.mp3", true);
}