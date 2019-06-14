//字节序反转
void ReverseBuffer(unsigned char* pInData, unsigned long len)
{
	for(int i=0;i<len/2;i++)
	{
		unsigned char temp = pInData[i];
		pInData[i] = pInData[len-1-i];
		pInData[len-1-i] = temp;
	}
}

//反转dword字节序
unsigned long ReverseDWORD(unsigned long dwData)
{
	unsigned long dwValue;
	dwValue=(dwData<<24 & 0xFF000000) | (dwData<<8 & 0xFF0000) | (dwData >>8 & 0xFF00) | (dwData>>24 & 0xFF);
	return dwValue;
}