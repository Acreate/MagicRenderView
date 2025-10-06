#ifndef ISNODEITEMTYPE_H_H_HEAD__FILE__
#define ISNODEITEMTYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class NodeItem;
class IsNodeItemType : public I_IsType {
	using t_current_type = NodeItem;
public:
	IsNodeItemType( );

};

#endif // ISNODEITEMTYPE_H_H_HEAD__FILE__
