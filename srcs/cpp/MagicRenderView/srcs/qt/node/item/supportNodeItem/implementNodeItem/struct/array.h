#ifndef ARRAY_H_H_HEAD__FILE__
#define ARRAY_H_H_HEAD__FILE__
#pragma once

#include "../../processNodeItem.h"

class Array : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	Array(  );
	std_vector_pairt<NodePort*,std_vector<std_shared_ptr<I_Var>> > arrayVar;
public:
	bool intPortItems( MainWidget *parent ) override;
protected:
	bool appendVar( NodePort *app_port, const std_shared_ptr<I_Var> &append_var ) override;
};

#endif // ARRAY_H_H_HEAD__FILE__
