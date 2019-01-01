# Vulnerable program
Here you can find the source code of a vulnerable program.

To find the address of an instruction to probe, you can use gdb as the compilation doesn't strip the symbols. The following example shows how to find an instruction address to probe the function `input_A`:

```
$ gdb ./abcd

(gdb) disas input_A
Dump of assembler code for function input_A:
   0x0000000000002000 <+0>:	push   %rbp
   0x0000000000002001 <+1>:	mov    %rsp,%rbp
   0x0000000000002004 <+4>:	sub    $0x10,%rsp
   0x0000000000002008 <+8>:	movl   $0x3,-0x4(%rbp)
   0x000000000000200f <+15>:	movl   $0x4,-0xc(%rbp)
   0x0000000000002016 <+22>:	mov    -0xc(%rbp),%eax
   0x0000000000002019 <+25>:	add    %eax,-0x4(%rbp)
   0x000000000000201c <+28>:	mov    -0x4(%rbp),%eax
   0x000000000000201f <+31>:	imul   -0xc(%rbp),%eax
   0x0000000000002023 <+35>:	mov    %eax,-0x4(%rbp)
   0x0000000000002026 <+38>:	mov    -0xc(%rbp),%eax
   0x0000000000002029 <+41>:	add    %eax,-0x4(%rbp)
   0x000000000000202c <+44>:	mov    -0x4(%rbp),%eax
   0x000000000000202f <+47>:	imul   -0xc(%rbp),%eax
   0x0000000000002033 <+51>:	mov    %eax,-0x4(%rbp)
   0x0000000000002036 <+54>:	mov    -0xc(%rbp),%eax
   0x0000000000002039 <+57>:	add    %eax,-0x4(%rbp)
   0x000000000000203c <+60>:	mov    -0x4(%rbp),%eax
   0x000000000000203f <+63>:	imul   -0xc(%rbp),%eax
   0x0000000000002043 <+67>:	mov    %eax,-0x4(%rbp)
   0x0000000000002046 <+70>:	mov    -0xc(%rbp),%eax
   0x0000000000002049 <+73>:	add    %eax,-0x4(%rbp)
   0x000000000000204c <+76>:	mov    -0x4(%rbp),%eax
   0x000000000000204f <+79>:	imul   -0xc(%rbp),%eax
   0x0000000000002053 <+83>:	mov    %eax,-0x4(%rbp)
   0x0000000000002056 <+86>:	mov    -0xc(%rbp),%eax
   0x0000000000002059 <+89>:	add    %eax,-0x4(%rbp)
   0x000000000000205c <+92>:	mov    -0x4(%rbp),%eax
   0x000000000000205f <+95>:	imul   -0xc(%rbp),%eax
   0x0000000000002063 <+99>:	mov    %eax,-0x4(%rbp)
   0x0000000000002066 <+102>:	mov    -0xc(%rbp),%eax
   0x0000000000002069 <+105>:	add    %eax,-0x4(%rbp)
   0x000000000000206c <+108>:	mov    -0x4(%rbp),%eax
   0x000000000000206f <+111>:	imul   -0xc(%rbp),%eax
   0x0000000000002073 <+115>:	mov    %eax,-0x4(%rbp)
   0x0000000000002076 <+118>:	mov    -0xc(%rbp),%eax
   0x0000000000002079 <+121>:	add    %eax,-0x4(%rbp)
   0x000000000000207c <+124>:	mov    -0x4(%rbp),%eax
   0x000000000000207f <+127>:	imul   -0xc(%rbp),%eax
   0x0000000000002083 <+131>:	mov    %eax,-0x4(%rbp)
   0x0000000000002086 <+134>:	mov    -0xc(%rbp),%eax
   0x0000000000002089 <+137>:	add    %eax,-0x4(%rbp)
   0x000000000000208c <+140>:	mov    -0x4(%rbp),%eax
   0x000000000000208f <+143>:	imul   -0xc(%rbp),%eax
   0x0000000000002093 <+147>:	mov    %eax,-0x4(%rbp)
   0x0000000000002096 <+150>:	mov    -0xc(%rbp),%eax
   0x0000000000002099 <+153>:	add    %eax,-0x4(%rbp)
   0x000000000000209c <+156>:	mov    -0x4(%rbp),%eax
   0x000000000000209f <+159>:	imul   -0xc(%rbp),%eax
   0x00000000000020a3 <+163>:	mov    %eax,-0x4(%rbp)
   0x00000000000020a6 <+166>:	mov    -0xc(%rbp),%eax
   0x00000000000020a9 <+169>:	add    %eax,-0x4(%rbp)
   0x00000000000020ac <+172>:	mov    -0x4(%rbp),%eax
   0x00000000000020af <+175>:	imul   -0xc(%rbp),%eax
   0x00000000000020b3 <+179>:	mov    %eax,-0x4(%rbp)
   0x00000000000020b6 <+182>:	mov    -0xc(%rbp),%eax
   0x00000000000020b9 <+185>:	add    %eax,-0x4(%rbp)
   0x00000000000020bc <+188>:	mov    -0x4(%rbp),%eax
   0x00000000000020bf <+191>:	imul   -0xc(%rbp),%eax
   0x00000000000020c3 <+195>:	mov    %eax,-0x4(%rbp)
   0x00000000000020c6 <+198>:	mov    -0xc(%rbp),%eax
   0x00000000000020c9 <+201>:	add    %eax,-0x4(%rbp)
   0x00000000000020cc <+204>:	mov    -0x4(%rbp),%eax
   0x00000000000020cf <+207>:	imul   -0xc(%rbp),%eax
   0x00000000000020d3 <+211>:	mov    %eax,-0x4(%rbp)
   0x00000000000020d6 <+214>:	mov    -0xc(%rbp),%eax
   0x00000000000020d9 <+217>:	add    %eax,-0x4(%rbp)
   0x00000000000020dc <+220>:	mov    -0x4(%rbp),%eax
   0x00000000000020df <+223>:	imul   -0xc(%rbp),%eax
   0x00000000000020e3 <+227>:	mov    %eax,-0x4(%rbp)
   0x00000000000020e6 <+230>:	mov    -0xc(%rbp),%eax
   0x00000000000020e9 <+233>:	add    %eax,-0x4(%rbp)
   0x00000000000020ec <+236>:	mov    -0x4(%rbp),%eax
   0x00000000000020ef <+239>:	imul   -0xc(%rbp),%eax
   0x00000000000020f3 <+243>:	mov    %eax,-0x4(%rbp)
   0x00000000000020f6 <+246>:	mov    -0xc(%rbp),%eax
   0x00000000000020f9 <+249>:	add    %eax,-0x4(%rbp)
   0x00000000000020fc <+252>:	mov    -0x4(%rbp),%eax
   0x00000000000020ff <+255>:	imul   -0xc(%rbp),%eax
   0x0000000000002103 <+259>:	mov    %eax,-0x4(%rbp)
   0x0000000000002106 <+262>:	mov    -0xc(%rbp),%eax
   0x0000000000002109 <+265>:	add    %eax,-0x4(%rbp)
   0x000000000000210c <+268>:	mov    -0x4(%rbp),%eax
   0x000000000000210f <+271>:	imul   -0xc(%rbp),%eax
   0x0000000000002113 <+275>:	mov    %eax,-0x4(%rbp)
   0x0000000000002116 <+278>:	mov    -0xc(%rbp),%eax
   0x0000000000002119 <+281>:	add    %eax,-0x4(%rbp)
   0x000000000000211c <+284>:	mov    -0x4(%rbp),%eax
   0x000000000000211f <+287>:	imul   -0xc(%rbp),%eax
   0x0000000000002123 <+291>:	mov    %eax,-0x4(%rbp)
   0x0000000000002126 <+294>:	mov    -0xc(%rbp),%eax
   0x0000000000002129 <+297>:	add    %eax,-0x4(%rbp)
   0x000000000000212c <+300>:	mov    -0x4(%rbp),%eax
   0x000000000000212f <+303>:	imul   -0xc(%rbp),%eax
   0x0000000000002133 <+307>:	mov    %eax,-0x4(%rbp)
   0x0000000000002136 <+310>:	mov    -0xc(%rbp),%eax
   0x0000000000002139 <+313>:	add    %eax,-0x4(%rbp)
   0x000000000000213c <+316>:	mov    -0x4(%rbp),%eax
   0x000000000000213f <+319>:	imul   -0xc(%rbp),%eax
   0x0000000000002143 <+323>:	mov    %eax,-0x4(%rbp)
   0x0000000000002146 <+326>:	mov    -0xc(%rbp),%eax
   0x0000000000002149 <+329>:	add    %eax,-0x4(%rbp)
   0x000000000000214c <+332>:	mov    -0x4(%rbp),%eax
   0x000000000000214f <+335>:	imul   -0xc(%rbp),%eax
   0x0000000000002153 <+339>:	mov    %eax,-0x4(%rbp)
   0x0000000000002156 <+342>:	movl   $0x0,-0x8(%rbp)
   0x000000000000215d <+349>:	jmp    0x2187 <input_A+391>
   0x000000000000215f <+351>:	mov    -0x4(%rbp),%eax
   0x0000000000002162 <+354>:	imul   -0xc(%rbp),%eax
   0x0000000000002166 <+358>:	mov    %eax,-0x4(%rbp)
   0x0000000000002169 <+361>:	mov    -0xc(%rbp),%eax
   0x000000000000216c <+364>:	add    %eax,-0x4(%rbp)
   0x000000000000216f <+367>:	mov    -0x4(%rbp),%eax
   0x0000000000002172 <+370>:	imul   -0xc(%rbp),%eax
   0x0000000000002176 <+374>:	mov    %eax,-0x4(%rbp)
   0x0000000000002179 <+377>:	mov    -0x4(%rbp),%eax
   0x000000000000217c <+380>:	imul   -0xc(%rbp),%eax
   0x0000000000002180 <+384>:	mov    %eax,-0x4(%rbp)
   0x0000000000002183 <+387>:	addl   $0x1,-0x8(%rbp)
   0x0000000000002187 <+391>:	cmpl   $0x752f,-0x8(%rbp)
   0x000000000000218e <+398>:	jle    0x215f <input_A+351>
   0x0000000000002190 <+400>:	mov    -0x4(%rbp),%eax
   0x0000000000002193 <+403>:	imul   -0xc(%rbp),%eax
   0x0000000000002197 <+407>:	mov    %eax,-0x4(%rbp)
   0x000000000000219a <+410>:	mov    -0xc(%rbp),%eax
   0x000000000000219d <+413>:	add    %eax,-0x4(%rbp)
   0x00000000000021a0 <+416>:	mov    -0x4(%rbp),%eax
   0x00000000000021a3 <+419>:	imul   -0xc(%rbp),%eax
   0x00000000000021a7 <+423>:	mov    %eax,-0x4(%rbp)
   0x00000000000021aa <+426>:	mov    -0x4(%rbp),%eax
   0x00000000000021ad <+429>:	imul   -0xc(%rbp),%eax
   0x00000000000021b1 <+433>:	mov    %eax,-0x4(%rbp)
   0x00000000000021b4 <+436>:	lea    0x3fcd(%rip),%rdi        # 0x6188
   0x00000000000021bb <+443>:	callq  0x610 <puts@plt>
   0x00000000000021c0 <+448>:	nop
   0x00000000000021c1 <+449>:	leaveq
   0x00000000000021c2 <+450>:	retq   
End of assembler dump.
```

To probe the instruction at `input_A+398` (`jle    0x215f <input_A+351>` which is the condition to exit the loop), you should probe the address `0x218e`.
Note that the addresses in your binary might not be the same.
