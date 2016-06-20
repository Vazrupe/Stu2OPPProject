	REDI	$a
	REDI	$b

	MOV	$lcm, $a
	MOV	$tmpb, $b

	CMP	$a, $b
	JL	@REV
	JMP	@LOOP
REV:
	MOV	$tmp, $a
	MOV	$a, $b
	MOV	$b, $tmp
LOOP:
	MOD	$c, $a, $b

	CMP	$c, 0
	JE	@END_GCD

	MOV	$a, $b
	MOV	$b, $c

	JMP	@LOOP
END_GCD:
	MOV	$gcd, $b

	DIV	$lcm, $lcm, $gcd
	MUL	$lcm, $lcm, $tmpb

	WRTI	$gcd
	WRT	32
	WRTI	$lcm
	WRT	10