#ifndef CHARGEBOY_HPP
#define CHARGEBOY_HPP

struct ChargeBoy
{
    Vec2 start_pos;
    Vec2 pos;
    Rect bounds;
    Flip flip;
};

INTERNAL void   InitChargeBoy ();
INTERNAL void   QuitChargeBoy ();
INTERNAL void CreateChargeBoy (ChargeBoy& chargeboy, float x, float y);
INTERNAL void UpdateChargeBoy (ChargeBoy& chargeboy, float dt);
INTERNAL void RenderChargeBoy (ChargeBoy& chargeboy, float dt);
INTERNAL void  ResetChargeBoy (ChargeBoy& chargeboy);

// Helpers used internally.
INTERNAL bool ChargeBoyCheckRightIsGood (ChargeBoy& chargeboy, Vec2 pos);
INTERNAL bool ChargeBoyCheckLeftIsGood  (ChargeBoy& chargeboy, Vec2 pos);
INTERNAL bool ChargeBoyShouldCharge     (ChargeBoy& chargeboy, float dt);

#endif /* CHARGEBOY_HPP */
