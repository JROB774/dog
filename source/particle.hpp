#ifndef PARTICLE_HPP
#define PARTICLE_HPP

enum ParticleType
{
    PARTICLE_TYPE_TEST,
    PARTICLE_TYPE_SPEC,
    PARTICLE_TYPE_PUFF,
    PARTICLE_TYPE_BASH,
    PARTICLE_TYPE_EXPLODE1,
    PARTICLE_TYPE_SMOKE,
    PARTICLE_TYPE_SBONE,
    PARTICLE_TYPE_LBONE,
    PARTICLE_TYPE_SBREAK,
    PARTICLE_TYPE_MBREAK,
    PARTICLE_TYPE_LBREAK,
    PARTICLE_TYPE_TOTAL
};

struct Particle
{
    ParticleType type;
    Vec2 pos,vel;
    Animation anim;
    Color color;
    bool dead;
    bool visible;

    // -1 can be used to make its life infinite. Which allows for the programmer
    // to specify a different method of deletion in the particle's update e.g.
    // after coming to a complete stop, travelling off-screen, etc.
    float lifetime;

    // Extra variables, do what you want with them if you need to store extra data.
    int extra0;
    int extra1;
};

INTERNAL void InitParticleSystem ();
INTERNAL void QuitParticleSystem ();

INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int min_count, int max_count, float lifetime_multiplier = 1.0f);
INTERNAL void CreateParticles (ParticleType type, int minx, int miny, int maxx, int maxy, int count, float lifetime_multiplier = 1.0f);

INTERNAL void UpdateParticles (float dt);
INTERNAL void DrawParticles   (float dt);
INTERNAL void ClearParticles  ();

// Create and update functions for the different particle types.

INTERNAL void ParticleCreateTest     (Particle& particle);
INTERNAL void ParticleUpdateTest     (Particle& particle, float dt);
INTERNAL void ParticleCreateSpec     (Particle& particle);
INTERNAL void ParticleUpdateSpec     (Particle& particle, float dt);
INTERNAL void ParticleCreatePuff     (Particle& particle);
INTERNAL void ParticleUpdatePuff     (Particle& particle, float dt);
INTERNAL void ParticleCreateBash     (Particle& particle);
INTERNAL void ParticleUpdateBash     (Particle& particle, float dt);
INTERNAL void ParticleCreateExplode1 (Particle& particle);
INTERNAL void ParticleUpdateExplode1 (Particle& particle, float dt);
INTERNAL void ParticleCreateSmoke    (Particle& particle);
INTERNAL void ParticleUpdateSmoke    (Particle& particle, float dt);
INTERNAL void ParticleCreateSBone    (Particle& particle);
INTERNAL void ParticleUpdateSBone    (Particle& particle, float dt);
INTERNAL void ParticleCreateLBone    (Particle& particle);
INTERNAL void ParticleUpdateLBone    (Particle& particle, float dt);
INTERNAL void ParticleCreateSBreak   (Particle& particle);
INTERNAL void ParticleUpdateSBreak   (Particle& particle, float dt);
INTERNAL void ParticleCreateMBreak   (Particle& particle);
INTERNAL void ParticleUpdateMBreak   (Particle& particle, float dt);
INTERNAL void ParticleCreateLBreak   (Particle& particle);
INTERNAL void ParticleUpdateLBreak   (Particle& particle, float dt);

// Base information for each type of particle.

typedef void(*ParticleCreate)(Particle& particle);
typedef void(*ParticleUpdate)(Particle& particle, float dt);

struct ParticleBase
{
    ParticleCreate create;
    ParticleUpdate update;
    std::vector<std::string> anims;
    float min_lifetime;
    float max_lifetime;
};

GLOBAL const ParticleBase PARTICLE_BASE[PARTICLE_TYPE_TOTAL]
{
    { ParticleCreateTest,     ParticleUpdateTest,     { "effect-test0.anim", "effect-test1.anim", "effect-test2.anim", "effect-test3.anim" }, 0.5f, 2.5f }, // PARTICLE_TYPE_TEST
    { ParticleCreateSpec,     ParticleUpdateSpec,     { "effect-spec0.anim", "effect-spec1.anim", "effect-spec2.anim", "effect-spec3.anim", "effect-spec4.anim", "effect-spec5.anim", "effect-spec6.anim", "effect-spec7.anim" }, 0.05f, 0.2f }, // PARTICLE_TYPE_SPEC
    { ParticleCreatePuff,     ParticleUpdatePuff,     { "effect-puff0.anim", "effect-puff1.anim", "effect-puff2.anim" }, -1, -1 }, // PARTICLE_TYPE_SPEC
    { ParticleCreateBash,     ParticleUpdateBash,     { "effect-spec4.anim", "effect-spec5.anim", "effect-spec6.anim", "effect-spec7.anim" }, 0.1f, 0.3f }, // PARTICLE_TYPE_BASH
    { ParticleCreateExplode1, ParticleUpdateExplode1, { "effect-explode0.anim", "effect-explode1.anim", "effect-explode2.anim", "effect-explode3.anim" }, -1, -1 }, // PARTICLE_TYPE_EXPLODE1
    { ParticleCreateSmoke,    ParticleUpdateSmoke,    { "effect-smoke0.anim", "effect-smoke1.anim" }, -1, -1 }, // PARTICLE_TYPE_SMOKE
    { ParticleCreateSBone,    ParticleUpdateSBone,    { "effect-sbone.anim" }, -1, -1 }, // PARTICLE_TYPE_SBONE
    { ParticleCreateLBone,    ParticleUpdateLBone,    { "effect-lbone.anim" }, -1, -1 }, // PARTICLE_TYPE_LBONE
    { ParticleCreateSBreak,   ParticleUpdateSBreak,   { "effect-sbreak0.anim", "effect-sbreak1.anim", "effect-sbreak2.anim", "effect-sbreak3.anim", "effect-sbreak4.anim", "effect-sbreak5.anim", "effect-sbreak6.anim", "effect-sbreak7.anim" }, 6,6 }, // PARTICLE_TYPE_SBREAK
    { ParticleCreateMBreak,   ParticleUpdateMBreak,   { "effect-mbreak0.anim", "effect-mbreak1.anim" }, 6,6 }, // PARTICLE_TYPE_MBREAK
    { ParticleCreateLBreak,   ParticleUpdateLBreak,   { "effect-lbreak0.anim" }, 6,6 }, // PARTICLE_TYPE_LBREAK

};

#endif /* PARTICLE_HPP */
