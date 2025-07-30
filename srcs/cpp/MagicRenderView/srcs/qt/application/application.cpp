#include "application.h"

#include <QMouseEvent>
#include <QProcess>
#include <qboxlayout.h>

#include "qt/tools/tools.h"

#include <QSettings>
#include <qfile.h>
#include <qfileinfo.h>

#include "../stacks/funStack/IFunStack.h"
#include "../stacks/varStack/IVarStack.h"

#include "../widgets/widgets/mainWidget.h"
Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
	mainWidget = nullptr;
	QString fileName = QCoreApplication::applicationDirPath( ) + "/" + applicationDisplayName( ) + ".ini";
	settings = new QSettings( fileName, QSettings::IniFormat );
	QFileInfo fileInfo( fileName );
	if( fileInfo.exists( ) == false ) {
		auto key = "settings";
		settings->setValue( key, 0 );
		settings->sync( );
		settings->remove( key );
		if( fileInfo.exists( ) == false )
			qDebug( ) << "无法创建匹配的 ini 文件";
		else
			settings->sync( );
	}
	stdMutex.reset( new std_mutex );
	stdMutex_p.reset( new std_mutex );
}
Application::~Application( ) {
	settings->sync( );
	delete settings;
}
bool Application::appendFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	auto funStack = new_function_stack.get( );
	auto name = funStack->getName( );
	auto className = funStack->metaObject( )->className( );
	for( auto &item : funStacks )
		if( item.get( ) == funStack || item->getName( ) == name && item->metaObject( )->className( ) == className )
			return false;
	funStacks.emplace_back( new_function_stack );
	return true;
}
bool Application::removeFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	auto removeExtent = new_function_stack.get( );
	auto iterator = funStacks.begin( );
	auto end = funStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( ) == removeExtent ) {
			funStacks.erase( iterator );
			return true;
		}
	return false;
}
bool Application::removeFunctionStackAtType( const QString &function_stack_class_name, const QString &function_stack_name ) {

	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	auto iterator = funStacks.begin( );
	auto end = funStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( )->metaObject( )->className( ) == function_stack_class_name && iterator->get( )->getName( ) == function_stack_name ) {
			funStacks.erase( iterator );
			return true;
		}
	return false;

	return false;
}
bool Application::removeFunctionStackAtType( const std_shared_ptr< IFunStack > &new_function_stack ) {
	return removeFunctionStackAtType( new_function_stack->metaObject( )->className( ), new_function_stack->getName( ) );
}
std_vector< std_shared_ptr< IFunStack > > Application::removeFunctionStackAtClassName( const QString &function_stack_class_name ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;

	std::vector< std::shared_ptr< IFunStack > >::iterator iterator, end;
	while( true ) {
		iterator = funStacks.begin( );
		end = funStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->metaObject( )->className( ) == function_stack_class_name ) {
				result.emplace_back( *iterator );
				funStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IFunStack > > Application::removeFunctionStackAtStackName( const QString &function_stack_name ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;

	std::vector< std::shared_ptr< IFunStack > >::iterator iterator, end;
	while( true ) {
		iterator = funStacks.begin( );
		end = funStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->getName( ) == function_stack_name ) {
				result.emplace_back( *iterator );
				funStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IFunStack > > Application::findFunStacksAtType( const QString &fun_stack_type_name ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;
	for( auto &item : funStacks )
		if( item->metaObject( )->className( ) == fun_stack_type_name )
			result.emplace_back( item );
	return result;
}
std_vector< std_shared_ptr< IFunStack > > Application::findFunStacksAtName( const QString &fun_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;
	for( auto &item : funStacks )
		if( item->getName( ) == fun_stack_name )
			result.emplace_back( item );
	return result;
}
std_shared_ptr< IFunStack > Application::findFunStack( const QString &fun_stack_type_name, const QString &fun_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	for( auto &item : funStacks )
		if( item->metaObject( )->className( ) == fun_stack_type_name && item->getName( ) == fun_stack_name )
			return item;
	return nullptr;
}
bool Application::appendVarStacks( const std_shared_ptr< IVarStack > &new_var_stack ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	auto newStackPtr = new_var_stack.get( );
	auto newStackType = newStackPtr->metaObject( )->className( );
	auto newStackName = newStackPtr->getStackTypeName( );
	for( auto &item : varStacks )
		if( item.get( ) == newStackPtr || item->getStackTypeName( ) == newStackName && item->metaObject( )->className( ) == newStackType )
			return false;
	varStacks.emplace_back( new_var_stack );
	return true;
}
bool Application::removeVarStack( const std_shared_ptr< IVarStack > &new_var_stack ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	auto removeExtent = new_var_stack.get( );
	auto iterator = varStacks.begin( );
	auto end = varStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( ) == removeExtent ) {
			varStacks.erase( iterator );
			return true;
		}
	return false;
}
std_vector< std_shared_ptr< IVarStack > > Application::removeVarStackAtType( const QString &var_type_name ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;

	std::vector< std::shared_ptr< IVarStack > >::iterator iterator, end;
	while( true ) {
		iterator = varStacks.begin( );
		end = varStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->metaObject( )->className( ) == var_type_name ) {
				result.emplace_back( *iterator );
				varStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IVarStack > > Application::removeVarStackAtName( const QString &var_stack_name ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;

	std::vector< std::shared_ptr< IVarStack > >::iterator iterator, end;
	while( true ) {
		iterator = varStacks.begin( );
		end = varStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->getStackTypeName( ) == var_stack_name ) {
				result.emplace_back( *iterator );
				varStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IVarStack > > Application::findVarStacksAtType( const QString &var_stack_type_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->metaObject( )->className( ) == var_stack_type_name )
			result.emplace_back( item );

	return result;
}
std_vector< std_shared_ptr< IVarStack > > Application::findVarStacksAtName( const QString &var_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->getStackTypeName( ) == var_stack_name )
			result.emplace_back( item );

	return result;
}
std_shared_ptr< IVarStack > Application::findVarStack( const QString &var_stack_type_name, const QString &var_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->getStackTypeName( ) == var_stack_name && item.get( )->metaObject( )->className( ) == var_stack_type_name )
			return item;
	return nullptr;
}
void Application::setAppIniValue( const QAnyStringView &key, const QVariant &value ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	settings->setValue( key, value );
}
QVariant Application::getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	return settings->value( key, defaultValue );
}
QVariant Application::getAppIniValue( const QAnyStringView &key ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	return settings->value( key );
}
void Application::syncAppValueIniFile( ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	settings->sync( );
}

std_vector< QWidget * > Application::getLayoutWidgets( QBoxLayout *main_widget ) {
	std_vector< QWidget * > result;
	int count = main_widget->count( );
	for( int index = 0; index < count; ++count ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		result.emplace_back( widget );
	}
	return result;
}
void Application::deleteLayoutWidgets( QBoxLayout *main_widget ) {
	int count = main_widget->count( );
	for( int index = 0; index < count; ++index ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem == nullptr )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		delete widget;
	}
}
Application * Application::getApplicationInstancePtr( ) {
	return qobject_cast< Application * >( qApp );
}
void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

void Application::resetApp( ) {
	quit( );
	QProcess::startDetached( applicationFilePath( ), arguments( ) );
}
void Application::quitApp( ) {
	quit( );
}
QString Application::normalKey( const QString &key ) {

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
	return result;
}
QString Application::normalKey( const QString &key, QWidget *widget ) {
	QString result = normalKey( key );
	QString className = widget->metaObject( )->className( );
	className.append( "/" );
	if( result.endsWith( className ) == false )
		result.append( className );
	return result;
}
QString Application::normalKeyAppendWidgetName( const QString &key, QWidget *widget ) {
	auto appendStr = widget->objectName( );
	if( appendStr.isEmpty( ) )
		return normalKey( key, widget );
	return normalKeyAppendEnd( key, widget, appendStr );
}
bool Application::notify( QObject *object, QEvent *event ) {

	auto type = event->type( );
	switch( type ) {
		case QEvent::MouseMove :
			if( mainWidget == nullptr )
				break;
			mainWidget->mouseToPoint( mainWidget->mapFromGlobal( QCursor::pos( ) ) );
			break;
	}
	return QApplication::notify( object, event );
}
