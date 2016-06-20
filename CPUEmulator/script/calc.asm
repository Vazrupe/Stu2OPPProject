	REDI	$a
	RED	$t
	REDI	$b

	MOV	$r, 0

	CMP	$t, '+'
	JE	@ADD
	CMP	$t, '-'
	JE	@SUB
	CMP	$t, '*'
	JE	@MUL
	CMP	$t, '/'
	JE	@DIV
	CMP	$t, '%'
	JE	@MOD
	JMP	@RESULT

ADD:	ADD	$r, $a, $b
	JMP	@RESULT

SUB:	SUB	$r, $a, $b
	JMP	@RESULT

MUL:	MUL	$r, $a, $b
	JMP	@RESULT

DIV:	DIV	$r, $a, $b
	JMP	@RESULT

MOD:	MOD	$r, $a, $b
	JMP	@RESULT

RESULT:	WRTI	$r