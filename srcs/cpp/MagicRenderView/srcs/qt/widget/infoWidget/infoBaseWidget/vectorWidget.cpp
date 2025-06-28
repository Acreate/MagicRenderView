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
	value = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< VectorTypeObject >( );
	value->setUiTypeName( title_msg );
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
	if( checkObj && checkObj( type_object.get( ) ) == false )
		return false;
	auto instance = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto uiTypeNames = type_object->getUiTypeNames( );
	for( auto uiName : uiTypeNames ) {
		auto infoWidget = instance->generateInfoWidget( uiName );
		if( infoWidget == nullptr )
			return false;
		infoWidget->setValue( type_object );
		mainLayout->addWidget( infoWidget );
		return true;
	}
	return false;
}
std_vector< std_shared_ptr< ITypeObject > > VectorWidget::getVector( ) const {
	auto infoWidgets = findChildren< IInfoWidget * >( );
	qsizetype count = infoWidgets.size( );
	if( count == 0 )
		return value.get( )->getVector( );
	auto infoWidget = infoWidgets.data( );
	value->resize( count );
	auto data = value->data( );
	for( decltype(count) index = 0; index < count; ++index )
		data[ index ] = infoWidget[ index ]->getValue( );
	return value.get( )->getVector( );
}
std_shared_ptr< ITypeObject > VectorWidget::getValue( ) const {
	value->setVector( getVector( ) );
	return value;
}
bool VectorWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	if( checkObj && checkObj( value.get( ) ) == false )
		return false;
	auto instance = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto vectorTypeObject = qobject_cast< VectorTypeObject * >( value.get( ) );
	if( vectorTypeObject != nullptr ) {
		std_vector< std_pairt< std_shared_ptr< ITypeObject >, IInfoWidget * > > appendElement;
		size_t count = vectorTypeObject->size( );
		auto dataPtr = vectorTypeObject->data( );
		size_t index = 0;
		for( ; index < count; ++index ) {
			auto typeObject = dataPtr[ index ];
			IInfoWidget *infoWidget = instance->generateInfoWidget( typeObject );
			if( infoWidget == nullptr )
				continue;;
			infoWidget->setValue( typeObject );
			appendElement.emplace_back( typeObject, infoWidget );
		}
		count = appendElement.size( );
		if( count == 0 )
			return false;
		auto infoWidgets = findChildren< IInfoWidget * >( );
		for( auto widget : infoWidgets )
			delete widget;
		auto pair = appendElement.data( );
		index = 0;
		this->value->resize( count );
		auto object = this->value->data( );

		for( ; index < count; ++index ) {
			object[ index ] = pair[ index ].first;
			mainLayout->addWidget( pair[ index ].second );
		}
	} else {
		auto infoWidget = instance->generateInfoWidget( value );
		if( infoWidget == nullptr )
			return false;
		auto infoWidgets = findChildren< IInfoWidget * >( );
		for( auto widget : infoWidgets )
			delete widget;
		mainLayout->addWidget( infoWidget );
		infoWidget->setValue( value );
		this->value->clear( );
		this->value->append( value );
	}
	synValue( );
	emit valueChanged( );
	return true;
}
