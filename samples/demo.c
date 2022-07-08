int main() {
    int a, b;
    a = 3 * 3;
    b = 4 + 4;
    while( a < 80 ){
        a = a + b;
        print("INWHILE");
        if(a > 60){
            print("BREAK");
            break;
        }
    }
    // comment
    print("EXIT");
    return 0;
}