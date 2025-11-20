#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>
#include <qt/node/item/nodeItem.h>

#include "../../../generate/varGenerate.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}

bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
bool NodeInputPort::setInputPortVar( const type_info &var_type_info, const void *set_new_var_ptr ) {
	if( this->varPtr == nullptr ) {
		auto call_back_function = [this] ( I_Var *create_var_ptr ) {
			this->varPtr.reset( create_var_ptr );
			return true;

		};
		if( varGenerate->createCheckTypeName( var_type_info, title, call_back_function ) == false )
			return false;
	}
	return varGenerate->conver( this->varPtr.get( ), var_type_info, set_new_var_ptr );

}
