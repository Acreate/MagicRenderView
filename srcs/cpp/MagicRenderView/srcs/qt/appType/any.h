#ifndef ANY_H_H_HEAD__FILE__
#define ANY_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class I_Var;
class Any : public QObject {
	Q_OBJECT;
	I_Var* var;
public:
	Any( );
	virtual I_Var * getVar( ) const { return var; }
	virtual void setVar( I_Var *var ) { this->var = var; }
};

#endif // ANY_H_H_HEAD__FILE__
