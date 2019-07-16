void ShowBinHex(unsigned char* pBin, long len)
{
	// Show 16 bytes each line.
	long lLines = len / 16;
	long lCharInLastLine = 0;
	int j = 0;
	long i = 0;
	if(0 != len % 16)
	{
		lCharInLastLine = len - lLines * 16;
	}

	for(i = 0; i < lLines; ++i)
	{
		for(j = 0; j < 16; ++j)
		{
			printf("%02X ", pBin[16 * i + j]);

			if(j == 7)
				printf("- ");
		}

		printf("    ");

		for(j = 0; j < 16; ++j)
		{
			if(isprint(pBin[16 * i + j]))
				printf("%c", pBin[16 * i + j]);
			else
				printf(".");
		}

		printf("\n");
	}

	if(0 != lCharInLastLine)
	{
		for(j = 0; j < lCharInLastLine; ++j)
		{
			printf("%02X ", pBin[16 * i + j]);

			if(j == 7 && lCharInLastLine > 8)
				printf("- ");
		}

		int k = 0;

		k += ((16 - lCharInLastLine) * 3);

		if(lCharInLastLine <= 8)
		{
			k += 2;
		}

		for(int kk = 0; kk < k; ++kk)
			printf(" ");

		printf("    ");

		for(j = 0; j < lCharInLastLine; ++j)
		{
			if(isprint(pBin[16 * i + j]))
				printf("%c", pBin[16 * i + j]);
			else
				printf(".");
		}

		printf("\n");
	}
	printf("\n");
}


TEST：
unsigned char Inbuf[]="hello";
int len = strlen(inbuf);
ShowBinHex(Inbuf,len);