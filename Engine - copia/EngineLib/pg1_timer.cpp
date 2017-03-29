
//---------------------------------------------------------------------------
#include "pg1_timer.h"
//---------------------------------------------------------------------------
using namespace pg1;
//---------------------------------------------------------------------------
Timer::Timer ()
:
m_dTimeBetweenFrames(0),
m_dMeasureFpsSample(0),
m_uiFPS(0),
m_uiFrameCounter(0)
{
	// nothing to do
}
//---------------------------------------------------------------------------
void Timer::firstMeasure ()
{
	QueryPerformanceFrequency(&m_kFrequency);
	QueryPerformanceCounter(&m_kPerfCount1);

	m_dTimeBetweenFrames = 0;
	m_dMeasureFpsSample = 0;
	m_uiFPS = 0;
	m_uiFrameCounter = 0;
}
//---------------------------------------------------------------------------
void Timer::measure ()
{
	QueryPerformanceCounter(&m_kPerfCount2);
	
	m_dTimeBetweenFrames = static_cast<double>
		((m_kPerfCount2.QuadPart - m_kPerfCount1.QuadPart) * 1000.0f / m_kFrequency.QuadPart);
	
	m_dMeasureFpsSample += m_dTimeBetweenFrames;

	m_uiFrameCounter++;
	m_kPerfCount1 = m_kPerfCount2;
	
	while(m_dMeasureFpsSample >= 1000)
	{
		m_dMeasureFpsSample -= 1000;
		m_uiFPS = m_uiFrameCounter;
		m_uiFrameCounter = 0;
	}
}
//---------------------------------------------------------------------------
