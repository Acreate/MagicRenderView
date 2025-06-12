#ifndef SCROLLNODEGRAPH_H_H_HEAD__FILE__
#define SCROLLNODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>

#include "qt/serialize/ISerialize.h"
class NodeGraph;
class ScrollNodeGraph : public QScrollArea, public ISerialize {
	Q_OBJECT;
protected:
	NodeGraph *nodeGraph;
public:
	ScrollNodeGraph( QWidget *parent );
	~ScrollNodeGraph( ) override;
	size_t serializeToObjectData( const std_vector<uchar> &read_data_vector ) const override;
	bool serializeToVectorData( std_vector<uchar> *result_data_vector ) const override;
};

#endif // SCROLLNODEGRAPH_H_H_HEAD__FILE__
