#include "Operation.h"

vector<string> Operation::operationList({
	"JMP", "JG", "JGE", "JL", "JLE", "JE", "JNE",
	"MOV", "CMP",
	"ADD", "SUB", "MUL", "DIV", "MOD",
	"RED", "REDI",
	"WRT", "WRTI"
});
vector<string> OneOpOperation::operationList({ "JMP", "JG", "JGE", "JL", "JLE", "JE", "JNE" });
vector<string> TwoOpOperation::operationList({ "MOV", "CMP" });
vector<string> ThreeOpOperation::operationList({ "ADD", "SUB", "MUL", "DIV", "MOD" });
vector<string> istreamOpOperation::operationList({ "RED", "REDI" });
vector<string> ostreamOpOperation::operationList({ "WRT", "WRTI" });

bool Operation::isOperation(vector<string> &operationList, const string &token) {
	string uppToken = uppercase(token);
	if (find(begin(operationList), end(operationList), uppToken) != end(operationList))
		return true;

	return false;
}
bool Operation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}

void Operation::nextRow(Register& reg) {
	reg.setReg("PC", reg.getReg("PC") + 1);
}

OneOpOperation::OneOpOperation(Operand *op) {
	this->op = op;
}
OneOpOperation::~OneOpOperation() {
	if (op) delete op;
}
bool OneOpOperation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}
OneOpOperation* OneOpOperationFactory::OneOpOperationBuild(const string &token, Operand *op) {
	string uppToken = uppercase(token);
	if (uppToken == "JMP")
		return (OneOpOperation*)(new JmpOp(op));
	if (uppToken == "JG")
		return (OneOpOperation*)(new JgOp(op));
	if (uppToken == "JGE")
		return (OneOpOperation*)(new JgeOp(op));
	if (uppToken == "JL")
		return (OneOpOperation*)(new JlOp(op));
	if (uppToken == "JLE")
		return (OneOpOperation*)(new JleOp(op));
	if (uppToken == "JE")
		return (OneOpOperation*)(new JeOp(op));
	if (uppToken == "JNE")
		return (OneOpOperation*)(new JneOp(op));

	throw new UndefineOperationException(token);
}


TwoOpOperation::TwoOpOperation(Operand *op1, Operand *op2) {
	this->op1 = op1;
	this->op2 = op2;
}
TwoOpOperation::~TwoOpOperation() {
	if (!op1) delete op1;
	if (!op2) delete op2;
}
bool TwoOpOperation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}
TwoOpOperation* TwoOpOperationFactory::TwoOpOperationBuild(const string &token, Operand *op1, Operand *op2) {
	string uppToken = uppercase(token);
	if (uppToken == "MOV")
		return (TwoOpOperation*)(new MovOp(op1, op2));
	if (uppToken == "CMP")
		return (TwoOpOperation*)(new CmpOp(op1, op2));

	throw new UndefineOperationException(token);
}

ThreeOpOperation::ThreeOpOperation(Operand *op1, Operand *op2, Operand *op3) {
	this->op1 = op1;
	this->op2 = op2;
	this->op3 = op3;
}
ThreeOpOperation::~ThreeOpOperation() {
	if (!op1) delete op1;
	if (!op2) delete op2;
	if (!op3) delete op3;
}
bool ThreeOpOperation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}
ThreeOpOperation* ThreeOpOperationFactory::ThreeOpOperationBuild(const string &token, Operand *op1, Operand *op2, Operand *op3) {
	string uppToken = uppercase(token);
	if (uppToken == "ADD")
		return (ThreeOpOperation*)(new AddOp(op1, op2, op3));
	if (uppToken == "SUB")
		return (ThreeOpOperation*)(new SubOp(op1, op2, op3));
	if (uppToken == "MUL")
		return (ThreeOpOperation*)(new MulOp(op1, op2, op3));
	if (uppToken == "DIV")
		return (ThreeOpOperation*)(new DivOp(op1, op2, op3));
	if (uppToken == "MOD")
		return (ThreeOpOperation*)(new ModOp(op1, op2, op3));

	throw new UndefineOperationException(token);
}

istreamOpOperation::istreamOpOperation(Operand *op, istream *stm) {
	this->op = op;
	this->stm = stm;
}
istreamOpOperation::~istreamOpOperation() {
	if (!op) delete op;
}
bool istreamOpOperation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}
istreamOpOperation* istreamOpOperationFactory::istreamOpOperationBuild(const string &token, Operand *op, istream *stm) {
	string uppToken = uppercase(token);
	if (uppToken == "RED")
		return (istreamOpOperation*)(new RedOp(op, stm));
	if (uppToken == "REDI")
		return (istreamOpOperation*)(new RediOp(op, stm));

	throw new UndefineOperationException(token);
}

ostreamOpOperation::ostreamOpOperation(Operand *op, ostream *stm) {
	this->op = op;
	this->stm = stm;
}
ostreamOpOperation::~ostreamOpOperation() {
	if (op) delete op;
}
bool ostreamOpOperation::isOperation(const string &token) {
	return Operation::isOperation(operationList, token);
}
ostreamOpOperation* ostreamOpOperationFactory::ostreamOpOperationBuild(const string &token, Operand *op, ostream *stm) {
	string uppToken = uppercase(token);
	if (uppToken == "WRT")
		return (ostreamOpOperation*)(new WrtOp(op, stm));
	if (uppToken == "WRTI")
		return (ostreamOpOperation*)(new WrtiOp(op, stm));

	throw new UndefineOperationException(token);
}

// 이동
void MovOp::run(Register& reg) {
	op1->setValue(reg, op2->getValue(reg));

	nextRow(reg);
}

// 덧셈
void AddOp::run(Register& reg) {
	op1->setValue(reg, op2->getValue(reg) + op3->getValue(reg));

	nextRow(reg);
}

// 뺄셈
void SubOp::run(Register& reg) {
	op1->setValue(reg, op2->getValue(reg) - op3->getValue(reg));

	nextRow(reg);
}

// 곱셈
void MulOp::run(Register& reg) {
	op1->setValue(reg, op2->getValue(reg) * op3->getValue(reg));

	nextRow(reg);
}

// 나눗셈
void DivOp::run(Register& reg) {
	int dem = op3->getValue(reg);

	if (dem == 0) throw new ZeroDivisionException();
	op1->setValue(reg, op2->getValue(reg) / op3->getValue(reg));

	nextRow(reg);
}

// 나머지
void ModOp::run(Register& reg) {
	op1->setValue(reg, op2->getValue(reg) % op3->getValue(reg));

	nextRow(reg);
}

// 비교
void CmpOp::run(Register& reg) {
	int a = op1->getValue(reg);
	int b = op2->getValue(reg);

	reg.setReg("UNDER", a < b);
	reg.setReg("EQUAL", a == b);
	reg.setReg("OVER", a > b);

	nextRow(reg);
}

// 점프
void JmpOp::run(Register& reg) {
	reg.setReg("PC", op->getValue(reg));
	nextRow(reg);
}

// A > B 점프
void JgOp::run(Register& reg) {
	if (reg.getReg("OVER"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// A >= B 점프
void JgeOp::run(Register& reg) {
	if (reg.getReg("OVER") || reg.getReg("EQUAL"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// A < B 점프
void JlOp::run(Register& reg) {
	if (reg.getReg("UNDER"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// A <= B 점프
void JleOp::run(Register& reg) {
	if (reg.getReg("UNDER") || reg.getReg("EQUAL"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// A == B 점프
void JeOp::run(Register& reg) {
	if (reg.getReg("EQUAL"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// A != B 점프
void JneOp::run(Register& reg) {
	if (reg.getReg("EQUAL"))
		reg.setReg("PC", op->getValue(reg));

	nextRow(reg);
}

// 1 문자 읽기
void RedOp::run(Register& reg) {
	op->setValue(reg, stm->get());
	
	nextRow(reg);
}

// 1 문자 쓰기
void WrtOp::run(Register& reg) {
	(*stm) << (char)op->getValue(reg);

	nextRow(reg);
}

// 정수 읽기
void RediOp::run(Register& reg) {
	int i;
	(*stm) >> i;
	op->setValue(reg, i);

	nextRow(reg);
}

// 정수 쓰기
void WrtiOp::run(Register& reg) {
	int t = op->getValue(reg);
	(*stm) << op->getValue(reg);

	nextRow(reg);
}