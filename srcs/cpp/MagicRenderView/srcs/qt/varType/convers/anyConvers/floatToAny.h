#ifndef FLOATTOANY_H_H_HEAD__FILE__
#define FLOATTOANY_H_H_HEAD__FILE__
#pragma once

#include "../../I_Conver.h"

class FloatToAny : public I_Conver {
public:
	bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const override;
};

#endif // FLOATTOANY_H_H_HEAD__FILE__
