#ifndef NULLTOANYTYPE_H_H_HEAD__FILE__
#define NULLTOANYTYPE_H_H_HEAD__FILE__
#pragma once

#include "../../I_Conver.h"

class NullToAnyType : public I_Conver {
public:
	bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const override;
};
#endif // NULLTOANYTYPE_H_H_HEAD__FILE__
