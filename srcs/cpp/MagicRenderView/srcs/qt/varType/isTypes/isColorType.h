#ifndef ISCOLORTYPE_H_H_HEAD__FILE__
#define ISCOLORTYPE_H_H_HEAD__FILE__
#pragma once
#include <qcolor.h>

#include "../I_IsType.h"

class IsColorType : public I_IsType {

	using t_current_type = QColor;
public:
	IsColorType( );
};

#endif // ISCOLORTYPE_H_H_HEAD__FILE__
