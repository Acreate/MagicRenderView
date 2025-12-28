#ifndef APPDIRECTOR_H_H_HEAD__FILE__
#define APPDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class AppDirector : public QObject {
	Q_OBJECT;
public:
	virtual bool init( );
	/// @brief 清理 app 的项目信息
	/// @return 成功返回 true
	virtual bool clearAppProjectInfo( );
	/// @brief 关闭 app 的项目信息
	/// @return 成功返回 true
	virtual bool closeAppProject( );
	/// @brief app 的项目内容到以前的磁盘位置
	/// @return 成功返回 true
	virtual bool saveAppProject( );
	/// @brief app 的项目内容另存为其他磁盘位置
	/// @return 成功返回 true
	virtual bool saveAsAppProject( );
	/// @brief 更新当前 app 项目信息
	/// @return 成功返回 true
	virtual bool updateAppProject( );
	/// @brief 从当前项目的 app 项目磁盘位置重新加载当前 app 的项目内容
	/// @return 成功返回 true
	virtual bool reloadAppProject( );
	/// @brief 从磁盘加载 app 项目文件
	/// @return 成功返回 true
	virtual bool loadAppPorject( );
};

#endif // APPDIRECTOR_H_H_HEAD__FILE__
