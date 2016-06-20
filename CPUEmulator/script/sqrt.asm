	REDI	$a
	MOV	$x, $a

	CMP	$a, 25
	JL	@END
LOOP:
	CMP	$x, 0
	JE	@END

	DIV	$sub, $a, $x
	ADD	$y, $x, $sub
	DIV	$y, $y, 2

	SUB	$chk, $x, $y
	CMP	$chk, 0
	JL	@ABS
	JMP	@CHK
ABS:
	SUB	$chk, 0, $chk
CHK:	
	CMP	$chk, 1
	JLE	@END
	MOV	$x, $y

	JMP	@LOOP	

END:	WRTI	$x
	WRT	10