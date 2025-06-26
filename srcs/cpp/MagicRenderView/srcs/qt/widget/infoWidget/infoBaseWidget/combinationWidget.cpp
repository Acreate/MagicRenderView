#include "./combinationWidget.h"

#include <QLabel>

#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"

#include "../../../type/blendType/combinationTypeObject.h"
CombinationWidget::CombinationWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	thisSharper = std_shared_ptr< CombinationWidget >( this, [] ( CombinationWidget * ) { } );
	value = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< CombinationTypeObject >( );
	value->setUiTypeName( title_msg );
}
bool CombinationWidget::remove( const QString &name ) {
	return false;
}
bool CombinationWidget::append( const QString &name, const std_shared_ptr< ITypeObject > &value ) {
	auto element = value.get( );
	if( checkObj && checkObj( element ) == false )
		return false;
	return false;
}
std_shared_ptr< ITypeObject > CombinationWidget::atName( const QString &name ) const {
	return { };
}
std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > CombinationWidget::getMapValue( ) const {
	return { };
}
void CombinationWidget::setMapValue( const std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > &value_std_vector ) const {
	for( auto element : value_std_vector )
		if( element.second != nullptr )
			thisSharper->append( element.first, element.second );
}
void CombinationWidget::setMapValue( const std_shared_ptr< CombinationTypeObject > &value_std_vector ) const {
	setMapValue( value_std_vector.get( ) );
}
void CombinationWidget::setMapValue( const CombinationTypeObject *value_std_vector ) const {
	auto sharedPtrs = value_std_vector->getStructInfo( );
	for( auto sharedPtr : sharedPtrs ) {
		auto element = sharedPtr.get( );
		if( element->first == nullptr )
			continue;
		thisSharper->append( element->second, element->first );
	}
}
std_shared_ptr< ITypeObject > CombinationWidget::getValue( ) const {
	value->clear( );
	auto infoWidgets = findChildren< IInfoWidget * >( );
	for( auto infoWidget : infoWidgets ) {
		auto stdShared = infoWidget->getValue( );
		auto title = infoWidget->getTitle( );
		value->setVarObject( stdShared, title );
	}
	value->appendUiTypeName( this->title->text( ) );
	return value;
}
bool CombinationWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	auto element = value.get( );
	if( checkObj && checkObj( element ) == false )
		return false;
	auto combinationTypeObject = qobject_cast< CombinationTypeObject * >( element );
	if( combinationTypeObject ) {
		setMapValue( combinationTypeObject );
		return true;
	}
	return true;
}
