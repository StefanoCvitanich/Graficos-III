//---------------------------------------------------------------------------
#include "input.h"
//---------------------------------------------------------------------------
Input::Input(){
	reset();
}
//---------------------------------------------------------------------------
Input::~Input(){
	// TO-DO:
}
//---------------------------------------------------------------------------
void Input::reset(){
	memset( &m_ucKeyBuffer, 0, sizeof(m_ucKeyBuffer) );

	m_lMouseScreenAbsPosition[0] = 0;
	m_lMouseScreenAbsPosition[1] = 0;
	m_lMouseScreenAbsPosition[2] = 0;

	m_lMouseRelPosition[0] = 0;
	m_lMouseRelPosition[1] = 0;
	m_lMouseRelPosition[2] = 0;
	
	m_ucMouseButton[0] = 0;
	m_ucMouseButton[1] = 0;
	m_ucMouseButton[2] = 0;
}
//---------------------------------------------------------------------------
