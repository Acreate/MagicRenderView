#ifndef INTTOANY_H_H_HEAD__FILE__
#define INTTOANY_H_H_HEAD__FILE__
#pragma once

#include "../../I_Conver.h"

class IntToAny : public I_Conver {
public:
	bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const override;
};

#endif // INTTOANY_H_H_HEAD__FILE__
