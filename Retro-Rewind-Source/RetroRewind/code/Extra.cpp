#include <RetroRewind.hpp>

namespace RetroRewind {

//Visual codes
//No Sun Filter [Anarion]
kmWrite8(0x8025739F, 0x00);
kmWrite8(0x80256F7F, 0x00);
kmWrite8(0x802575DF, 0x00);
kmWrite8(0x802572BF, 0x00);

//Remove Background Blur [Davidevgen]
kmWrite32(0x80258184, 0x30);
kmWrite32(0x80257E64, 0x30);
kmWrite32(0x80257B24, 0x30);
kmWrite32(0x80257F44, 0x30);

//Online codes
//Don't Lose VR While Disconnecting [Bully]
kmWrite32(0x80856560, 0x60000000);

//Instant Voting Roulette Decide / Skip Voting [Ro]
kmWrite32(0x80643BC4, 0x4800011C);

//VR System Changes [MrBean35000vr]
kmWrite32(0x8052D134, 0x1C630002);
kmWrite32(0x8052D138, 0x2C03D8F2);
kmWrite32(0x8052D13C, 0x40800008);
kmWrite32(0x8052D140, 0x3860D8F2);
kmWrite32(0x8052D144, 0x2C03270E);
kmWrite32(0x8052D1DC, 0x1C630003);
kmWrite32(0x8052D1E0, 0x2C03D8F2);
kmWrite32(0x8052D1E4, 0x40800008);
kmWrite32(0x8052D1E8, 0x3860D8F2);
kmWrite32(0x8052D1EC, 0x2C03270E);


//Cap VR loss from one victorious opponent between 0 and -10.
asmFunc GetCapVRLoss() {
    ASM(
  lwz       r3, 0x14(r1);
  cmpwi     r3, -10;
  bge       0f;
  li        r3, -10;
  b         1f;
  0:;
  cmpwi     r3, 0;
  ble       1f;
  li        r3, 0;
  1:;
    )
}
kmCall(0x8052D260, GetCapVRLoss);

//Cap VR gain from one defeated opponent between 1 and 5.
asmFunc GetCapVRGain() {
    ASM(
  lwz       r3, 0x14(r1);
  cmpwi     r3, 1;
  bge       0f;
  li        r3, 1;
  b         1f;
  0:;
  cmpwi     r3, 10;
  ble       1f;
  li        r3, 10;
  1:;
    )
}
kmCall(0x8052D1B0, GetCapVRGain);

} // namespace RetroRewind