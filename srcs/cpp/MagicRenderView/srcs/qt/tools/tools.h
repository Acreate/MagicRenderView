#ifndef TOOLS_H_H_HEAD__FILE__
#define TOOLS_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>

#include "alias/type_alias.h"

namespace tools {
	namespace ui {
		/// @brief 窗口移动到指定显示器当中
		/// @param move_target 移动的窗口
		/// @param display_target 移动的目标显示器
		/// @return 返回 0 表示成功
		int moveDisplayCenter( QWidget *move_target, size_t display_target );
		/// @brief 窗口移动到指定显示器当中
		/// @param move_target 移动的窗口
		/// @param display_target 移动的目标显示器
		/// @return 返回 0 表示成功
		int moveDisplayCenter( QWindow *move_target, size_t display_target );
	}
	namespace debug {
		/// @brief 获取层级调用信息
		/// @param leven 层级
		/// @return 返回指定层级上的所有层级与行号
		std_vector< std_pairt< QString, size_t > > getFunctionName(size_t leven);
		/// @brief 输出错误信息
		/// @param msg 信息
		/// @param start_index 堆栈-0 为本函数调用
		/// @param last_remove_count 末尾移除个数
		void printError( const std::wstring &msg, size_t start_index, size_t last_remove_count );
		/// @brief 输出错误信息
		/// @param msg 信息
		inline void printError( const std::wstring &msg ) {
			printError( msg, 2, 1 );
		}
		/// @brief 输出错误信息
		/// @param msg 信息
		inline void printError( const QString &msg ) {
			printError( msg.toStdWString( ), 2, 1 );
		}
	}

}

#endif // TOOLS_H_H_HEAD__FILE__
