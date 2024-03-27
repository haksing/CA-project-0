#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBinary(unsigned int num) {
	if (num > 1) {
		printBinary(num / 2);
	}
	printf("%d", num % 2);
}
int translate_register(char* ary)
{
	if (strcmp(ary, "zero") == 0)
	{
		return 0;
	}
	else if (strcmp(ary, "at") == 0)
	{
		return 1;
	}
	else if (strcmp(ary, "gp") == 0)
	{
		return 28;
	}
	else if (strcmp(ary, "sp") == 0)
	{
		return 29;
	}
	else if (strcmp(ary, "fp") == 0)
	{
		return 30;
	}
	else if (strcmp(ary, "ra") == 0)
	{
		return 31;
	}
	else if (ary[0] == 'v')
	{
		return atoi(&ary[1]) + 2;
	}
	else if (ary[0] == 'a')
	{
		return atoi(&ary[1]) + 4;
	}
	else if (ary[0] == 's')
	{
		return atoi(&ary[1]) + 16;
	}
	else if (ary[0] == 'k')
	{
		return atoi(&ary[1]) + 26;
	}
	else if (ary[0] == 't')
	{
		if (atoi(&ary[1]) <= 7) return atoi(&ary[1]) + 8;
		else return atoi(&ary[1]) + 16;
	}
}
static unsigned int translate(int nr_tokens, char* tokens[])
{
	int opcode = 0;
	int rs = 0;
	int rt = 0;
	int rd = 0;
	int shamt = 0;
	int funct = 0;
	int constant_OR_address = 0;
	char string[8];
	if (tokens[0] == "add") // add  0 + 0x20
	{
		opcode = 0b000000;
		funct = 0x20;
		int shamt = 0b00000;
		int value = 0;
		rd = translate_register(tokens[1]);
		rs = translate_register(tokens[2]);
		rt = translate_register(tokens[3]);
		
		value = (opcode << 5) | rs;
		value = (value << 5) | rt;
		value = (value << 5) | rd;
		value = (value << 5) | shamt;
		value = (value << 6) | funct;
		printBinary(value);
		printf("\n");
		for (int i = 7; i >= 0; i--) {
			int digit = value & 0b1111; 
			printf("%d\n", digit);
			
			if (digit < 10)
				string[i] = (char)(digit + '0'); // 0부터 9까지는 '0'부터 '9'까지의 문자로 변환
			else
				string[i] = (char)(digit - 10 + 'A'); // 10부터 15까지는 'A'부터 'F'까지의 문자로 변환
			
			value = (value >> 4);
		}
		for (int i = 0; i < 8; i++)
		{
			printf("%c", string[i]);
		}
		printf("\n");
	}
	else if (tokens[0] == "addi")
	{
		opcode = 0x0c;
		funct = 0x20;
		int constant_address = atoi(tokens[3]); // 0x3225같은 16진수나 0b0011같은 문자열은 atoi로 처리불가
		printf("con : %d\n", constant_address);
		int value = 0;
		rs = translate_register(tokens[2]);
		rt = translate_register(tokens[1]);

		value = (opcode << 5) | rs;
		value = (value << 5) | rt;
		value = (value << 16) | constant_address;
		printBinary(value);
		printf("\n");
		for (int i = 7; i >= 0; i--) {
			int digit = value & 0b1111;
			printf("%d\n", digit);

			if (digit < 10)
				string[i] = (char)(digit + '0'); // 0부터 9까지는 '0'부터 '9'까지의 문자로 변환
			else
				string[i] = (char)(digit - 10 + 'A'); // 10부터 15까지는 'A'부터 'F'까지의 문자로 변환

			value = (value >> 4);
		}
		for (int i = 0; i < 8; i++)
		{
			printf("%c", string[i]);
		}
		printf("\n");
	}
	else if (tokens[0] == "sub")
	{

	}
	else if (tokens[0] == "and")
	{

	}
	else if (tokens[0] == "andi")
	{

	}
	else if (tokens[0] == "or")
	{

	}
	else if (tokens[0] == "ori")
	{

	}
	else if (tokens[0] == "nor")
	{

	}
	else if (tokens[0] == "lw")
	{

	}
	else if (tokens[0] == "sw")
	{

	}
	else if (tokens[0] == "sll")
	{

	}
	else if (tokens[0] == "srl")
	{

	}
	else if (tokens[0] == "sra")
	{

	}
	else if (tokens[0] == "beq")
	{

	}
	else if (tokens[0] == "bne")
	{

	}
	return 0x02324022;
}

int main(void)
{
	char* v[] = { "add","t0","t1","t2" };
	char* addi[] = { "addi","sp","sp","0x3225" };
	translate(4,v);
	translate(4,addi);

	return 0;
}
