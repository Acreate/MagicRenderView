#include "./combinationWidget.h"

#include <QLabel>
#include <QVBoxLayout>

#include "../../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"
#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"

#include "../../../type/blendType/combinationTypeObject.h"
CombinationWidget::CombinationWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	thisSharper = std_shared_ptr< CombinationWidget >( this, [] ( CombinationWidget * ) { } );
	value = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< CombinationTypeObject >( );
	value->setUiTypeName( title_msg );
}
bool CombinationWidget::remove( const QString &name ) {
	auto infoWidgets = findChildren< IInfoWidget * >( );
	for( auto windgetPtr : infoWidgets )
		if( windgetPtr->getTitle( ) == name ) {
			this->value->removeItem( name );
			delete windgetPtr;
			return true;
		}
	return false;
}
bool CombinationWidget::removeAll( const QString &name ) {
	bool isRemove = remove( name );
	if( isRemove == false )
		return false;
	do
		isRemove = remove( name );
	while( isRemove );
	return true;
}
bool CombinationWidget::append( const QString &name, const std_shared_ptr< ITypeObject > &value ) {
	auto element = value.get( );
	if( checkObj && checkObj( element ) == false )
		return false;

	auto baseInfoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto names = element->getUiTypeNames( );
	IInfoWidget *generateInfoWidget;
	generateInfoWidget = baseInfoWidgetStack->generateInfoWidget( name );
	if( generateInfoWidget == nullptr )
		for( auto &uiName : names ) {
			generateInfoWidget = baseInfoWidgetStack->generateInfoWidget( uiName );
			if( generateInfoWidget != nullptr )
				break;
		}
	if( generateInfoWidget == nullptr )
		return false;
	auto typeObject = this->value->getVarObject( name );
	if( typeObject != nullptr ) {
		remove( name );
	}
	this->value->setVarObject( value, name );
	mainLayout->addWidget( generateInfoWidget );
	generateInfoWidget->setValue( value );
	generateInfoWidget->setTitle( name );
	return true;
}
bool CombinationWidget::append( const std_shared_ptr< ITypeObject > &value ) {
	auto element = value.get( );
	if( checkObj && checkObj( element ) == false )
		return false;

	auto baseInfoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto names = element->getUiTypeNames( );
	for( auto &uiName : names ) {
		IInfoWidget *generateInfoWidget = baseInfoWidgetStack->generateInfoWidget( uiName );
		if( generateInfoWidget ) {
			mainLayout->addWidget( generateInfoWidget );
			generateInfoWidget->setValue( value );
			this->value->setVarObject( value, uiName );
			generateInfoWidget->setTitle( uiName );
			return true;
		}
	}
	return false;
}
std_shared_ptr< ITypeObject > CombinationWidget::atName( const QString &name ) const {
	auto var = this->value->getVarObject( name );
	return var;
}
std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > CombinationWidget::getMapValue( ) const {
	auto pairs = value->getStructInfo( );
	std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > result;
	for( auto sharedPtr : pairs )
		result.emplace_back( sharedPtr->second, sharedPtr->first );
	return result;
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
