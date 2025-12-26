#ifndef EDITORNODEMENUSTACK_H_H_HEAD__FILE__
#define EDITORNODEMENUSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <tools/aliasType.h>

class NormalNodeEditorPropertyMenu;
class EditorNodeMenuStack : public QObject {
	Q_OBJECT;
protected:
	std::vector< EditorNodeMenuStackType::TUintyPairt > editorMenuVector;
	size_t editorCount;
	EditorNodeMenuStackType::TUintyPairt *editorArrayPtr;
public:
	EditorNodeMenuStack( QObject *parent = nullptr );
	virtual NormalNodeEditorPropertyMenu * createNormalNodeEditorPropertyMenu( const QString &menu_type_name );
	virtual bool initStack( );
};

#endif // EDITORNODEMENUSTACK_H_H_HEAD__FILE__
