#include "./nodeListWidget.h"

#include <QPainter>
#include <QListWidget>
#include <qboxlayout.h>
#include <qfileinfo.h>

#include "gridWidget.h"

#include "../../stacks/varStack/IVarStack.h"
#include "../../stacks/varStack/base/baseVarStack.h"

#include "../../types/baseType/intTypeObject.h"
#include "../../types/baseType/stringTypeObject.h"
#include "../../types/blendType/combinationTypeObject.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	mainLayout = new QHBoxLayout( this );
	mainLayout->setSpacing( 0 );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	nodeTypeList = new QListWidget( this );
	nodeGeneraterList = new GridWidget( this );
	mainLayout->addWidget( nodeTypeList, 2 );
	mainLayout->addWidget( nodeGeneraterList, 8 );
	IFunctionDeclaration functionDeclaration( "FileInfo openFile(string path);", [] ( const IVarStack &var_stack, const IFunctionDeclaration &function_declaration_obj ) ->std_shared_ptr< ITypeObject > {
		auto paramInfos = function_declaration_obj.getParamInfos( );
		size_t count = paramInfos.size( );
		if( count == 0 )
			return nullptr;
		QString storageName = paramInfos[ 0 ].get( )->second;
		auto pathObject = var_stack.getStorageVar( storageName );
		if( *pathObject == nullptr )
			return nullptr;
		auto path = pathObject->toString( );
		QFileInfo fileInfo( path );
		if( fileInfo.exists( ) == false )
			return nullptr;
		auto result = var_stack.generateTVar< CombinationTypeObject >( );
		if( result == nullptr )
			return nullptr;
		auto filePath = result->append< StringTypeObject >( "filePath" );
		filePath->setString( fileInfo.absoluteFilePath( ) );
		auto bitSize = result->append< IntTypeObject >( "bitSize" );
		bitSize->setVal( fileInfo.size( ) );
		auto createTime = result->append< IntTypeObject >( "createTime" );
		createTime->setVal( fileInfo.birthTime( ).currentMSecsSinceEpoch( ) );
		auto lastChangeTime = result->append< IntTypeObject >( "lastChangeTime" );
		lastChangeTime->setVal( fileInfo.lastModified( ).currentMSecsSinceEpoch( ) );

		QString name = function_declaration_obj.getReturnValueName( );
		var_stack.setStorageVar( result, name );
		return result;
	} );
	nodeGeneraterList->addNode( functionDeclaration );
	IFunctionDeclaration::std_call call = functionDeclaration.getCallFcuntion( );
	auto instance = IVarStack::getTUBPtrInstance< BaseVarStack >( );
	auto stringTypeObject = instance->appendStorageVar< StringTypeObject >( "path" );
	stringTypeObject->setString( __FILE__ );
	call( *instance, functionDeclaration );
}
NodeListWidget::~NodeListWidget( ) {
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::blue );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
