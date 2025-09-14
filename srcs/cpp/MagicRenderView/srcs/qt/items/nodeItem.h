#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

enum class RunCode :size_t {
	/// @brief 没有错误
	No_Error = 0,
	/// @brief 没有运行
	No_Run,
	/// @brief 重复运行
	Again_Run,
	/// @brief 执行期间发生错误
	Code_Error,
	/// @brief 内部初始化变量时候发生错误
	Var_Error,
	/// @brief 传递错误数量参数个数的错误
	Param_Count_Error,
	/// @brief 传递错误参数类型的错误
	Param_Type_Error,

	/// @brief 其他错误-未界定
	Other_Error = ( ( size_t ) 0 - ( size_t ) 1 ),
};

class NodeItem : public QObject {
	Q_OBJECT;
protected:
	/// @brief 运行代码
	RunCode runCode;
	/// @brief 需求选项
	std_list< NodeItem * > needNodeItems;
public:
	/// @brief 运行节点
	/// @return 成功返回 true
	virtual RunCode getRunCode( ) const {
		return runCode;
	}
	/// @brief 获取需求选项列表
	/// @return 需求选项
	virtual const std_list< NodeItem * > & getNeedNodeItems( ) const {
		return needNodeItems;
	}
};

#endif // NODEITEM_H_H_HEAD__FILE__
