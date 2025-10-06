#ifndef QCOLORSTACK_H_H_HEAD__FILE__
#define QCOLORSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../I_Stack.h"

class QColor;
class QColorStack  : public  I_Stack{
	using t_current_type = QColor;
	
public:
	QColorStack( );

};

#endif // QCOLORSTACK_H_H_HEAD__FILE__
