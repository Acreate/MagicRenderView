#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>

#include <alias/type_alias.h>

class QBoxLayout;

class Application : public QApplication {
	Q_OBJECT;

public:
	/// @brief 获取布局当中所有的窗口
	/// @param main_widget 布局
	/// @return 窗口列表
	static std_vector<QWidget*> getLayoutWidgets(QBoxLayout* main_widget);
	/// @brief 删除所有布局当中的窗口
	/// @param main_widget 布局
	static void deleteLayoutWidgets(QBoxLayout* main_widget);
	
	/// @brief 获取实例指针
	/// @return 成功返回 true
	static Application* getApplicationInstancePtr();
	/// @brief 把全部窗口移动到指定显示器上
	/// @param index 显示器序列
	static void setWindowToIndexScreenCentre( size_t index );
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );

	/// @brief 重启应用
	static void resetApp();
	/// @brief 退出应用
	static void quitApp();
public:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
