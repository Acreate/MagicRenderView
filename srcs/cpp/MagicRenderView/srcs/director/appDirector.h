#ifndef APPDIRECTOR_H_H_HEAD__FILE__
#define APPDIRECTOR_H_H_HEAD__FILE__

#include <QObject>
class VarDirector;
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
	QString currentProjectAbsoluteFilePathName;
	std::vector< QString > projectHistory;
protected:
	virtual bool syncProjectToFile( );
	virtual bool syncFileToProject( );
	virtual void saveThisDataToAppInstance( );
	virtual void loadThisDataToAppInstance( );
	virtual void appendProjectPath( const QString &append_project_file_path );
public:
	~AppDirector( ) override;
	virtual bool init( );
	/// @brief 获取历史文件
	/// @return 历史文件项目路径
	virtual const std::vector< QString > & getProjectHistory( ) const { return projectHistory; }
	/// @brief 获取最近文件
	/// @return 最近打开的项目文件路径
	virtual const QString & getCurrentProjectName( ) const { return currentProjectName; }
	/// @brief 清理 app 的项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool clearAppProjectInfo( QWidget *parent );
	/// @brief 关闭 app 的项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool closeAppProject( QWidget *parent );
	/// @brief app 的项目内容到以前的磁盘位置
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool saveAppProject( QWidget *parent );
	/// @brief app 的项目内容另存为其他磁盘位置
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool saveAsAppProject( QWidget *parent );
	/// @brief 更新当前 app 项目信息
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool updateAppProject( QWidget *parent );
	/// @brief 从当前项目的 app 项目磁盘位置重新加载当前 app 的项目内容
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool reloadAppProject( QWidget *parent );
	/// @brief 从磁盘加载 app 项目文件
	/// @param parent 父窗口
	/// @return 成功返回 true
	virtual bool loadAppPorject( QWidget *parent );
	/// @brief 从磁盘加载 app 项目文件
	/// @param parent 父窗口
	/// @param open_file_path 路径
	/// @return 成功返回 true
	virtual bool loadAppPorject( QWidget *parent, const QString &open_file_path );
Q_SIGNALS:
	void changeHistoryProject_Signal( AppDirector *signal_obj_ptr, const QString &open_file_path );
	void openProject_Signal( AppDirector *signal_obj_ptr, const QString &open_file_path );
	void closeProject_Signal( AppDirector *signal_obj_ptr, const QString &open_file_path );
	void reloadProject_Signal( AppDirector *signal_obj_ptr, const QString &open_file_path );
	void updateProject_Signal( AppDirector *signal_obj_ptr, const QString &open_file_path );
};

#endif // APPDIRECTOR_H_H_HEAD__FILE__
