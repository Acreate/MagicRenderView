#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../generate/varGenerate.h"

#include "../../../tools/tools.h"

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/mainWidget.h"

#include "../../item/nodeItem.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}
bool NodeInputPort::linkOutputPort( NodePort *output_port ) {
	if( output_port->isOutputPort( ) == false )
		return false;

	size_t count = overrideLink.size( );
	auto data = overrideLink.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == output_port )
			return true; // 已经链接

	auto var = output_port->getVar( );
	if( var == nullptr )
		return false;
	I_Type *outVar = var->getTypeInfo( ).get( );
	if( outVar == nullptr )
		return false;
	I_Var *varPtr = this->var.get( );
	if( varPtr == nullptr )
		return false;
	I_Type *typeInfo = varPtr->getTypeInfo( ).get( );
	if( typeInfo == nullptr )
		return false;
	const auto &thisTypeInfo = typeInfo->getTypeInfo( );

	if( varGenerate->supportType( thisTypeInfo, outVar->getTypeInfo( ) ) == false )
		return false;

	// 检查是否存在重复链接
	overrideLink.emplace_back( output_port );

	auto nodeItemGenerateCode = parentItem->getGenerateCode( );
	auto nodePortName = output_port->getTitle( );
	linkOutputVector.emplace_back( nodeItemGenerateCode, nodePortName );
	connect( output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
	emit linkOutputPorOver( output_port );
	return true;
}
bool NodeInputPort::disLinkOutputPor( NodePort *remove_output_port ) {
	if( remove_output_port->isOutputPort( ) == false )
		return false;
	size_t count = overrideLink.size( );
	if( count == 0 )
		return false;

	auto removeParentItem = remove_output_port->getParentItem( );
	if( removeParentItem == nullptr )
		return false;
	auto vectorPtr = linkOutputVector.data( );
	auto removeOutputPortName = remove_output_port->getTitle( );
	size_t generaterCode;
	size_t index = 0;
	count = overrideLink.size( );
	auto data = overrideLink.data( );
	for( ; index < count; ++index )
		if( data[ index ] == remove_output_port ) {
			overrideLink.erase( overrideLink.begin( ) + index );

			generaterCode = removeParentItem->getGenerateCode( );
			count = linkOutputVector.size( );
			index = 0;
			for( ; index < count; ++index )
				if( vectorPtr[ index ].second == removeOutputPortName && generaterCode == vectorPtr[ index ].first ) {
					linkOutputVector.erase( linkOutputVector.begin( ) + index );
					disconnect( remove_output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
					emit disLinkOutputPorOver( remove_output_port );
					return true;
				}
		}

	return false;
}
bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
