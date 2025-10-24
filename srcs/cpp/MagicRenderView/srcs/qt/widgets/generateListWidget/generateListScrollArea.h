#ifndef GENERATELISTSCROLLAREA_H_H_HEAD__FILE__
#define GENERATELISTSCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class GenerateListWidget;
class GenerateListScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	GenerateListWidget *generateListWidget;
public:
	GenerateListScrollArea( QWidget *parent = nullptr );
	virtual GenerateListWidget * getGenerateListWidget( ) const { return generateListWidget; }
};

#endif // GENERATELISTSCROLLAREA_H_H_HEAD__FILE__
