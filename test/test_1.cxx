#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "ResonanceType.h"

TEST_CASE ("Testing particle attribute getters") {
    char name_1 = 'a';
    char* name_1_ptr{&name_1};
    ParticleType part{name_1_ptr, 3.4, 1};
    
    CHECK(part.GetParticleName() == 'a');
    CHECK(part.GetParticleCharge() == 1);
    CHECK(part.GetParticleMass() == 3.4);
}

TEST_CASE("Testing resonance attribute getters") {
    char name_2 = 'b';
    char* name_2_ptr{&name_2};
    ResonanceType res{name_2_ptr, 4.5, -1, 0.3};

    CHECK(res.GetParticleName() == 'b');
    CHECK(res.GetParticleCharge() == -1);
    CHECK(res.GetParticleMass() == 4.5);
    CHECK(res.GetResonanceTypeWidth() == 0.3);
}

TEST_CASE("Testing const-ness of methods") {
    char name_1 = 'c';
    char* name_1_ptr{&name_1};
    const ParticleType part{name_1_ptr, 6.4, 2};
    
    CHECK(part.GetParticleName() == 'c');
    CHECK(part.GetParticleCharge() == 2);
    CHECK(part.GetParticleMass() == 6.4);

    char name_2 = 'd';
    char* name_2_ptr{&name_2};
    const ResonanceType res{name_2_ptr, 5.5, -2, 0.4};

    CHECK(res.GetParticleName() == 'd');
    CHECK(res.GetParticleCharge() == -2);
    CHECK(res.GetParticleMass() == 5.5);
    CHECK(res.GetResonanceTypeWidth() == 0.4);
}