
//---------------------------------------------------------------------------
inline bool Input::keyDown(KeyCode eKey){
	return ( (m_ucKeyBuffer[eKey] & 0x80) != 0 );
}
//---------------------------------------------------------------------------
inline bool Input::keyUp(KeyCode eKey){
	return ( !keyDown(eKey) );
}
//---------------------------------------------------------------------------
inline bool Input::mouseDown(MouseButton eButtonID){
	return ( (m_ucMouseButton[eButtonID] & 0x80) != 0 );
}
//---------------------------------------------------------------------------
inline bool Input::mouseUp(MouseButton eButtonID){
	return ( !mouseDown(eButtonID) );
}
//---------------------------------------------------------------------------
inline long Input::mouseScrAbsPosX(){
	return m_lMouseScreenAbsPosition[0];
}
//---------------------------------------------------------------------------
inline long Input::mouseScrAbsPosY(){
	return m_lMouseScreenAbsPosition[1];
}
//---------------------------------------------------------------------------
inline long Input::mouseScrAbsPosZ(){
	return m_lMouseScreenAbsPosition[2];
}
//---------------------------------------------------------------------------
inline long Input::mouseRelPosX(){
	return m_lMouseRelPosition[0];
}
//---------------------------------------------------------------------------
inline long Input::mouseRelPosY(){
	return m_lMouseRelPosition[1];
}
//---------------------------------------------------------------------------
inline long Input::mouseRelPosZ(){
	return m_lMouseRelPosition[2];
}
//---------------------------------------------------------------------------
