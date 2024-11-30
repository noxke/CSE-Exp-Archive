mov ecx,slength
xor eax,eax
xor edi,edi
xor esi,esi
  again2:
      mov dl,string[esi]
      cmp dl,60h
      js hhh
      sub dl,20h
      hhh:inc esi
  loop again2

mov ecx,slength-cmpslength
again1:
       mov dl,string[edi]
       mov bl,cmpstr[0]
       cmp dl,bl
       jnz bu
       mov dl,string[edi+1]
       mov bl,cmpstr[1]
       cmp dl,bl
       jnz bu
       mov dl,string[edi+2]
       mov bl,cmpstr[2]
       cmp dl,bl
       jnz bu
       inc eax     
 bu:inc edi
loop again1
