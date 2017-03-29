
//---------------------------------------------------------------------------
#ifndef PG1_TIMER_H
#define PG1_TIMER_H
//---------------------------------------------------------------------------
#include <Windows.h>
//---------------------------------------------------------------------------
namespace pg1
{
//---------------------------------------------------------------------------
class Timer
{
// constructor
public:
	Timer ();


// measure
public:
	void firstMeasure ();
	void measure ();

	float timeBetweenFrames () const;
	unsigned int fps () const;

private:
	double m_dTimeBetweenFrames;
	double m_dMeasureFpsSample;
	unsigned int m_uiFPS;
	unsigned int m_uiFrameCounter;

	LARGE_INTEGER m_kPerfCount1;
	LARGE_INTEGER m_kPerfCount2;
	LARGE_INTEGER m_kFrequency;
};
//---------------------------------------------------------------------------
#include "pg1_timer.inl"
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif // PG1_TIMER_H
//---------------------------------------------------------------------------
