#include "application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/event/menu/itemAddMenu.h"
#include "qt/event/window/mainWindowInit.h"
#include "qt/tools/tools.h"
/// @brief 窗口消息开始序列号
constexpr t_event_type windowTypeStart = static_cast< t_event_type >( QEvent::User + 1001 );
/// @brief 菜单消息开始序列号
constexpr t_event_type menuTypeStart = static_cast< t_event_type >( QEvent::User + 1 );
/// @brief 节点消息开始序列号
constexpr t_event_type nodeTypeStart = static_cast< t_event_type >( QEvent::User + 10001 );

/// @brief 节点添加菜单序列号
constexpr t_event_type itemAddMenuType = static_cast< t_event_type >( menuTypeStart + 1 );
/// @brief 窗口初始化序列号
constexpr t_event_type mainWindowInitType = static_cast< t_event_type >( windowTypeStart + 1 );

bool Application::initEventType( ) {
	// 菜单类型 //
	ItemAddMenu::setEventType( itemAddMenuType );

	// 节点类型 //

	// 窗口类型 //
	MainWindowInit::setEventType( mainWindowInitType );

	// 其他类型 //

	return true;
}
Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
	if( initEventType( ) == false || initAddNodeMenu( ) == false )
		return;
}
bool Application::initAddNodeMenu( ) {
	return false;
}
void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

bool Application::notify( QObject *object, QEvent *event ) {
	QEvent::Type eventType = event->type( );
	if( eventType > QEvent::User /* 用户处理消息 */ ) {
		if( mainWindowInitType == eventType ) {
			auto mainWindow = qobject_cast< MainWindow * >( object );
			if( mainWindow != nullptr /* 初始化窗口位置 */ )
				tools::ui::moveDisplayCenter( mainWindow, 0 );
		} else if( itemAddMenuType == eventType ) {
			ItemAddMenu *addMenu = dynamic_cast< ItemAddMenu * >( event );
			if( addMenu == nullptr )
				tools::debug::printError( "转换错误" );
		}
		delete event;
		return true;
	}
	return QApplication::notify( object, event );
}
