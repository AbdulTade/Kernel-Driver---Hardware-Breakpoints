
__sidt__ PROC, buff:QWORD
	mov rbx, ds:[buff];
	sidt ds:[rbx];
	mov ds:[rax], ds:[rbx];
	ret
__sidt__ ENDP
END