#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>

const int WIDTH = 200;
const int HEIGHT = 160;
const float R1 = 1;
const float R2 = 2;
const float K1 = 150;
const float K2 = 5;

void renderAsciiFrame(float &A, float &B){
    std::vector<char>buffer(WIDTH * HEIGHT, ' ');
    std::vector<float> zBuffer(WIDTH * HEIGHT, 0);

    float cA = std::cos(A), sA = std::sin(A);
    float cB = std::cos(B), sB = std::sin(B);

    for(float theta = 0; theta < 2 * M_PI; theta += 0.07){
        float ct = std::cos(theta);
        float st = std::sin(theta);

        for(float phi = 0; phi < 2 * M_PI; phi += 0.02){
            float sp = std::sin(phi);
            float cp = std::cos(phi);

            float h = ct + 2;
            float D = 1 / (sp * h * sA + st * cA + 5);
            float t = sp * h * cA - st * sA;

            int x = static_cast<int>(WIDTH / 2 + (WIDTH / 4) * D * (cp * h * cB - t * sB));
            int y = static_cast<int>(HEIGHT / 2 + (HEIGHT / 4) * D * (cp * h * sB + t * cB));

            int o = x + WIDTH * y;
            int N = static_cast<int>(8 * ((st * sA - sp * ct * cA) * cB - sp * ct * sA - st * cA - cp * ct * sB));
            if ( y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && D > zBuffer[o]){
                zBuffer[o] = D;
                buffer[o] = ".,-~:;=!*#$@"[std::max(0, N)];
            }
        }
    }
    std::cout << "\x1b[H";
    for(int i=0; i < HEIGHT; i++){
        for(int j=0; j < WIDTH; j++){
            std::cout << buffer[i * WIDTH +j];
        }
        std::cout << '\n';
    }
}

int main(){
    float A = 1;
    float B = 1;
    std::cout << "\x1b[2J";

    while(true){
        renderAsciiFrame(A, B);
        A += 0.07;
        B += 0.03;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}