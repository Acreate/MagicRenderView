#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>
class Application : public QApplication {
	Q_OBJECT;
public:
	/// @brief 把全部窗口移动到指定显示器上
	/// @param index 显示器序列
	static void setWindowToIndexScreenCentre( size_t index );
	/// @brief 初始化事件
	static bool initEventType( );
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	/// @brief 初始化添加节点的菜单
	/// @return 成功返回 true
	bool initAddNodeMenu();
public:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
