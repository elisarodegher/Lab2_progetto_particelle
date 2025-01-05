#include "ResonanceType.h" //non me lo sente
#include<array>

int main() {
    
    char n_1 = 'a';
    char n_2 = 'b';
    char* n_1_p{&n_1};
    char* n_2_p{&n_2};
    ParticleType part{n_1_p, 4.5, -1};
    ResonanceType res{n_2_p, 3.5, 1, 0.5};
    std::array<ParticleType*, 2> point_array {&part, &res};

    for (int i = 0; i < 2; ++i) {
        point_array[i]->Print();
    }
}