#ifndef NODEENUM_H_H_HEAD__FILE__
#define NODEENUM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace NodeEnum {
	enum class ErrorType {
		Param,
		Result,
		Run,
		Other
	};
	enum class AdviseType {
		Param,
		Result,
		Run,
		Other
	};
	Q_NAMESPACE;
	Q_ENUM_NS( ErrorType );
	Q_ENUM_NS( AdviseType );
};

#endif // NODEENUM_H_H_HEAD__FILE__
