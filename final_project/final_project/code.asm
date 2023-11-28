_printString PROTO
_getString PROTO

extrn ExitProcess : proc; defining the exit process


pair STRUCT
	key DB ?
	value DB ?
pair ENDS

.data

msg1 byte "e",0


test pair <1,2>

.code
_asmMain PROC
	

	push rbp
	sub rsp, 20h
	lea rbp, [rsp + 20h]		; align stack pointer

	lea rcx, msg1
	call _hashChar

	lea rsp, [rbp];				stack eplilogue code
	pop rbp
	ret
	xor rcx,rcx
	call ExitProcess; starting the exit process


_asmMain ENDP; ending main


_hashChar PROC;		this function takes a char and converts it to an index of an array of 8 elements
	push rbp
	push rbp;	stack frame

	xor rdx, rdx;		clearing remainder register
	mov rax, [rcx];		moving the divitend to the rax register
	mov rcx, 8;			moving the divisor to the rcx register
	div rcx;			dividing char by 8

	pop rbx;	stack frame
	pop rbp
	ret
_hashChar ENDP; ending hashing function


END; ending the program