#ifndef UINTTOANY_H_H_HEAD__FILE__
#define UINTTOANY_H_H_HEAD__FILE__
#pragma once


#include "../../I_Conver.h"

class UintToAny : public I_Conver {
public:
	bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const override;
};

#endif // UINTTOANY_H_H_HEAD__FILE__
