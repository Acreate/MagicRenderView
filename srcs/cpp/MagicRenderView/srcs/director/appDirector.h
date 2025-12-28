#ifndef APPDIRECTOR_H_H_HEAD__FILE__
#define APPDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>
class Application;
class PrinterDirector;
class NodeDirector;
class AppDirector : public QObject {
	Q_OBJECT;
protected:
	Application *application;
	PrinterDirector *printerDirector;
	NodeDirector *nodeDirector;
protected:
	QString currentProjectWorkPath;
	QString currentProjectName;
protected:
	virtual bool syncProjectToFile();
	virtual bool syncFileToProject();
public:
	virtual bool init( );
	/// @brief 清理 app 的项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool clearAppProjectInfo( QWidget* parent );
	/// @brief 关闭 app 的项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool closeAppProject(  QWidget* parent);
	/// @brief app 的项目内容到以前的磁盘位置
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool saveAppProject(  QWidget* parent);
	/// @brief app 的项目内容另存为其他磁盘位置
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool saveAsAppProject( QWidget* parent );
	/// @brief 更新当前 app 项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool updateAppProject(  QWidget* parent);
	/// @brief 从当前项目的 app 项目磁盘位置重新加载当前 app 的项目内容
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool reloadAppProject( QWidget* parent );
	/// @brief 从磁盘加载 app 项目文件
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool loadAppPorject(  QWidget* parent);
};

#endif // APPDIRECTOR_H_H_HEAD__FILE__
