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

	void	writeBlock(T *input, int size)
	{
		if (size >= buffSize - wptr - 1)
		{
			strncpy_s(&(this->buffer[this->wptr]), size + 1, input, buffSize - wptr - 1);
			strncpy_s(this->buffer, size + 1, &input[buffSize - wptr - 1], size - (buffSize - wptr - 1));
			this->wptr = size - (buffSize - wptr - 1);
		}
		else
		{
			strncpy_s(&(this->buffer[this->wptr]), size + 1, input, size);
			this->wptr += size;
		}
		this->emptyFlag++;
	}

	void	readBlock(T *output, int size)
	{
		if (size >= buffSize - rptr - 1)
		{
			strncpy_s(output, size + 1, &(this->buffer[this->rptr]), buffSize - rptr - 1);
			strncpy_s(&output[buffSize - rptr - 1], size + 1, this->buffer, size - (buffSize - rptr - 1));
			this->rptr = size - (buffSize - rptr - 1);
		}
		else
		{
			strncpy_s(output, size + 1, &(this->buffer[this->rptr]), size);
			this->rptr += size;
		}
		output[size] = '\0';
		this->emptyFlag--;
	}
};

#endif //!_BABELBUFFER_H_