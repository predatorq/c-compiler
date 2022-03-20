int main() {
	int n;
	n = 10;
    int _m7n3;
    _m7n3 = 1e10;
    _m7n3 = 0b10;
    _m7n3 = 0xFA;
    _m7n3 = 0777; // just a comment

    int a;
    int b;
    a = 1;
    b = 0;
    a = a & b;

    n = readint("Please input an integer: ");
	print("Your input number is: %d", n);

    while (n >= 0) {
		if (n == 5) {
			break;
		}
		n -= 1;
        n << 1;
    }
    return 0;
}