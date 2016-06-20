#pragma once
#include "Operand.h"
#include "Register.h"
#include "Util.h"
#include <vector>
#include <string>
using namespace std;

class Operation {
	static vector<string> operationList;
protected:
	static bool isOperation(vector<string> &operationList, const string &token);
public:
	void nextRow(Register& reg);
	virtual void run(Register& reg) = 0;
	static bool isOperation(const string &token);
};

class OneOpOperation : public Operation {
	static vector<string> operationList;
protected:
	Operand *op;
public:
	OneOpOperation(Operand *op);
	~OneOpOperation();
	virtual void run(Register& reg) {}
	static bool isOperation(const string &token);
};

class TwoOpOperation : public Operation {
	static vector<string> operationList;
protected:
	Operand *op1, *op2;
public:
	TwoOpOperation(Operand *op1, Operand *op2);
	~TwoOpOperation();
	virtual void run(Register& reg) {}
	static bool isOperation(const string &token);
};

class ThreeOpOperation : public Operation {
	static vector<string> operationList;
protected:
	Operand *op1, *op2, *op3;
public:
	ThreeOpOperation(Operand *op1, Operand *op2, Operand *op3);
	~ThreeOpOperation();
	virtual void run(Register& reg) {}
	static bool isOperation(const string &token);
};

class istreamOpOperation : public Operation {
	static vector<string> operationList;
protected:
	Operand *op;
	istream *stm;
public:
	istreamOpOperation(Operand *op, istream *stm);
	~istreamOpOperation();
	virtual void run(Register& reg) {}
	static bool isOperation(const string &token);
};

class ostreamOpOperation : public Operation {
	static vector<string> operationList;
protected:
	Operand *op;
	ostream *stm;
public:
	ostreamOpOperation(Operand *op, ostream *stm);
	~ostreamOpOperation();
	virtual void run(Register& reg) {}
	static bool isOperation(const string &token);
};

class MovOp : public TwoOpOperation {
public:
	MovOp(Operand *dst, Operand *src) : TwoOpOperation(dst, src) { }
	void run(Register& reg);
};

class AddOp : public ThreeOpOperation {
public:
	AddOp(Operand *dst, Operand *src1, Operand *src2) : ThreeOpOperation(dst, src1, src2) {}
	void run(Register& reg);
};

class SubOp : public ThreeOpOperation {
	Operand dst, src1, src2;
public:
	SubOp(Operand *dst, Operand *src1, Operand *src2) : ThreeOpOperation(dst, src1, src2) {}
	void run(Register& reg);
};

class MulOp : public ThreeOpOperation {
	Operand dst, src1, src2;
public:
	MulOp(Operand *dst, Operand *src1, Operand *src2) : ThreeOpOperation(dst, src1, src2) {}
	void run(Register& reg);
};

class DivOp : public ThreeOpOperation {
public:
	DivOp(Operand *dst, Operand *src1, Operand *src2) : ThreeOpOperation(dst, src1, src2) {}
	void run(Register& reg);
};

class ModOp : public ThreeOpOperation {
public:
	ModOp(Operand *dst, Operand *src1, Operand *src2) : ThreeOpOperation(dst, src1, src2) {}
	void run(Register& reg);
};

class CmpOp : public TwoOpOperation {
	Operand src1, src2;
public:
	CmpOp(Operand *src1, Operand *src2) : TwoOpOperation(src1, src2) { }
	void run(Register& reg);
};

class JmpOp : public OneOpOperation {
public:
	JmpOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JgOp : public OneOpOperation {
public:
	JgOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JgeOp : public OneOpOperation {
public:
	JgeOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JlOp : public OneOpOperation {
public:
	JlOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JleOp : public OneOpOperation {
public:
	JleOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JeOp : public OneOpOperation {
public:
	JeOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class JneOp : public OneOpOperation {
public:
	JneOp(Operand *trg) : OneOpOperation(trg) {}
	void run(Register& reg);
};

class RedOp : public istreamOpOperation {
public:
	RedOp(Operand *buf, istream *stm) : istreamOpOperation(buf, stm) { }
	void run(Register& reg);
};

class WrtOp : public ostreamOpOperation {
public:
	WrtOp(Operand *buf, ostream *stm) : ostreamOpOperation(buf, stm) { }
	void run(Register& reg);
};

class RediOp : public istreamOpOperation {
public:
	RediOp(Operand *buf, istream *stm) : istreamOpOperation(buf, stm) { }
	void run(Register& reg);
};

class WrtiOp : public ostreamOpOperation {
public:
	WrtiOp(Operand *buf, ostream *stm) : ostreamOpOperation(buf, stm) { }
	void run(Register& reg);
};

class OperationFactory {
public:
	virtual OneOpOperation* OneOpOperationBuild(const string &token, Operand *op) { return new OneOpOperation(op); }
	virtual TwoOpOperation* TwoOpOperationBuild(const string &token, Operand *op1, Operand *op2) { return new TwoOpOperation(op1, op2); }
	virtual ThreeOpOperation* ThreeOpOperationBuild(const string &token, Operand *op1, Operand *op2, Operand *op3) { return new ThreeOpOperation(op1, op2, op3); }
	virtual istreamOpOperation* istreamOpOperationBuild(const string &token, Operand *op, istream *stm) { return new istreamOpOperation(op, stm); }
	virtual ostreamOpOperation* ostreamOpOperationBuild(const string &token, Operand *op, ostream *stm) { return new ostreamOpOperation(op, stm); }
};
class OneOpOperationFactory : public OperationFactory {
public:
	OneOpOperation* OneOpOperationBuild(const string &token, Operand *op);
};
class TwoOpOperationFactory : public OperationFactory {
public:
	TwoOpOperation* TwoOpOperationBuild(const string &token, Operand *op1, Operand *op2);
};
class ThreeOpOperationFactory : public OperationFactory {
public:
	ThreeOpOperation* ThreeOpOperationBuild(const string &token, Operand *op1, Operand *op2, Operand *op3);
};
class istreamOpOperationFactory : public OperationFactory {
public:
	istreamOpOperation* istreamOpOperationBuild(const string &token, Operand *op, istream *stm);
};
class ostreamOpOperationFactory : public OperationFactory {
public:
	ostreamOpOperation* ostreamOpOperationBuild(const string &token, Operand *op, ostream *stm);
};