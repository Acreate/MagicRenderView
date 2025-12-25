#ifndef GENERATENODEMENUSTACK_H_H_HEAD__FILE__
#define GENERATENODEMENUSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class NormalGenerateNodeMenu;
class QMenu;
class GenerateNodeMenuStack : public QObject {
	Q_OBJECT;
protected:
	using TUintyKey = std::function< NormalGenerateNodeMenu*( ) >;
	using TUintyValueTypeAliasName = std::vector< QString >;
	using TUintyValueTypeName = QString;
	using TUintyValuePair = std::pair< TUintyValueTypeName, TUintyValueTypeAliasName >;
	using TUintyPairt = std::pair< TUintyKey, TUintyValuePair >;
protected:
	std::vector< TUintyPairt > generateMenuVector;
	size_t generateCount;
	std::pair< TUintyKey, TUintyValuePair > *generateArrayPtr;
public:
	GenerateNodeMenuStack( );
	virtual bool initStack( );
	virtual NormalGenerateNodeMenu * createGenerateNodeMenu( const QString &menu_name );
};

#endif // GENERATENODEMENUSTACK_H_H_HEAD__FILE__
