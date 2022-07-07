int main() {
    int a, b;
    a = 1 + 1;
    a = 3 * 3;
    b = 2 + 2;
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