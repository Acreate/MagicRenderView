#include "nodeFileInfo.h"

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/nullTypeObject.h"
NodeFileInfo::NodeFileInfo( const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f ) : INodeWidget( nullptr, parent, f ) {
	auto declaration = new UserFunctionDeclaration(
		"file fileInfo(string); " );
	declaration->setCallFcuntion( [this,declaration]( ) {
		qDebug( ) << declaration->getDeclarationName( );
		emit this->finish( IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< NullTypeObject >( ), 0, __LINE__ );
	} );
	functionDeclaration.reset( declaration );
}
