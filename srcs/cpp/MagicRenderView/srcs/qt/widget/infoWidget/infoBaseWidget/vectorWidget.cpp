#include "./vectorWidget.h"

#include <QVBoxLayout>

#include "../../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"
#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"

#include "../../../type/baseType/nullTypeObject.h"
#include "../../../type/lineType/vectorTypeObject.h"
VectorWidget::VectorWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	thisConverObject = std_shared_ptr< VectorWidget >( this, [] ( VectorWidget *ptr ) {
	} );
}
std_shared_ptr< ITypeObject > VectorWidget::atIndex( const size_t &index ) const {
	auto infoWidgets = findChildren< IInfoWidget * >( );
	qsizetype count = infoWidgets.size( );
	if( count == 0 || count <= index )
		return std_shared_ptr< ITypeObject >( new NullTypeObject );
	return infoWidgets.at( index )->getValue( );
}
void VectorWidget::setVector( const std_vector< std_shared_ptr< ITypeObject > > &vector ) {
	std_vector< QString > names;
	QStringList msg;
	QString uiMsg;
	QString nameMsg;
	size_t count = vector.size( );
	auto typeObject = vector.data( );
	for( decltype(count) index = 0; index < count; ++index )
		if( append( typeObject[ index ] ) == false ) {
			names = typeObject[ index ]->typeNames( );
			msg.clear( );
			for( auto name : names )
				msg.append( name );
			nameMsg = "{ " + msg.join( ", " ) + " }";
			names = typeObject[ index ]->getUiTypeNames( );
			msg.clear( );
			for( auto name : names )
				msg.append( name );
			uiMsg = "{ " + msg.join( ", " ) + " }";
			tools::debug::printError( "成员无法被转换到信息窗口节点 : " + nameMsg + " ," + uiMsg );
		}
}
bool VectorWidget::append( const std_shared_ptr< ITypeObject > &type_object ) {
	auto instance = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto uiTypeNames = type_object->getUiTypeNames( );
	for( auto uiName : uiTypeNames ) {
		auto infoWidget = instance->generateInfoWidget( uiName );
		if( infoWidget == nullptr )
			return false;
		mainLayout->addWidget( infoWidget );
		return true;
	}
	return false;
}
std_vector< std_shared_ptr< ITypeObject > > VectorWidget::getVector( ) const {
	std_vector< std_shared_ptr< ITypeObject > > result;
	auto infoWidgets = findChildren< IInfoWidget * >( );
	qsizetype count = infoWidgets.size( );
	if( count == 0 )
		return result;
	auto infoWidget = infoWidgets.data( );
	result.resize( count );
	auto data = result.data( );
	for( decltype(count) index = 0; index < count; ++index )
		data[ index ] = infoWidget[ index ]->getValue( );
	return result;
}
std_shared_ptr< ITypeObject > VectorWidget::getValue( ) const {
	auto vectorTypeObject = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< VectorTypeObject >( );
	vectorTypeObject->setVector( getVector( ) );
	return vectorTypeObject;
}
bool VectorWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	auto vectorTypeObject = qobject_cast< VectorTypeObject * >( value.get( ) );
	if( vectorTypeObject == nullptr )
		return false;
	std_vector< std::shared_ptr< ITypeObject > > vector = vectorTypeObject->getVector( );
	thisConverObject->setVector( vector );
	return true;
}
