#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>
class VarGenerate;
class PrintfInfo;
class NodeDirector;
class Application : public QApplication {
	Q_OBJECT;
protected:
	static Application *instance;
public:
	static Application * getInstancePtr( );
protected:
	NodeDirector *nodeDirector;
	PrintfInfo *printfInfo;
	VarGenerate *varGenerate;
public:
	Application( int &argc, char **const argv, const int i = ApplicationFlags );
	~Application( ) override;
	virtual bool init( );
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrintfInfo * getPrintfInfo( ) const { return printfInfo; }
	virtual VarGenerate * getVarGenerate( ) const { return varGenerate; }
};

#endif // APPLICATION_H_H_HEAD__FILE__
