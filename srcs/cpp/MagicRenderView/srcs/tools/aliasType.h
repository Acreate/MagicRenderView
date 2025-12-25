#ifndef ALIASTYPE_H_H_HEAD__FILE__
#define ALIASTYPE_H_H_HEAD__FILE__
#pragma once
#include <QString>
#include <utility>

class QAction;
class Node;
class NormalGenerateNodeMenu;
using portInfo = std::pair< uint64_t, QString >;
using InputportLinkOutputPortInfoMap = std::pair< portInfo, std::vector< portInfo > >;
namespace NormalGenerateNodeMenuType {
	using TCreateNodeFunction = std::function< Node *( const QString & ) >;
	using TCreateNodeInfo = std::pair< QString, TCreateNodeFunction >;
	using TCreateUintyType = std::pair< QAction *, TCreateNodeInfo >;
}
namespace GenerateNodeMenuStackType {
	using TUintyKey = std::function< NormalGenerateNodeMenu*( ) >;
	using TUintyValueTypeAliasName = std::vector< QString >;
	using TUintyValueTypeName = QString;
	using TUintyValuePair = std::pair< TUintyValueTypeName, TUintyValueTypeAliasName >;
	using TUintyPairt = std::pair< TUintyKey, TUintyValuePair >;
}
#endif // ALIASTYPE_H_H_HEAD__FILE__
