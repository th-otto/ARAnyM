#include <stdio.h>

int main(int argc, char **argv)
{
	char *n1, *n2;
	FILE *f1, *f2;
	unsigned long ptr;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		return 1;
	}

	n1 = argv[1];
	n2 = argv[2];
	f1 = fopen(n1, "rb");
	if (f1 == NULL) {
		fprintf(stderr, "Error opening '%s'\n", n1);
		return 2;
	}
	f2 = fopen(n2, "rb");
	if (f2 == NULL) {
		fprintf(stderr, "Error opening '%s'\n", n2);
		fclose(f1);
		return 3;
	}

	ptr = 0;
	printf("ROMdiff tosdiff[] = {\n");
	while(!feof(f1) && !feof(f2)) {
		unsigned char c1, c2;
		c1 = fgetc(f1);
		c2 = fgetc(f2);
		if (c1 != c2)
			printf("\t{%lu, %d},\n", ptr, c2-c1);
		ptr++;
	}
	printf("\t{-1, 0}\n};\n");

	fclose(f1);
	fclose(f2);
}
