#ifndef PATH_H_H_HEAD__FILE__
#define PATH_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class QFileInfo;
namespace path {
	class friendPathTree;
	class pathTree {
		friend class friendPathTree;
		QString name;
		pathTree *parentPathTree;
		std::vector< pathTree * > subPath;
	public:
		virtual ~pathTree( );
		pathTree( const QString &root_file_name );
		virtual const QString & getName( ) const { return name; }
		virtual const std::vector< pathTree * > & getSubPath( ) const { return subPath; }
		virtual void getAbsolutePath( QString &result_absolute_path );
		virtual bool appSubPath( const QString &sub_file_path );
		virtual QString toQString( const size_t index = 0, const QChar fill_char = '\t' ) const;
	};
	/// @brief 标准化路径符，使用 / 替换 \\ ，去除重复的路径符
	/// @param normal_target_path 变化的路径
	/// @return 标准化后的路径
	QString normalPathSeparatorToPath( const QString &normal_target_path );
	/// @brief 使用路径符进行分割
	/// @param normal_target_path 分割的路径
	/// @return 分割的路径
	QStringList normalPathSeparatorSplitPath( const QString &normal_target_path );
	/// @brief 创建文件
	/// @param create_file_path_name 创建的文件路径名称 
	/// @return 成功返回 true
	bool createFile( const QString &create_file_path_name );
	/// @brief 删除指定文件
	/// @param remove_file_path_name 删除的文件路径
	/// @return 成功返回 true
	bool removeFile( const QString &remove_file_path_name );
	/// @brief 创建目录
	/// @param create_file_path_name 创建的目录名称
	/// @return 成功返回 true
	bool createDir( const QString &create_file_path_name );
	/// @brief 删除指定目录
	/// @param remove_file_path_name 移除的文件目录路径
	/// @return 移除文件目录
	bool removeDir( const QString &remove_file_path_name );
	/// @brief 是否存在文件
	/// @param check_file_path_name 文件路径
	/// @return 存在返回 true
	bool hasFile( const QString &check_file_path_name );
	/// @brief 是否存在目录
	/// @param check_dir_path_name 目录路径
	/// @return 存在返回 true
	bool hasDir( const QString &check_dir_path_name );
	/// @brief 获取路径信息
	/// @param check_dir_path_name 路径
	/// @param result_file_info 返回文件信息
	/// @return 成功返回 true
	bool getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info );
};

#endif // PATH_H_H_HEAD__FILE__
