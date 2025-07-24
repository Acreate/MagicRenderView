#include "./widgetStatus.h"

#include "../application/application.h"
WidgetStatus::WidgetStatus( const QString &key, QWidget *widget, size_t layout ): layout( layout ), widget( widget ), key( key ) {
	application = Application::getApplicationInstancePtr( );

	std_vector< QChar > charData;

	qsizetype length = key.length( ), index = 0;
	auto data = key.data( );
	for( ; index < length; ++index )
		if( data[ index ] == '/' || data[ index ] == '\\' ) {
			charData.emplace_back( '/' );
			for( ; index < length; ++index )
				if( data[ index ] != '/' && data[ index ] != '\\' ) {
					charData.emplace_back( data[ index ] );
					break;
				}
		} else
			charData.emplace_back( data[ index ] );
	size_t count = charData.size( );

	if( charData[ count - 1 ] == "/" )
		this->key = QString( charData.data( ), count );
	else
		this->key = QString( charData.data( ), count ).append( "/" );
}
bool WidgetStatus::isShow( ) const {
	return this->widget->isHidden( ) == false;
}
void WidgetStatus::getAppIniValue( ) {
	application->sync( );
	if( application->getAppIniValue( this->key + "show", this->widget->isHidden( ) == false ).toBool( ) )
		this->widget->show( );
	else
		widget->hide( );
	this->layout = application->getAppIniValue( this->key + "layout", this->layout ).toULongLong( );
}
void WidgetStatus::setAppIniValue( ) {
	application->setAppIniValue( this->key + "show", this->widget->isHidden( ) == false );
	application->setAppIniValue( this->key + "layout", this->layout );
}
QString WidgetStatus::normalKey( const QString &key, QWidget *widget ) {
	QString result;
	std_vector< QChar > charData;

	qsizetype length = key.length( ), index = 0;
	auto data = key.data( );
	for( ; index < length; ++index )
		if( data[ index ] == '/' || data[ index ] == '\\' ) {
			charData.emplace_back( '/' );
			for( ; index < length; ++index )
				if( data[ index ] != '/' && data[ index ] != '\\' ) {
					charData.emplace_back( data[ index ] );
					break;
				}
		} else
			charData.emplace_back( data[ index ] );
	size_t count = charData.size( );

	result = staticMetaObject.className( );
	result.append( "/" );
	if( charData[ count - 1 ] == "/" )
		result.append( QString( charData.data( ), count ) );
	else
		result.append( QString( charData.data( ), count ) ).append( "/" );
	QString className = widget->metaObject( )->className( );
	className.append( "/" );
	if( result.endsWith( className ) == false )
		result.append( className );

	return result;
}
QString WidgetStatus::normalKeyAppendWidgetName( const QString &key, QWidget *widget ) {
	auto appendStr = widget->objectName( );
	if( appendStr.isEmpty( ) )
		return normalKey( key, widget );
	return normalKeyAppendEnd( key, widget, appendStr );
}
