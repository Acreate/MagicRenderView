﻿#include "./varDiv.h"

#include "../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarDiv, QObject::tr( "VarDiv" ), QObject::tr( "calculate" ) );

VarDiv::VarDiv( ) : NodeItem( ) {
}
bool VarDiv::intPortItems( MainWidget *parent ) {

	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被除数" );
		addInputProt< FloatInputPort >( "除数" );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );

}
