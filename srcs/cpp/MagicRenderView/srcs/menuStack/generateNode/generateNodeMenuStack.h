#ifndef GENERATENODEMENUSTACK_H_H_HEAD__FILE__
#define GENERATENODEMENUSTACK_H_H_HEAD__FILE__

#include <QObject>

#include "../../tools/aliasType.h"

class NormalGenerateNodeMenu;
class QMenu;
class GenerateNodeMenuStack : public QObject {
	Q_OBJECT;
protected:
	std::vector< GenerateNodeMenuStackType::TUintyPairt > generateMenuVector;
	size_t generateCount;
	GenerateNodeMenuStackType::TUintyPairt *generateArrayPtr;
public:
	GenerateNodeMenuStack( );
	virtual bool initStack( );
	virtual NormalGenerateNodeMenu * createGenerateNodeMenu( const QString &menu_name );
};

#endif // GENERATENODEMENUSTACK_H_H_HEAD__FILE__
