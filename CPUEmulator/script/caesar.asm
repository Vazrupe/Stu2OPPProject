	REDI	$key
	SUB	$revkey, 0, $key
	WRTI	$revkey
	
	RED	$dummy
	WRT	10

	MOD	$key, $key, 26
	CMP	$key, 0
	JL	@REV
	JMP	@LOOP
REV:
	ADD	$key, $key, 26
	
LOOP:
	RED	$c

	CMP	$c, 10
	JE	@END

	CMP	$c, 'A'
	JL	@WRITE
	CMP	$c, 'Z'
	JLE	@UPPER

	CMP	$c, 'a'
	JL	@WRITE
	CMP	$c, 'z'
	JLE	@LOWER

	JMP	@WRITE


UPPER:
	SUB	$c, $c, 'A'
	ADD	$c, $c, $key

	CMP	$c, 26
	JGE	@U_MOD
	JMP	@U_GO

U_MOD:	SUB	$c, $c, 26
U_GO:	ADD	$c, $c, 'A'
	JMP	@WRITE

LOWER:
	SUB	$c, $c, 'a'
	ADD	$c, $c, $key

	CMP	$c, 26
	JGE	@L_MOD
	JMP	@L_GO

L_MOD:	SUB	$c, $c, 26
L_GO:	ADD	$c, $c, 'a'
	

WRITE:	WRT	$c
	JMP	@LOOP

END:	WRT	10