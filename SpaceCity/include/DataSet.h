#pragma once

#include <array>
#include <bits/stdc++.h>

template<size_t N>
class DataSet
{
public:
	void put(double value) {
		m_buffer[m_writeIndex] = value;
        m_writeIndex ++;
        if(m_writeIndex >= m_buffer.size()){
            m_writeIndex = 0;
        }
	}

    double getSum(){
        double sum = 0;
        for (double i : m_buffer)
        {
            sum += i;
        }
        return sum;
    }

    double getAverage(){
        return getSum() / double(m_buffer.size());
    };

    double getMedian(){
        sort();
        return m_sortedBuffer[m_sortedBuffer.size()/2];
    };

protected:

    void sort(){

        int i, j, n;
        bool swapped;

        m_sortedBuffer = m_buffer;
        n = m_sortedBuffer.size();

        for (i = 0; i < n - 1; i++) {
            swapped = false;
            for (j = 0; j < n - i - 1; j++) {
                if (m_sortedBuffer[j] > m_sortedBuffer[j + 1]) {
                    std::swap(m_sortedBuffer[j], m_sortedBuffer[j + 1]);
                    swapped = true;
                }
            }
    
            // If no two elements were swapped
            // by inner loop, then break
            if (swapped == false)
                break;
        }
    };

    std::array <double ,N> m_buffer;
    std::array <double ,N> m_sortedBuffer;
	int m_writeIndex = 0;
};



