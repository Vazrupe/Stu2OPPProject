	REDI	$a
	REDI	$n

	MOV	$i, 0
	MOV	$r, 1
LOOP:
	CMP	$i, $n
	JGE	@END

	MUL	$r, $r, $a	

	ADD	$i, $i, 1
	JMP	@LOOP

END:	WRTI	$r
	WRT	10