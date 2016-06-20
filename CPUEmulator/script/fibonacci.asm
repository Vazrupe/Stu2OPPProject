	MOV	$a, 0
	MOV	$b, 1

	MOV	$i, 0

	REDI	$cnt

	CMP	$cnt, 1
	JL	@END
LOOP:
	ADD	$c, $a, $b
	MOV	$a, $b
	MOV	$b, $c
	
	WRTI	$b
	WRT	10

	ADD	$i, $i, 1

	CMP	$i, $cnt
	JL	@LOOP
END: