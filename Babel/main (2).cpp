#include <iostream>
#include <string>
#include "portaudio.h"
#include "AbsIOSound.h"
#include "PaIOSound.h"
#include "Encoder.h"

int main()
{
	AbsIOSound<short> *test = new PaIOSound;
	Encoder		*encode = new Encoder(8);
	/*encode->encode(data->IBuf, data->encode);
	encode->decode(data->encode, data->OBuf);*/
	/*data->OBuf = data->IBuf;
	data->OMaxFrameIndex = 160 /2;
	data->OAvailable = true;*/

	try
	{
		test->recordVoice();

		IOStreamData<short>	*data = test->getdata();
		int i;
		while (1)
		{
			if (data->IAvailable)
			{
				for (i=0; i<160;i++)
				{	
					data->OBuf[i] = data->IBuf[i];
				}
				/*encode->encode(data->IBuf, data->encoded);
				encode->decode(data->encoded, data->OBuf);*/
				data->OMaxFrameIndex = 80;
				data->OAvailable = true;
				data->IAvailable = false;
			}
		}
	}
	catch (char const *e)
	{
		std::cerr << e << std::endl;
	}
	Pa_Sleep(30 * 1000);

	return 0;
}