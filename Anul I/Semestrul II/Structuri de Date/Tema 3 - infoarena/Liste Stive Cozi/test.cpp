#include <iostream>

int camere[10];
int main(){
    int n;
    char c[] = {""};
    std::cin >> n;
    std::cout << n;
    std::cin >> c;

    for(int i = 0; i < n; i++){
        if(c[i] == 'L'){
            for(int j = 0; j < 10; j++)
                if(camere[j] == 0){
                    camere[j] = 1;
                    break;
                }
        }
        else if(c[i] == 'R'){
            for(int j = 9; j >= 0; j--)
                if(camere[j] == 0){
                    camere[j] = 1;
                    break;
                }
        }
        else{
            camere[(c[i] - 48)] = 0;
        }
    }

    std::cout << "ok\n";

    for(int i = 0; i < 10; i++)
        std::cout << camere[i];
    std::cout << "\n";
    return 0;
}