#include <iostream>
#include "Encoder.h"

Encoder::Encoder(int quality)
{
	if (quality < 1 || quality > 10)
		quality = 5;
	speex_bits_init(&ebits);
	enc_state = speex_encoder_init(&speex_nb_mode);
	speex_encoder_ctl(enc_state,SPEEX_SET_QUALITY,&quality);
	std::cout << "Encoder Created with quality = " << quality << std::endl;
	speex_bits_init(&dbits);
    dec_state = speex_decoder_init(&speex_nb_mode);
}

Encoder::~Encoder()
{
	speex_bits_destroy(&ebits);
	speex_encoder_destroy(enc_state);
	std::cout << "Encoder destroyed" << std::endl;
}


void		Encoder::encode(ABSdecoded input, ABSencoded output)
{
	int		nbBytes;
	int		size;
	int		i = 0;
	float	in[INPUT_SIZE];

	char	*output2 = static_cast<char *>(output);
	short	*input2 = static_cast<short *>(input);
	while(i < INPUT_SIZE)
		in[i] = input2[i++];

	speex_bits_reset(&this->ebits);
	speex_encode(this->enc_state, in, &this->ebits);
	size = speex_bits_nbytes(&this->ebits);
	nbBytes = speex_bits_write(&this->ebits, output2, size);
}

void	Encoder::decode(ABSencoded input, ABSdecoded output)
{
	int frame_size;

	char	*input2 = static_cast<char *>(input);
	short	*output2 = static_cast<short *>(output);
    speex_bits_read_from(&dbits, input2, INPUT_SIZE);
    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);
    speex_decode_int(dec_state, &dbits, output2);
}
