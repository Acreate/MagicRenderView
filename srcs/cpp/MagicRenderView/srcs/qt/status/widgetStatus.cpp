#include "./widgetStatus.h"

#include "../application/application.h"
WidgetStatus::WidgetStatus( const QString &key, QWidget *widget, size_t layout, bool is_show ): layout( layout ), widget( widget ), showStatus( is_show ) {
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

	this->key = staticMetaObject.className( );
	this->key.append( "/" );
	if( charData[ count - 1 ] == "/" )
		this->key.append( QString( charData.data( ), count ) );
	else
		this->key.append( QString( charData.data( ), count ) ).append( "/" );
}
void WidgetStatus::getAppIniValue( ) {
	application->sync( );
	this->showStatus = application->getAppIniValue( this->key + "show", this->showStatus ).toBool( );
	this->layout = application->getAppIniValue( this->key + "layout", this->layout ).toULongLong( );
}
void WidgetStatus::setAppIniValue( ) {
	application->setAppIniValue( this->key + "show", this->showStatus );
	application->setAppIniValue( this->key + "layout", this->layout );
}
