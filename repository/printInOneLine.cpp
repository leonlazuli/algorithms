#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

int main()
{
	int i = 0; 
	for ( ; i < 10; i++) 
	{ 
		std::cout << "percentage: " << i << "\r" << std::flush ; /// \r \b 等应该是指光标移动，而不是直接对打印出得字符操作
	// printf("sec: %d\b\b\b\b\b\b", i); // /r是回车的转义符，目的是回到行首 
	// fflush(stdout); // 如果不能及时显示，就把这一行加上 
		 sleep(1); // 我觉得sleep放显示后面比较好，呵呵 
	} 
	std::cout << std::endl;
}