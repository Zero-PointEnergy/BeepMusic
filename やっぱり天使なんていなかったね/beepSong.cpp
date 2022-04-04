#include <bits\stdc++.h>
#include <windows.h>
#include "../pitchFrequency.h"
// Tempo 是乐曲演奏速度，单位 bpm (beats per minute)
#define Tempo 126
// semibreveDuration 是全音符时值
#define semibreveDuration 1952
// minimDuration 是二分音符时值
#define minimDuration 976
// crotchetDuration 是四分音符时值
#define crotchetDuration 476
// quaverDuration 是八分音符时值
#define quaverDuration 238
// semiquaverDuration 是十六分音符时值
#define semiquaverDuration 119

using namespace std;

// 乐谱结构体
typedef struct {
    float frequency;
    float duration;
}staff;

// やっぱり天使なんていなかったね
// D-flat major
// flatD、flatE、F、flatG、flatA、flatB、C 与 flatD
// C D E F G A B

// 乐谱，右手演奏部分，即双行五线谱的上面那行
staff stfRightHand[] = {
    // bar 1
    flatD6,quaverDuration,C6,quaverDuration,flatA5,quaverDuration,flatB5,quaverDuration,rest,minimDuration,
    // bar 2
    flatD6,quaverDuration,C6,quaverDuration,flatA5,quaverDuration,flatE5,quaverDuration,rest,minimDuration,
    // bar 3
    flatD6,quaverDuration,C6,quaverDuration,flatA5,quaverDuration,flatD5,quaverDuration,rest,minimDuration,
    // bar 4
    flatD5,quaverDuration,flatE5,quaverDuration,F5,crotchetDuration,flatA5,crotchetDuration,flatE5,crotchetDuration,
    // bar 5
    flatA5,crotchetDuration,/* 这里是二分附点音符连音琶音开始，但是我现在不知道该怎么实现这个效果 */F4,(crotchetDuration),flatD5,(crotchetDuration),F5,(minimDuration),
    // bar 6
    /*F4,1,flatD5,1,F5,1,*//* 到这里结束,后面开始升八度 */flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 7
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 8
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 9
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 10
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 11
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 12
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 13
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 14
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 15
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 16
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 17
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,
    // bar 18
    flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,
    // bar 19
    F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 20
    flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,
    // bar 21
    flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 22
    flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,
    // bar 23
    flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 24
    flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,
    // bar 25
    flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 26
    flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,
    // bar 27
    flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 28
    flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 29
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 30
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 31
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 32
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 33
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 34
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 35
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 36
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 37
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 38
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 39
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 40
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 41
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 42
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 43
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 44
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 45
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 46
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 47
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 48
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 49
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 50
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,
    // bar 51
    flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatA6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,
    // bar 52
    F6,quaverDuration,flatB6,quaverDuration,flatB5,quaverDuration,F6,quaverDuration,flatB6,quaverDuration,rest,quaverDuration,rest,crotchetDuration
};

// 乐谱，左手演奏部分，即双行五线谱的下面那行
staff stfLeftHand[] = {
    // bar 1
    rest,crotchetDuration,rest,quaverDuration,flatG3,quaverDuration,flatB3,quaverDuration,flatD4,quaverDuration,flatG4,quaverDuration,flatE4,quaverDuration,
    // bar 2
    flatE4,quaverDuration,flatD4,quaverDuration,C4,quaverDuration,flatA3,quaverDuration,C4,quaverDuration,flatE4,quaverDuration,flatA4,quaverDuration,flatG4,quaverDuration,
    // bar 3
    F4,quaverDuration,flatE4,quaverDuration,flatD4,quaverDuration,flatB3,quaverDuration,flatD4,quaverDuration,F4,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,
    // bar 4
    F4,quaverDuration,flatD4,quaverDuration,/* 踩下右踏板 */flatB3,minimDuration,/* 释放右踏板。后面这里是连音 */flatA3,minimDuration,
    // bar 5
    /* 踩下右踏板 */ flatG3,minimDuration,flatA3,semibreveDuration, /* 释放右踏板 */ // 这里是琶音，我不知道怎么写了，就这样吧
    // bar 6 连音开始
    flatB2,minimDuration,
    // bar 7
    flatB2,semibreveDuration,
    // bar 8 
    flatB2,minimDuration, /* 结束连音 */ /* 连音开始 */flatB2,minimDuration,
    // bar 9
    flatB2,semibreveDuration, // 连音结束
    // bar 10
    rest,quaverDuration,flatD6,quaverDuration,C6,quaverDuration,flatA5,quaverDuration,F5,crotchetDuration,flatE5,crotchetDuration,
    // bar 11
    flatD5,crotchetDuration,C5,crotchetDuration,flatB4,crotchetDuration,C5,crotchetDuration,
    // bar 12
    flatD5,crotchetDuration,flatE5,crotchetDuration,F5,crotchetDuration,flatE5,crotchetDuration,
    // bar 13
    flatD5,crotchetDuration,C5,crotchetDuration,flatB4,crotchetDuration,flatE5,crotchetDuration,
    // bar 14
    F5,quaverDuration,flatD5,quaverDuration,C5,quaverDuration,flatA4,quaverDuration,flatB4,crotchetDuration,flatA4,crotchetDuration,
    // bar 15
    flatE4,crotchetDuration,flatA4,crotchetDuration,flatE4,minimDuration,
    // bar 16
    flatE4,crotchetDuration,flatD4,quaverDuration,flatE4,quaverDuration,F4,minimDuration,
    // bar 17
    F4,crotchetDuration,flatA4,quaverDuration,flatG4,quaverDuration,flatD4,minimDuration,
    // bar 18
    flatD4,crotchetDuration,flatD5,quaverDuration,C5,quaverDuration,flatA4,quaverDuration,flatB4,crotchetDuration,flatA4,quaverDuration,
    // bar 19
    flatA4,quaverDuration,flatE4,crotchetDuration,flatA4,crotchetDuration,flatE4,crotchetDuration,
    // bar 20
    flatE4,minimDuration,flatD4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 21
    F4,minimDuration,flatA4,quaverDuration,C5,quaverDuration,flatD5,crotchetDuration,
    // bar 22
    flatD5,crotchetDuration,C5,minimDuration,flatB4,crotchetDuration,
    // bar 23
    flatB4,quaverDuration,flatD5,quaverDuration,C5,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,flatE4,crotchetDuration,rest,quaverDuration,
    // bar 24
    flatE4,minimDuration,flatA4,quaverDuration,C4,quaverDuration,flatD4,crotchetDuration,
    // bar 25
    flatD4,minimDuration,flatD4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 26
    flatB4,crotchetDuration,flatA4,crotchetDuration,F4,crotchetDuration,flatD4,crotchetDuration,
    // bar 27
    flatD4,(crotchetDuration+quaverDuration),C4,quaverDuration,flatD4,quaverDuration,flatE4,crotchetDuration,flatA4,quaverDuration,
    // bar 28
    flatE4,(crotchetDuration+quaverDuration),C4,quaverDuration,flatA3,quaverDuration,C4,crotchetDuration,
    // bar 29
    C4,minimDuration,rest,minimDuration,
    // bar 30
    rest,semibreveDuration,
    // bar 31
    rest,semibreveDuration,
    // bar 32
    rest,quaverDuration,flatB4,quaverDuration,flatB4,quaverDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,flatB4,crotchetDuration,
    // bar 33
    flatB4,quaverDuration,flatB4,quaverDuration,flatB4,quaverDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,flatA4,crotchetDuration,
    // bar 34
    flatA4,quaverDuration,C5,semiquaverDuration,flatD5,semiquaverDuration,C5,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 35
    F4,quaverDuration,C5,semiquaverDuration,flatD5,semiquaverDuration,C5,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 36
    F4,quaverDuration,flatB4,quaverDuration,flatB4,quaverDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,F5,crotchetDuration,
    // bar 37
    F5,quaverDuration,F5,quaverDuration,F5,quaverDuration,flatE5,quaverDuration,flatE5,quaverDuration,flatD5,quaverDuration,C5,crotchetDuration,
    // bar 38
    flatD5,crotchetDuration,C5,crotchetDuration,flatA4,quaverDuration,F4,quaverDuration,C5,crotchetDuration,
    // bar 39
    C5,(crotchetDuration+quaverDuration),flatB4,quaverDuration,C5,quaverDuration,flatD5,(crotchetDuration+quaverDuration),
    // bar 40
    flatD5,quaverDuration,flatB4,quaverDuration,flatB4,quaverDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,flatB4,crotchetDuration,
    // bar 41
    flatB4,quaverDuration,flatB4,quaverDuration,flatB4,quaverDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,flatA4,crotchetDuration,
    // bar 42
    flatA4,quaverDuration,C5,semiquaverDuration,flatD5,semiquaverDuration,C5,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 43
    F4,quaverDuration,C5,semiquaverDuration,flatD5,semiquaverDuration,C5,quaverDuration,flatB4,quaverDuration,flatA4,quaverDuration,flatE4,quaverDuration,F4,crotchetDuration,
    // bar 44
    flatA4,crotchetDuration,C5,quaverDuration,flatD5,quaverDuration,flatE5,quaverDuration,flatA4,quaverDuration,flatB4,crotchetDuration,
    // bar 45
    flatB4,(crotchetDuration+quaverDuration),flatB4,quaverDuration,C5,minimDuration,
    // bar 46
    C5,crotchetDuration,flatD5,quaverDuration,C5,quaverDuration,F4,minimDuration,
    // bar 47
    F4,minimDuration,rest,minimDuration,
    // bar 48
    rest,semibreveDuration,
    // bar 49
    rest,semibreveDuration,
    // bar 50
    rest,semibreveDuration,
    // bar 51
    rest,semibreveDuration,
    // bar 52
    rest,semibreveDuration
};

void playStfRightHand() {
    cout << "Start Playing staff(R)" << endl;
    Beep(rest,Tempo);
    for (int i=0; i<sizeof(stfRightHand)/sizeof(staff); i++) {
       Beep(stfRightHand[i].frequency,stfRightHand[i].duration);
       cout << "R => " << stfRightHand[i].frequency << "\t" << stfRightHand[i].duration << endl;
    }
}

void playStfLeftHand() {
    cout << "Start Playing staff(L)" << endl;
    Beep(rest,Tempo);
    for (int i=0; i<sizeof(stfLeftHand)/sizeof(staff); i++) {
       Beep(stfLeftHand[i].frequency,stfLeftHand[i].duration);
       cout << "L => " << stfLeftHand[i].frequency << "\t" << stfLeftHand[i].duration << endl;
    }
}

int main(int argc, char const *argv[]) {
    // 注意，目前使用双线程 Beep 函数播放可能会导致播放情况不理想
    // 这个问题暂时没有解决
    cout << "Thread started" << endl;
    thread playStaffRightHand(playStfRightHand);
    // thread playStaffLeftHand(playStfLeftHand);
    playStaffRightHand.join();
    // playStaffLeftHand.join();
    cout << "Thread ended" << endl;
    return 0;
}
