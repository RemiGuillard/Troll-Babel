#ifndef _BABELBUFFER_H_
# define _BABELBUFFER_H_

#include <string.h>

template <typename T>
class		BabelBuffer
{
private:
	T		*buffer;
	int		rptr;
	int		wptr;
	int		buffSize;
	int		emptyFlag;

public:
	BabelBuffer(int isize = 1024) : rptr(0), wptr(0), emptyFlag(0)
	{
		buffSize = isize;
		buffer = new T[isize];
	}

	bool	canRead()
	{
		return (emptyFlag > 0);
	}

	void	writeBlock(const T *input, int size)
	{
		if (size >= buffSize - wptr)
		{
			copy(&(this->buffer[this->wptr]), input, buffSize - wptr);
			copy(this->buffer, &input[buffSize - wptr - 1], size - (buffSize - wptr));
			this->wptr = size - (buffSize - wptr);
		}
		else
		{
			copy(&(this->buffer[this->wptr]), input, size);
			this->wptr += size;
		}
		this->emptyFlag++;
	}

	void	readBlock(T *output, int size)
	{
		if (size >= buffSize - rptr)
		{
			copy(output, &(this->buffer[this->rptr]), buffSize - rptr);
			copy(&output[buffSize - rptr], this->buffer, size - (buffSize - rptr));
			this->rptr = size - (buffSize - rptr);
		}
		else
		{
			copy(output, &(this->buffer[this->rptr]), size);
			this->rptr += size;
		}
		output[size] = 0;
		this->emptyFlag--;
	}

	void	copy(T *dest, const T *src, int size)
	{
		for(int i=0; i<size; ++i)
			dest[i] = src[i];
	}

	void	emptyBlock(T *dest, int size, T sample)
	{
		for(int i=0; i<size; ++i)
			dest[i] = sample;
	}
};

#endif //!_BABELBUFFER_H_