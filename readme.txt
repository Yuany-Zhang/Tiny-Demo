TINY扩充语言的语义分析及代码生成




一、实验内容：

扩充的语法规则有：实现 while、do while、for语句和求余计算式子，具体文法规则自行构造。
可参考：P97及P136的文法规则。

(1) While-stmt --> while  exp  do  stmt-sequence  endwhile
(2) Dowhile-stmt-->do  stmt-sequence  while  exp 
(3) for-stmt-->for identifier:=simple-exp  to  simple-exp  do  stmt-sequence enddo    步长递增1
(4) for-stmt-->for identifier:=simple-exp  downto  simple-exp  do  stmt-sequence enddo    步长递减1