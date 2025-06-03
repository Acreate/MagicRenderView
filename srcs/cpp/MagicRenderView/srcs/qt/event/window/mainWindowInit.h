#ifndef MAINWINDOWINIT_H_H_HEAD__FILE__
#define MAINWINDOWINIT_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>
#include <qwidget.h>
class MainWindowInit : public QEvent {

	/// @brief 事件类型
	static t_event_type Event_Type;
public:
	
	/// @brief 设置事件编号
	/// @param new_event_type 
	static void setEventType( t_event_type new_event_type ) {
		if( new_event_type > QEvent::User )
			Event_Type = new_event_type;
		else
			Event_Type = QEvent::User;
	}
	/// @brief 获取事件类型
	/// @return 事件类型
	static t_event_type getEventType( ) {
		return Event_Type;
	}
private:
	/// @brief 菜单窗口
	QWidget *eventWidget;
public:
	MainWindowInit( QWidget *event_widget )
		: QEvent( Event_Type ),
		eventWidget( event_widget ) { }
	
};

#endif // MAINWINDOWINIT_H_H_HEAD__FILE__
