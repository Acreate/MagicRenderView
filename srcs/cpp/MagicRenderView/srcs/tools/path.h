#ifndef PATH_H_H_HEAD__FILE__
#define PATH_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class QFileInfo;
namespace path {

	/// @brief 标准化路径符，使用 / 替换 \\ ，去除重复的路径符
	/// @param normal_target_path 变化的路径
	/// @return 标准化后的路径
	QString normalPathSeparator( const QString &normal_target_path );
	bool createFile( const QString &create_file_path_name );
	bool removeFile( const QString &remove_file_path_name );
	bool createDir( const QString &create_file_path_name );
	bool removeDir( const QString &remove_file_path_name );
	bool hasFile( const QString &check_file_path_name );
	bool hasDir( const QString &check_dir_path_name );
	bool getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info );
};

#endif // PATH_H_H_HEAD__FILE__
