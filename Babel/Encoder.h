#ifndef _ENCODER_H_
# define _ENCODER_H_

#include "speex/speex.h"
#define INPUT_SIZE 160

class		ABSEncoder
{
private:
	int	quality;
public:
	typedef void*	ABSencoded;
	typedef void*	ABSdecoded;
	virtual void	encode(ABSdecoded, ABSencoded) = 0;
	virtual void	decode(ABSencoded, ABSdecoded) = 0;
};

class		Encoder : public ABSEncoder
{
private:
	SpeexBits	ebits;
	SpeexBits	dbits;
	void		*enc_state;
	void		*dec_state;
public:
	Encoder(int = 5);
	~Encoder();
	void	encode(ABSdecoded, ABSencoded);
	void	decode(ABSencoded, ABSdecoded);
};

#endif //!_ENCODER_H_