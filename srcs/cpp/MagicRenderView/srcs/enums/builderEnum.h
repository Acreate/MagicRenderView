#ifndef BUILDERENUM_H_H_HEAD__FILE__
#define BUILDERENUM_H_H_HEAD__FILE__
#include <qobject.h>

namespace BuilderEnum {

	/// @brief 编译错误
	enum class BuilderErrorType {
		None,
		BuilderSortError,
		NodeBuilderError,
		NodeBuilderSortError,
		MissingRefInput,
		MissingRefOutput
	};

	/// @brief 编译警告类型
	enum class BuilderWarningType {
		Param,
		Result,
		Run,
		Other
	};
	Q_NAMESPACE;
	Q_ENUM_NS( BuilderErrorType );
	Q_ENUM_NS( BuilderWarningType );
}

#endif // BUILDERENUM_H_H_HEAD__FILE__
