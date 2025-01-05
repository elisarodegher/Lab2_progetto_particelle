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