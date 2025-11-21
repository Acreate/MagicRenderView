#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>
class PrintfInfo;
class NodeDirector;
class Application : public QApplication {
	Q_OBJECT;
protected:
	static Application *instance;
public:
	static Application * getInstancePtr( );
	static void setInstancePtr( Application *new_instance );
protected:
	NodeDirector *nodeDirector;
	PrintfInfo *printfInfo;
public:
	Application( int &argc, char **const argv, const int i = ApplicationFlags );
	~Application( ) override;
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrintfInfo * getPrintfInfo( ) const { return printfInfo; }
};

#endif // APPLICATION_H_H_HEAD__FILE__
