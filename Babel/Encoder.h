#ifndef _ENCODER_H_
# define _ENCODER_H_

#include "speex/speex.h"
#define INPUT_SIZE 160

class		Encoder
{
private:
	SpeexBits ebits;
	SpeexBits dbits;
	void *enc_state;
	void *dec_state;
	int	quality;
public:
	Encoder(int = 5);
	~Encoder();
	void	encode(short *, char *);
	void	decode(char *, short *);
};

#endif //!_ENCODER_H_