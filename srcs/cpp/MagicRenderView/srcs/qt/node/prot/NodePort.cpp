#include "./NodePort.h"

#include <QPainter>

#include <qt/node/item/nodeItem.h>

#include "../../application/application.h"

#include "../../varType/I_Var.h"

#include "../../widgets/mainWidget.h"

#include "../director/nodePortLinkInfo.h"

#include "outputProt/nodeOutputPort.h"

Imp_StaticMetaInfo( NodePort, QObject::tr( "NodeOutputPort" ), QObject::tr( "outputProt" ) );
NodePort::NodePort( NodeItem *parent_item ) : QObject( parent_item ), nodePortRender( new QImage( 16, 16, QImage::Format_RGBA8888 ) ), ico( new QImage( 16, 16, QImage::Format_RGBA8888 ) ), parentItem( parent_item ) {
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( ico->load( ":/ico/info_node.png" ) == false || ico->isNull( ) )
		tools::debug::printError( "加载图标失败[" + getMetaObjectName( ) + "]" );
	icoItemHeith = ico->height( );
	icoItemWidth = ico->width( );
	varPtr = nullptr;
	typePtr = nullptr;
	nodePortRender->fill( 0 );
}
NodePort::~NodePort( ) {
	delete nodePortRender;
	delete ico;
	if( varPtr )
		delete varPtr;
}

void NodePort::setTitle( const QString &title ) {
	this->title = title;
	if( varPtr == nullptr )
		return;
	varPtr->setVarName( title );
}
void NodePort::setIco( const QString &new_ico_path ) {
	auto load = QImage( new_ico_path );
	if( load.isNull( ) )
		return;
	setIco( load );
}
bool NodePort::renderLayout( bool ico_is_end ) {
	auto font = applicationInstancePtr->getFont( );
	auto fontMetrics = QFontMetrics( font );
	QRect boundingRect = fontMetrics.boundingRect( title );
	int width = boundingRect.width( ) + boundingRect.x( );

	icoItemHeith = portItemHeith = fontMetrics.height( ) ;

	if( ico->height( ) != portItemHeith ) {
		*ico = ico->scaledToHeight( portItemHeith );
		if( ico->isNull( ) ) {
			tools::debug::printError( "适配图标失败[" + getMetaObjectName( ) + "]" );
			return false;
		}
	}

	icoItemWidth = ico->width( );
	portItemWidth = width + icoItemWidth;
	*nodePortRender = nodePortRender->scaled( portItemWidth, portItemHeith );

	nodePortRender->fill( 0 );
	QPainter painter( nodePortRender );
	painter.setFont( font );
	
	int y = icoItemHeith - fontMetrics.leading( ) - fontMetrics.descent( );
	if( ico_is_end ) {
		painter.drawImage( width, 0, *ico );
		painter.drawText( 0, y, title );
	} else {
		painter.drawImage( 0, 0, *ico );
		painter.drawText( icoItemWidth, y, title );
	}

	painter.end( );
	if( nodePortRender->isNull( ) ) {
		tools::debug::printError( "渲染标题失败[" + getMetaObjectName( ) + "]" );
		return false;
	}
	return true;
}
