#include "./nodeItemWidget.h"

#include <QPainter>
#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>
#include <qgridlayout.h>

#include "protInputItemWidget.h"
#include "protOutputItemWidget.h"

Imp_StaticMetaInfo( NodeItemWidget, QObject::tr( "NodeItemWidget" ), QObject::tr( "items" ) )

std_vector< NodeItemWidget::generateItem > NodeItemWidget::generateItemVector;
std_mutex NodeItemWidget::generateItemVectorMutex;

bool NodeItemWidget::appendGenerate( const QString &dir_name, const QString &node_name, const generateFunction &generate_function ) {
	if( generate_function == nullptr )
		return false;
	QString dirName = dir_name.trimmed( );
	if( dirName.isEmpty( ) )
		return false;
	QString nodeName = node_name.trimmed( );
	if( nodeName.isEmpty( ) )
		return false;

	std_lock_grad_mutex lockGradMutex( generateItemVectorMutex );

	size_t count = generateItemVector.size( ), index = 0;
	auto data = generateItemVector.data( );
	for( ; index < count; ++index )
		if( data[ index ].first == dirName ) {
			auto &nodeNamevVector = data[ index ].second;
			size_t size = nodeNamevVector.size( );
			auto nameData = nodeNamevVector.data( );
			size_t subIndex = 0;
			for( ; subIndex < size; ++subIndex )
				if( nameData[ subIndex ].first == nodeName ) {
					nameData[ subIndex ].second = generate_function;
					return true;
				}
			nodeNamevVector.emplace_back( nodeName, generate_function );
			return true;
		}
	NodeItemWidget::generateInfo itemInfo( nodeName, generate_function );
	NodeItemWidget::generateInfoVector itemInfoVector( 1 );
	itemInfoVector.data( )[ 0 ] = itemInfo;
	NodeItemWidget::generateItem generateItem( dirName, itemInfoVector );
	generateItemVector.emplace_back( generateItem );
	return true;
}
NodeItemWidget * NodeItemWidget::generateNode( QWidget *parent, const QString &dir_name, const QString &node_name ) {
	QString dirName = dir_name.trimmed( );
	if( dirName.isEmpty( ) )
		return nullptr;
	QString nodeName = node_name.trimmed( );
	if( nodeName.isEmpty( ) )
		return nullptr;

	std_lock_grad_mutex lockGradMutex( generateItemVectorMutex );

	size_t count = generateItemVector.size( ), index = 0;
	auto data = generateItemVector.data( );
	for( ; index < count; ++index )
		if( data[ index ].first == dirName ) {
			auto &nodeNamevVector = data[ index ].second;
			size_t size = nodeNamevVector.size( );
			auto nameData = nodeNamevVector.data( );
			size_t subIndex = 0;
			for( ; subIndex < size; ++subIndex )
				if( nameData[ subIndex ].first == nodeName )
					if( nameData[ subIndex ].second != nullptr )
						return nameData[ subIndex ].second( parent );
					else
						break;
			break;
		}
	return nullptr;
}
std_vector< NodeItemWidget::generatePathClassInfo > NodeItemWidget::getGenerateItems( ) {
	std_lock_grad_mutex lockGradMutex( generateItemVectorMutex );
	size_t count = generateItemVector.size( );
	size_t resultCount;
	size_t resultIndex;
	size_t infoPairVectorPtrCount;
	size_t infoPairVectorPtrIndex;
	size_t index = 0;
	std_vector< generatePathClassInfo > result;
	std_pairt< QString, std::vector< QString > > *resultDataPtr;
	generateInfo *infoPairVectorPtr;
	auto data = generateItemVector.data( );
	for( ; index < count; ++index ) {
		auto &infoPairVector = data[ index ].second;
		infoPairVectorPtr = infoPairVector.data( );
		infoPairVectorPtrCount = infoPairVector.size( );
		infoPairVectorPtrIndex = 0;
		for( ; infoPairVectorPtrIndex < infoPairVectorPtrCount; ++infoPairVectorPtrIndex ) {
			resultIndex = 0;
			resultCount = result.size( );
			resultDataPtr = result.data( );
			for( ; resultIndex < resultCount; ++resultIndex )
				if( resultDataPtr[ resultIndex ].first == data[ index ].first ) {
					resultDataPtr[ resultIndex ].second.emplace_back( infoPairVectorPtr[ infoPairVectorPtrIndex ].first );
					break;
				}
			if( resultIndex < resultCount )
				continue;
			std_vector< QString > names;
			names.emplace_back( infoPairVectorPtr[ infoPairVectorPtrIndex ].first );
			result.emplace_back( data[ index ].first, names );
		}
	}
	return result;
}
NodeItemWidget::NodeItemWidget( QWidget *parent ) : QWidget( parent ), protInputItemWidgetVectorMutex( new std_mutex ), protOutputItemWidgetVectorMutex( new std_mutex ) {

	titile = new QLabel( this );
	titile->setText( getStaticMetaObjectName( ) );
	leftStartSpace = rightEndSpace = topSpace = boomSpace = 5;
	midSpace = 10;
	titile->move( 0, topSpace );
}
void NodeItemWidget::setNodeTitle( const QString &new_titile ) {
	titile->setText( new_titile );
}
bool NodeItemWidget::appendProtInputItemWidget( ProtInputItemWidget *prot_input_item_widget ) {
	std_lock_grad_mutex lockMutex( *protInputItemWidgetVectorMutex );
	nodeProtInputItems.emplace_back( prot_input_item_widget );
	prot_input_item_widget->setParent( this );
	prot_input_item_widget->show( );

	return true;
}
bool NodeItemWidget::appendProtOutputItemWidget( ProtOutputItemWidget *prot_output_item_widget ) {
	std_lock_grad_mutex lockMutex( *protOutputItemWidgetVectorMutex );
	nodeProtOutputItems.emplace_back( prot_output_item_widget );
	prot_output_item_widget->setParent( this );
	prot_output_item_widget->show( );
	return true;
}
bool NodeItemWidget::removeProtInputItemWidget( const ProtInputItemWidget *prot_input_item_widget ) {
	std_lock_grad_mutex lockMutex( *protInputItemWidgetVectorMutex );
	size_t count = nodeProtInputItems.size( );
	auto data = nodeProtInputItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == prot_input_item_widget ) {
			delete data[ index ];
			nodeProtInputItems.erase( nodeProtInputItems.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItemWidget::removeProtOutputItemWidget( const ProtOutputItemWidget *prot_output_item_widget ) {
	std_lock_grad_mutex lockMutex( *protOutputItemWidgetVectorMutex );
	size_t count = nodeProtOutputItems.size( );
	auto data = nodeProtOutputItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == prot_output_item_widget ) {
			delete data[ index ];
			nodeProtOutputItems.erase( nodeProtOutputItems.begin( ) + index );
			return true;
		}
	return false;
}
QSize NodeItemWidget::applyAdviseSizeToNodeItemWidget( ) {

	auto protInputItemWidgetDataPtr = nodeProtInputItems.data( );
	int inputHeight = titile->height( ) + topSpace;
	int inputWidth = 0;
	size_t count = nodeProtInputItems.size( );
	size_t index = 0;
	int width;

	for( ; index < count; ++index ) {
		inputHeight += topSpace;
		protInputItemWidgetDataPtr[ index ]->move( leftStartSpace, inputHeight );
		inputHeight += protInputItemWidgetDataPtr[ index ]->height( );
		width = protInputItemWidgetDataPtr[ index ]->width( );
		if( inputWidth < width )
			inputWidth = width;
	}

	auto protOutputItemWidgetDataPtr = nodeProtOutputItems.data( );
	int outputHeight = titile->height( ) + topSpace;
	int outputWidth = 0;
	count = nodeProtOutputItems.size( );
	index = 0;

	int maxWidth = inputWidth + midSpace + leftStartSpace;
	for( ; index < count; ++index ) {
		outputHeight += topSpace;
		protOutputItemWidgetDataPtr[ index ]->move( maxWidth, outputHeight );
		outputHeight += protOutputItemWidgetDataPtr[ index ]->height( );
		width = protOutputItemWidgetDataPtr[ index ]->width( );
		if( outputWidth < width )
			outputWidth = width;
	}
	int maxHeight = outputHeight > inputHeight ? outputHeight : inputHeight;
	maxWidth += outputWidth + rightEndSpace;
	if( outputWidth == 0 )
		maxWidth -= midSpace;
	width = titile->width( ) + leftStartSpace + rightEndSpace;
	maxWidth = maxWidth > width ? maxWidth : width;
	maxHeight += boomSpace;
	QSize result( maxWidth, maxHeight );
	setFixedSize( result );
	width = maxWidth - width;
	width = width == 0 ? 0 : width / 2;
	titile->move( width, topSpace );
	return result;
}
NodeItemWidget::~NodeItemWidget( ) {
}
ProtInputItemWidget * NodeItemWidget::getProtInputItemWidget( const QPoint &globle_point ) const {
	std_lock_grad_mutex lockMutex( *protInputItemWidgetVectorMutex );
	size_t count = nodeProtInputItems.size( );
	auto data = nodeProtInputItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->contentsRect( ).contains( data[ index ]->mapFromGlobal( globle_point ) ) )
			return data[ index ];
	return nullptr;
}
ProtOutputItemWidget * NodeItemWidget::getProtOutputItemWidget( const QPoint &globle_point ) const {
	std_lock_grad_mutex lockMutex( *protOutputItemWidgetVectorMutex );
	size_t count = nodeProtOutputItems.size( );
	auto data = nodeProtOutputItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->contentsRect( ).contains( data[ index ]->mapFromGlobal( globle_point ) ) )
			return data[ index ];
	return nullptr;
}
void NodeItemWidget::paintEvent( QPaintEvent *event ) {
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::white );
}
