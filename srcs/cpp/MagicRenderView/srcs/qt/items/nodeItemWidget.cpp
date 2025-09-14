#include "./nodeItemWidget.h"

#include <QPainter>
#include <qdir.h>
#include <qfileinfo.h>
Imp_StaticMetaInfo( NodeItemWidget, QObject::tr( "NodeItemWidget" ) )

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

}
ProtItemWidget * NodeItemWidget::getProtInputItemWidget( const QPoint &globle_point ) const {
	std_lock_grad_mutex lockMutex( *protInputItemWidgetVectorMutex );
	size_t count = nodeProtInputItems.size( );
	auto data = nodeProtInputItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->contentsRect( ).contains( data[ index ]->mapFromGlobal( globle_point ) ) )
			return data[ index ];
	return nullptr;
}
ProtItemWidget * NodeItemWidget::getProtOutputItemWidget( const QPoint &globle_point ) const {
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
	painter.fillRect( contentsRect( ), Qt::blue );
}
