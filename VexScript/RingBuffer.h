#pragma once
#include <array>

template<typename T, size_t N>
class RingBuffer
{
public:
	int put(T value) {
		if ( (m_writeIndex+1) % m_bufferSize == m_readIndex)
		{
			return NULL;
		}
		m_buffer[m_writeIndex] = value;
		m_writeIndex = (m_writeIndex + 1) % m_bufferSize;
		return 1;
	}
	int get(T* value) {
		if (m_readIndex == m_writeIndex) {
			return NULL;
		}
		*value = m_buffer[m_readIndex];
		m_readIndex = (m_readIndex + 1) % m_bufferSize;
		return 1;
	}

private:
	std::array <T,N> m_buffer;
	int m_writeIndex = 0;
	int m_readIndex = 0;
	int m_bufferSize = N;
};

